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

