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
    if( thread_count < 2 ){
        throw std::runtime_error("work-queue-thread-count @value cannot be less than 2.");
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
                                   std::string&       log_severity )
{
    // Grab log node
    pugi::xml_node log_node = root_node.child("logging");

    // Default inputs
    bool def_log_enabled;
    std::string def_log_path;
    std::string def_log_sev;

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
    // Return success
    return true;
}


/*********************************************************/
/*      Load the Connection Configuration XML Nodes      */
/*********************************************************/
bool Load_Connection_Config_XML_Nodes( pugi::xml_node&                          root_node,
                                       bool const&                              create_if_missing,
                                       CORE::ConnectionType&                    cli_conn_type,
                                       A_Connection_Manager_Base_Config::ptr_t& connection_manager_config,
                                       int&                                     window_rows,
                                       int&                                     window_cols )
{
    // Get the connection type node
    pugi::xml_node connection_type_node = root_node.child("connection-type");

    // If missing, check if we should create
    if( create_if_missing == true &&
        connection_type_node == pugi::xml_node() )
    {
        // Create the node
        connection_type_node = root_node.append_child("connection-type");

    }

    else if( create_if_missing == false &&
             connection_type_node == pugi::xml_node() )
    {
        return false;
    }

    // If not missing, continue
    else{

    }
    
    // Get the Connection Type
    CORE::ConnectionType def_cli_conn_type = CORE::ConnectionType::SOCKET;
    if( create_if_missing == true && 
        connection_type_node.attribute("value") == pugi::xml_attribute())
    {
        // Create node
        connection_type_node.append_attribute("value").set_value(CORE::ConnectionTypeToString(cli_conn_type).c_str());
    }
    else{
        cli_conn_type = CORE::StringToConnectionType(connection_type_node.attribute("value").as_string(CORE::ConnectionTypeToString(def_cli_conn_type).c_str()));
    }
    
    
    // Process the socket connection information 
    if( cli_conn_type == CORE::ConnectionType::SOCKET ){

        // Socket Config
        pugi::xml_node socket_config_node = root_node.child("socket-configuration");

        // Check if we need to create the node
        if( create_if_missing == true &&
            socket_config_node == pugi::xml_node() )
        {
            socket_config_node = root_node.append_child("socket-configuration");
            socket_config_node.append_attribute("value").set_value("SOCKET");
            
        }
        else if( create_if_missing == false &&
                 socket_config_node == pugi::xml_node() )
        {
            return false;
        }
        else{
        
        }
        
        
        // Check if the internal nodes are valid and the input config is not null
        if( create_if_missing == true &&
            connection_manager_config != nullptr )
        {
        
            // Create socket config
            A_Connection_Manager_Socket_Config::ptr_t socket_config = std::dynamic_pointer_cast<A_Connection_Manager_Socket_Config>(connection_manager_config);
                
            // Listening Port Configuration
            if( socket_config_node.child("listening-port") == pugi::xml_node() ){
                socket_config_node.append_child("listening-port").append_attribute("value").set_value(socket_config->Get_Port());
            }
            if( socket_config_node.child("listening-port").attribute("value") == pugi::xml_attribute() ){
                socket_config_node.child("listening-port").append_attribute("value").set_value(socket_config->Get_Port());
            }

            // Window Size
            if( socket_config_node.child("window-size") == pugi::xml_node() ){
                socket_config_node.append_child("window-size").append_attribute("rows").set_value(window_rows);
                socket_config_node.child("window-size").append_attribute("cols").set_value(window_cols);
            }
            if( socket_config_node.child("window-size").attribute("rows") == pugi::xml_attribute()){
                socket_config_node.child("window-size").append_attribute("rows").set_value(window_rows);
            }
            if( socket_config_node.child("window-size").attribute("cols") == pugi::xml_attribute()){
                socket_config_node.child("window-size").append_attribute("cols").set_value(window_cols);
            }

            // Read Timeout Sleep Time
            if( socket_config_node.child("read-timeout-sleep-time") == pugi::xml_node() ){
                socket_config_node.append_child("read-timeout-sleep-time").append_attribute("microseconds").set_value(socket_config->Get_Read_Timeout_Sleep_Microseconds());
            }
            if( socket_config_node.child("read-timeout-sleep-time").attribute("microseconds") == pugi::xml_attribute() ){
                socket_config_node.child("read-timeout-sleep-time").append_attribute("microseconds").set_value(socket_config->Get_Read_Timeout_Sleep_Microseconds());
            }
        }

        // Grab the window rows
        window_rows = socket_config_node.child("window-size").attribute("rows").as_int();
        window_cols = socket_config_node.child("window-size").attribute("cols").as_int();

        // Get the port number
        int portno = socket_config_node.child("listening-port").attribute("value").as_int();
        
        // Get the timeout time
        int64_t sleep_time  = socket_config_node.child("read-timeout-sleep-time").attribute("microseconds").as_int(500000);
        int max_connections = socket_config_node.child("max-connections").attribute("value").as_int(1); 
        
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

