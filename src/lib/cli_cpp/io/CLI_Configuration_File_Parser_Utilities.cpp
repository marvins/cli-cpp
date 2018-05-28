/**
 * @file    CLI_Configuration_File_Parser_Utilities.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#include "CLI_Configuration_File_Parser_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>
#include <stdexcept>
#include <string>
#include <unistd.h>


// CLI Libraries
#include "../cli/A_Connection_Manager_Socket_Config.hpp"
#include "../cli/A_Socket_JSON_Instance.hpp"
#include "../cli/A_Socket_Telnet_Instance.hpp"
#include "../core/ConnectionType.hpp"
#include "../core/SessionType.hpp"
#include "../utility/Log_Utilities.hpp"

namespace CLI{
namespace IO{
namespace CONFIG{
namespace XML{


/********************************/
/*          Constructor         */
/********************************/
A_CLI_Config_Parser_PugiXML::A_CLI_Config_Parser_PugiXML( const std::string& config_pathname )
  : m_class_name("A_CLI_Config_Parser_PugiXML"),
    m_config_pathname(config_pathname),
    m_is_valid(false)
{
    Parse();
}


/********************************************************/
/*          Parse the XML Configuration File            */
/********************************************************/
void A_CLI_Config_Parser_PugiXML::Parse()
{
    /// Queries
    const std::string ROOT_QUERY           = "cli_manager_configuration";
    const std::string COMMAND_CONFIG_QUERY = "command_configuration";
    
    // Attributes
    const std::string PATH_ATTR            = "path";

    // Temp Variables
    std::string temp_str;
    
    // Create XML Document
    pugi::xml_document xmldoc;
    pugi::xml_parse_result result = xmldoc.load_file( m_config_pathname.c_str() );
    
    if( result == false )
    {
        LOG_ERROR( "CLI Config-File parsed with errors. Details: " + std::string(result.description()));
        return;
    }
    
    
    // Get the root node
    pugi::xml_node root_node = xmldoc.child(ROOT_QUERY.c_str());
    
    // Check the node
    if( root_node == pugi::xml_node() ){
        LOG_ERROR("Root Node Cannot Be Null!");
        return;
    }
    
    
    // Parse the Logging Config Nodes
    Parse_Log_Node( root_node );
    
    // Parse the Connection-Manager Nodes
    Parse_Connection_Manager_Nodes( root_node );
    
    // Parse the CLI Node
    Parse_CLI_Node( root_node );

    // Build the Command-Parser
    auto cmd_config_path = root_node.child( COMMAND_CONFIG_QUERY.c_str() ).attribute( PATH_ATTR.c_str()).as_string();
    auto command_parser = CMD::A_Command_Parser_Factory::Initialize( cmd_config_path,
                                                                     alias_support,
                                                                     alias_path,
                                                                     variable_support,
                                                                     variable_path );


    // Parse the Event-Manager-Config
    EVT::Event_Manager_Config event_mgr_config = Parse_Event_Manager_Node( root_node );
    

    // Build the CLI-Manager
    m_cli_manager_config = A_CLI_Manager_Configuration( m_connection_manager_configs,
                                                        m_render_driver_configs,
                                                        command_parser,
                                                        command_queue_config,
                                                        event_mgr_config );
    
    // Set valid
    m_is_valid = m_cli_manager_config.Is_Valid();
}


/***************************************************/
/*          Load the Logging Config Node           */
/***************************************************/
void A_CLI_Config_Parser_PugiXML::Parse_Log_Node( pugi::xml_node&  root_node )
{
    // Grab log node
    pugi::xml_node log_node = root_node.child("logging");

    // Default inputs
    bool logging_enabled;
    bool logfile_enabled = false;
    std::string log_path;
    std::string log_severity;
    
    // Get the Parameters
    logging_enabled  = log_node.attribute("enabled").as_bool("true");
    log_path         = log_node.attribute("log_path").as_string("");
    log_severity     = log_node.attribute("log_level").as_string("debug");

    
    // Check log path
    if( log_path.size() > 0 ){
        logfile_enabled = true;
    }
    
    // Initialize the Logger
    if( logging_enabled == true )
    {
        UTILS::Initialize_Logger( log_severity,
                                  log_path,
                                  logfile_enabled );
    }
}


/********************************************************/
/*          Parse the Connection-Manager Nodes          */
/********************************************************/
void A_CLI_Config_Parser_PugiXML::Parse_Connection_Manager_Nodes( pugi::xml_node& root_node )
{
    // Node Queries
    const std::string CONNECTION_CONFIGS_QUERY = "connection_configuration";
    const std::string CONNECTION_QUERY         = "connection";
    const std::string PORT_QUERY               = "listening_port";
    const std::string WINDOW_SIZE_QUERY        = "window_size";
    const std::string READ_TIMEOUT_QUERY       = "read_timeout_sleep_time";
    const std::string MAX_CONN_QUERY           = "max_connections";

    // Attribute Queries
    const std::string CONN_TYPE_ATTR           = "conn_type";
    const std::string SESSION_TYPE_ATTR        = "session_type";
    const std::string VALUE_ATTR               = "value";
    const std::string MICROSECONDS_ATTR        = "microseconds";

    
    // Misc Vars
    std::string temp_str;


    // Get the Connection Node
    auto configs_node = root_node.child(CONNECTION_CONFIGS_QUERY.c_str());

    // Iterate over connection nodes
    for( auto connection_node = configs_node.child(CONNECTION_QUERY.c_str()); 
         connection_node;
         connection_node = connection_node.next_sibling(CONNECTION_QUERY.c_str()))
    {
        // Get the Connection-Type
        temp_str = connection_node.attribute(CONN_TYPE_ATTR.c_str()).as_string();
        auto connection_type = CORE::StringToConnectionType( temp_str );
        if( connection_type == CORE::ConnectionType::UNKNOWN ){
            LOG_ERROR("Unsupported Connection-Type: " + temp_str);
            continue;
        }

        
        // Get the session-type
        temp_str = connection_node.attribute(SESSION_TYPE_ATTR.c_str()).as_string();
        auto session_type = CORE::StringToSessionType( temp_str );
        if( session_type == CORE::SessionType::UNKNOWN ){
            LOG_ERROR("Unsupported Session-Type: " + temp_str);
            continue;
        }
    
        
        // Get the Port-Number
        auto listening_port = connection_node.child(PORT_QUERY.c_str()).attribute(VALUE_ATTR.c_str()).as_int(-1);
        if( listening_port < 1000 ){
            LOG_ERROR("Unsupported Listening-Port: " + std::to_string(listening_port));
            continue;
        }

        
        // Read-Timeout
        auto timeout_val = connection_node.child(READ_TIMEOUT_QUERY.c_str()).attribute(MICROSECONDS_ATTR.c_str()).as_llong(-1);
        if( timeout_val < 0 ){
            LOG_ERROR("Unsupported Read-Sleep timeout: " + std::to_string(timeout_val));
            continue;
        }
        std::chrono::microseconds read_sleep_timeout( timeout_val );
        
        
        // Max-Connections
        auto max_connections = connection_node.child(MAX_CONN_QUERY.c_str()).attribute(VALUE_ATTR.c_str()).as_int(-1);
        if( max_connections <= 0 ){
            LOG_ERROR("Unsupported Max-Connections: " + std::to_string(max_connections));
            continue;
        }


        // If JSON, continue
        if( connection_type == CORE::ConnectionType::SOCKET && 
            session_type == CORE::SessionType::JSON )
        {
            auto session_instance_config = std::make_shared<A_Socket_Instance_Config_JSON>( read_sleep_timeout );
            
            // Add to Config List
            auto config_ptr = std::make_shared<A_Connection_Manager_Socket_Config>( listening_port,
                                                                                    max_connections,
                                                                                    session_instance_config );
            m_connection_manager_configs.push_back( config_ptr );
        }

        // If Telnet, continue
        else if( connection_type == CORE::ConnectionType::SOCKET && 
                 session_type == CORE::SessionType::TELNET )
        {
            auto session_instance_config = std::make_shared<A_Socket_Instance_Config_Telnet>( read_sleep_timeout );
            
            // Add to Config List
            auto config_ptr = std::make_shared<A_Connection_Manager_Socket_Config>( listening_port,
                                                                                    max_connections,
                                                                                    session_instance_config );
            m_connection_manager_configs.push_back( config_ptr );

        }

        // Otherwise, error
        else 
        {
            LOG_ERROR("Unsupported Session-Type: " + CORE::SessionTypeToString(session_type));
            continue;
        }

    }

}


/************************************************************/
/*          Parse the Event-Manager Configuration           */
/************************************************************/
EVT::Event_Manager_Config  A_CLI_Config_Parser_PugiXML::Parse_Event_Manager_Node(pugi::xml_node &root_node)
{
    // Queries
    const std::string EVENT_QUERY        = "event_manager";
    const std::string MAX_SIZE_QUERY     = "event_queue_max_capacity";
    const std::string QUEUE_THREAD_QUERY = "work_queue_thread_count";
    
    // Get the event-node
    auto event_node = root_node.child(EVENT_QUERY.c_str());
    
    // Make sure the node exists
    if( event_node == pugi::xml_node() ){
        throw std::runtime_error( EVENT_QUERY + " node does not exist.");
    }
    
    // Make sure the name is right
    if( std::string(event_node.name()) != EVENT_QUERY ){
        throw std::runtime_error("Expected " + EVENT_QUERY + " node, but got " + std::string(event_node.name()) + " instead.");
    }
    
    ///////////////////////////////////////////////
    //    Get the event queue size
    pugi::xml_node event_queue_max_cap_node = event_node.child(MAX_SIZE_QUERY.c_str());
    if( event_queue_max_cap_node == pugi::xml_node() ){
        throw std::runtime_error(MAX_SIZE_QUERY + " node was not found.");
    }
    int event_queue_max_cap = event_queue_max_cap_node.attribute("value").as_int(-1);
    if( event_queue_max_cap <= 0 ){
        throw std::runtime_error( MAX_SIZE_QUERY + " value cannot be less than 1.");
    }
    
    ///////////////////////////////////////////////
    //    Get the work queue size
    pugi::xml_node event_work_queue_node = event_node.child(QUEUE_THREAD_QUERY.c_str());
    if( event_work_queue_node == pugi::xml_node() ){
        throw std::runtime_error(QUEUE_THREAD_QUERY + " node was not found.");
    }
    int thread_count = event_work_queue_node.attribute("value").as_int(-1);
    if( thread_count < 1 ){
        throw std::runtime_error(QUEUE_THREAD_QUERY + " value cannot be less than 1.");
    }
    
    
    // Create the return object
    return EVT::Event_Manager_Config( event_queue_max_cap,
                                      thread_count );
}


} // End of XML    Namespace
} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

