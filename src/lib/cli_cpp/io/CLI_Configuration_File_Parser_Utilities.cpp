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
    const std::string ROOT_QUERY    = "cli_manager_configuration";
    
    // Temp Variables
    std::string temp_str;
    int temp_int;
    
    // Create XML Document
    pugi::xml_document xmldoc;
    pugi::xml_parse_result result = xmldoc.load_file( m_config_pathname.c_str() );
    
    if( result == false )
    {
        LOG_TRACE( "CLI Config-File parsed with errors. Details: " + std::string(result.description()));
        return;
    }
    
    
    // Get the root node
    pugi::xml_node root_node = xmldoc.child(ROOT_QUERY.c_str());
    
    // Check the node
    if( root_node == pugi::xml_node() ){
        LOG_TRACE("Root Node Cannot Be Null!");
        return;
    }
    
    
    // Log the log configuration
    Parse_Log_Node( root_node );
    
    
    // Parse the Event-Manager-Config
    EVT::Event_Manager_Config event_mgr_config = Parse_Event_Manager_Node( root_node );
    
    
   
    
    
    // Configure the connection information
    auto connections_node = xmldoc.child(CONNECTIONS_QUERY.c_str());
    for( auto connection_node : connections_node.children(CONNECTION_QUERY.c_str()))
    {
        A_Connection_Manager_Base_Config::ptr_t  connection_manager_config;
        
        if( !Parse_Connection_Node( connection_node,
                                    true,
                                    connection_manager_config ) ){
            BOOST_LOG_TRIVIAL(error) << "Unable to load the Connection-Config.";
            return;
        }
        else
        {
            m_connection_manager_configs.push_back(connection_manager_config);
        }
    }
    
    
    // Set the connection manager config inside the CLI configuration
    if( m_connection_manager_configs.empty() )
    {
        BOOST_LOG_TRIVIAL(error) << "Unable to load the connection manager configurations. Currently empty.";
        return;
    }
    m_current_configuration.Set_Connection_Manager_Configs( m_connection_manager_configs );
    
    
    // Grab the CLI Node
    pugi::xml_node cli_node = root_node.child(CLI_CONFIG_QUERY.c_str());
    
    // Get the CLI title
    temp_str = cli_node.child(CLI_TITLE_QUERY.c_str()).attribute("value").as_string();
    if( temp_str == "" ){
        temp_str = "Console";
    }
    m_current_configuration.Set_CLI_Title( temp_str );
    
    
    // Get the CLI Command Queue Max Size
    temp_int = cli_node.child( CLI_COMMAND_QUEUE_QUERY.c_str()).attribute("max_size").as_int();
    if( temp_int <= 0 ){
        std::cerr << "CLI Command Queue Max Size must be > 0" << std::endl;
        return;
    }
    m_current_configuration.Set_Command_Queue_Config( CMD::A_Command_Queue_Config( temp_int ));
    
    
    // Get the redirect variables
    bool redirect_stdout = cli_node.child(CLI_REDIRECT_QUERY.c_str()).attribute("stdout").as_bool(false);
    bool redirect_stderr = cli_node.child(CLI_REDIRECT_QUERY.c_str()).attribute("stderr").as_bool(false);
    
    m_current_configuration.Set_Log_Window_Redirect_Flags( redirect_stdout,
                                                           redirect_stderr );
    
    // Grab the alias parameters
    pugi::xml_node alias_node = cli_node.child("alias-support");
    
    bool alias_support     = alias_node.attribute("enable").as_bool(false);
    std::string alias_path = alias_node.child("alias-list").attribute("pathname").as_string("");
    
    // Grab the Command Variable Parameters
    pugi::xml_node variable_node = cli_node.child("variable-support");
    
    bool variable_support     = variable_node.attribute("enable").as_bool(false);
    std::string variable_path = variable_node.child("variable-list").attribute("pathname").as_string("");
    
    // Parse the Async Message Timeout
    int async_refresh_time = cli_node.child("async-message-refresh-time").attribute("ms").as_int(-1);
    if( async_refresh_time < 0 )
    {
        async_refresh_time = 2000;
    }
    // Set config object
    m_current_configuration.Set_Async_Message_Refresh_Time(std::chrono::milliseconds(async_refresh_time));
    
    // Get the Command Parser config file
    temp_str = root_node.child(COMMAND_CONFIG_NODE.c_str()).attribute("path").as_string();
    
    
    // make sure it exists
    if( boost::filesystem::exists( temp_str ) == false ){
        std::cerr << "error:  " << temp_str << " does not exist." << std::endl;
        return;
    }
    
    // Parse the command file
    CMD::A_Command_Parser::ptr_t command_parser = CMD::A_Command_Parser_Factory::Initialize( temp_str,
                                                                                             alias_support, alias_path,
                                                                                             variable_support, variable_path );
    
    // Make sure the parser is not null
    if( command_parser == nullptr ){
        std::cerr << "error: " << temp_str << " parsed with errors." << std::endl;
        return;
    }
    else{
        // Set the parser
        m_current_configuration.Set_Command_Parser(command_parser);
    }
    
    
    // Load the Event-Manager Configuration
    pugi::xml_node event_node = root_node.child(EVENT_MANAGER_QUERY.c_str());
    m_event_manager_config = XML::Load_Event_Manager_Config_XML_Node( event_node );
    
    // Pass the event manager configuration to the cli manager config
    m_current_configuration.Set_Event_Manager_Config( m_event_manager_config );
    
    
    // Set valid
    m_is_valid = true;
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


/*********************************************************/
/*      Load the Connection Configuration XML Nodes      */
/*********************************************************/
bool Parse_Connection_Node( pugi::xml_node&                          root_node,
                            bool const&                              create_if_missing,
                            A_Connection_Manager_Base_Config::ptr_t& connection_manager_config )
{
    // Get the connection type
    CORE::ConnectionType connection_type = CORE::StringToConnectionType( root_node.attribute("conn_type").as_string());
    CORE::SessionType    session_type    = CORE::StringToSessionType( root_node.attribute("session_type").as_string());
    
    // Check If SOcket
    if( connection_type == CORE::ConnectionType::SOCKET )
    {
        // Grab the port number
        int port_number = root_node.child("listening-port").attribute("value").as_int();
        
        // Max Connections
        int max_connections = root_node.child("max-connections").attribute("value").as_int();
        
        
        // Check the session-type as telnet
        A_Socket_Instance_Config_Base::ptr_t instance_config;
        if( session_type == CORE::SessionType::TELNET )
        {
        
        }
        
        // Check if JSON
        else if( session_type == CORE::SessionType::JSON )
        {
        
        }
        
        // Otherwise, error
        else
        {
            std::stringstream sin;
            sin << "Unable to find valid Session-Type: " << std::string(root_node.attribute("session_type").as_string());
            CLI_LOG_FUNC( error, sin.str());
            return false;
        }
        
        // Create the Connection-Config
        connection_manager_config = std::make_shared<A_Connection_Manager_Socket_Config>( port_number,
                                                                                          max_connections,
                                                                                          instance_config );
    }
    
    // Otherwise, error
    else
    {
        std::stringstream sin;
        sin << "Unable to find Connection-Type: " << root_node.attribute("conn_type").as_string();
        
        CLI_LOG_FUNC( error, sin.str() );
    }
    

    
    return true;
}


/************************************************************/
/*          Parse the Event-Manager Configuration           */
/************************************************************/
EVT::Event_Manager_Config  A_CLI_Config_Parser_PugiXML::Parse_Event_Manager_Config(pugi::xml_node &root_node)
{
    // Make sure the node exists
    if( event_node == pugi::xml_node() ){
        throw std::runtime_error("event-manager node does not exist.");
    }
    
    // Make sure the name is right
    if( std::string(event_node.name()) != "event-manager" ){
        throw std::runtime_error("Expected event-manager node, but got " + std::string(event_node.name()) + " instead.");
    }
    
    ///////////////////////////////////////////////
    //    Get the event queue size
    pugi::xml_node event_queue_max_cap_node = event_node.child("event-queue-max-capacity");
    if( event_queue_max_cap_node == pugi::xml_node() ){
        throw std::runtime_error("event-queue-max-capacity node was not found.");
    }
    int event_queue_max_cap = event_queue_max_cap_node.attribute("value").as_int(-1);
    if( event_queue_max_cap <= 0 ){
        throw std::runtime_error("event-queue-max-capacity @value cannot be less than 1.");
    }
    
    ///////////////////////////////////////////////
    //    Get the work queue size
    pugi::xml_node event_work_queue_node = event_node.child("work-queue-thread-count");
    if( event_work_queue_node == pugi::xml_node() ){
        throw std::runtime_error("work-queue-thread-count node was not found.");
    }
    int thread_count = event_work_queue_node.attribute("value").as_int(-1);
    if( thread_count < 1 ){
        throw std::runtime_error("work-queue-thread-count @value cannot be less than 1.");
    }
    
    
    // Create the return object
    return EVT::Event_Manager_Config( event_queue_max_cap,
                                      thread_count );
}


} // End of XML    Namespace
} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

