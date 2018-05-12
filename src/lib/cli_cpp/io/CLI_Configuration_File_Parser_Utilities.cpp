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


/**************************************************************/
/*          Load the Event Manager XML Config Node            */
/**************************************************************/
EVT::Event_Manager_Config  Load_Event_Manager_Config_XML_Node( pugi::xml_node& event_node )
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

/***************************************************/
/*          Load the Logging Config Node           */
/***************************************************/
bool Load_Logging_Config_XML_Node( pugi::xml_node&    root_node,
                                   bool const&        create_if_missing,
                                   bool&              logging_enabled,
                                   std::string&       log_path,
                                   std::string&       log_severity,
                                   bool&              logfile_enabled )
{
    // Grab log node
    pugi::xml_node log_node = root_node.child("logging");

    // Default inputs
    bool def_log_enabled;
    std::string def_log_path;
    std::string def_log_sev;
    logfile_enabled = false;

    // If the create if missing flag is present, then create
    if( create_if_missing == true )
    {
        def_log_enabled = logging_enabled;
        def_log_path    = log_path;
        def_log_sev     = log_severity;

        // Check if exists
        if( log_node == pugi::xml_node() ){
            log_node = root_node.append_child(pugi::xml_node_type::node_element);
            log_node.set_name("logging");
        }
    }
    // otherwise, if the node does not exist, then return false
    else if( create_if_missing == false &&
             log_node == pugi::xml_node() )
    {
        return false;
    }

    // Finally, if false, just continue
    else{
        def_log_enabled = false;
        def_log_path    = "";
        def_log_sev     = "info";
    }

    logging_enabled  = log_node.attribute("enabled").as_bool(def_log_enabled);
    log_path         = log_node.attribute("log_path").as_string(def_log_path.c_str());
    log_severity     = log_node.attribute("log_level").as_string(def_log_sev.c_str());

    // Check if the nodes exist and we need to create if missing
    if( create_if_missing == true )
    {
        if( log_node.attribute("enabled") == pugi::xml_attribute() ){
            log_node.append_attribute("enabled").set_value(def_log_enabled);
        }
        if( log_node.attribute("log_path") == pugi::xml_attribute() ){
            log_node.append_attribute("log_path").set_value(def_log_path.c_str());
        }
        if( log_node.attribute("log_level") == pugi::xml_attribute() ){
            log_node.append_attribute("log_level").set_value(def_log_sev.c_str());
        }
    }

    // Check log path
    if( log_path.size() > 0 ){
        logfile_enabled = true;
    }

    // Return success
    return true;
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
    
    

        // Grab the window rows
        window_rows = socket_config_node.child("window-size").attribute("rows").as_int();
        window_cols = socket_config_node.child("window-size").attribute("cols").as_int();

        // Get the port number
        int portno = socket_config_node.child("listening-port").attribute("value").as_int();
        
        // Get the timeout time
        int64_t sleep_time  = socket_config_node.child("read-timeout-sleep-time").attribute("microseconds").as_int(500000);
        int max_connections = socket_config_node.child("max-connections").attribute("value").as_int(1);
        
        // Get the Session-Type
        SessionType session_type = StringToSessionType( )
        
        // Create the configuration
        connection_manager_config = std::make_shared<A_Connection_Manager_Socket_Config>( portno,
                                                                                          sleep_time,
                                                                                          max_connections );
    }
    

    
    return true;
}


} // End of XML    Namespace
} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

