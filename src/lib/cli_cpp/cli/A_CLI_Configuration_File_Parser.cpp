/**
 * @file    A_CLI_Configuration_File_Parser.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_CLI_Configuration_File_Parser.hpp"

// CLI Libraries
#include "A_Connection_Manager_Local_Config.hpp"
#include "A_Connection_Manager_Socket_Config.hpp"
#include "../cmd/A_Command_Parser_Factory.hpp"
#include "../thirdparty/pugixml.hpp"
#include "../utility/Log_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>
#include <sstream>

// Boost Libraries
#include <boost/filesystem.hpp>

namespace CLI{


/************************************/
/*          Constructor             */
/************************************/
A_CLI_Configuration_File_Parser::A_CLI_Configuration_File_Parser( const std::string& config_path )
  : m_class_name("A_CLI_Configuration_File_Parser"),
    m_config_pathname(config_path),
    m_current_configuration(A_CLI_Manager_Configuration(CORE::ConnectionType::LOCAL)),
    m_is_valid(false)
{
    // Parse the file
    Parse_Configuration_File();
}


/********************************************/
/*      Parse the Configuration File        */
/********************************************/
void A_CLI_Configuration_File_Parser::Parse_Configuration_File()
{

    /// List of queries
    const std::string CONNECTION_TYPE_QUERY   = "connection-type";
    const std::string COMMAND_CONFIG_NODE     = "command-configuration";
    const std::string LOGGING_QUERY           = "logging";
    const std::string CLI_CONFIG_QUERY        = "cli";
    const std::string CLI_TITLE_QUERY         = "title";
    const std::string CLI_COMMAND_QUEUE_QUERY = "command-queue"; 

    // Temp Variables
    std::string temp_str;
    int temp_int;

    // Create XML Document
    pugi::xml_document xmldoc;
    pugi::xml_parse_result result = xmldoc.load_file( m_config_pathname.c_str() );

    if( result == false ){
        std::stringstream sin;
        sin << "error: " << __FILE__ << ", Line: " << __LINE__ << ". CLI Configuration File parsed with errors. Details: " << result.description();
        std::cerr << sin.str() << std::endl;
        return;
    }

    
    // Get the root node
    pugi::xml_node root_node = xmldoc.child("cli-manager-configuration");

    // Check the node
    if( root_node == pugi::xml_node() ){ return; }

    // Get the logging node
    pugi::xml_node log_node = root_node.child(LOGGING_QUERY.c_str());

    // Get the parameters
    bool        log_enabled = log_node.attribute("enabled").as_bool(false);
    std::string log_path    = log_node.attribute("log_path").as_string();
    std::string log_severity = log_node.attribute("log_level").as_string("info");

    if( log_enabled == true ){
        UTILS::Initialize_Logger( log_severity, log_path );
    }


    // Check the connection type
    CORE::ConnectionType cli_conn_type = CORE::StringToConnectionType( root_node.child(CONNECTION_TYPE_QUERY.c_str()).attribute("value").as_string());
    if( cli_conn_type == CORE::ConnectionType::UNKNOWN ){
        std::stringstream sin;
        sin << "error: " << __FILE__ << ", Line: " << __LINE__ << ". CLI Connection Type value is invalid.";
        std::cerr << sin.str() << std::endl;
        return;
    }
    m_current_configuration.Set_Connection_Type( cli_conn_type );

    
    // If we are Local, then load the local configuration
    if( cli_conn_type == CORE::ConnectionType::LOCAL ){

        // Create the local configuration
        m_connection_manager_config = std::make_shared<A_Connection_Manager_Local_Config>();

        // Set the configuration
        m_current_configuration.Set_Connection_Manager_Config( m_connection_manager_config );
    }
    else if( cli_conn_type == CORE::ConnectionType::SOCKET ){

        // Socket Config
        pugi::xml_node socket_config_node = root_node.child("socket-configuration");

        // Get the port number
        int portno = socket_config_node.child("listening-port").attribute("value").as_int();

        // Create the configuration
        m_connection_manager_config = std::make_shared<A_Connection_Manager_Socket_Config>( portno );
        m_current_configuration.Set_Connection_Manager_Config( m_connection_manager_config );

        // set the window size
        m_current_configuration.Set_Socket_Window_Cols( socket_config_node.child("window-size").attribute("cols").as_int(100));
        m_current_configuration.Set_Socket_Window_Rows( socket_config_node.child("window-size").attribute("rows").as_int(20));
    }

    // Get the Command Parser config file
    temp_str = root_node.child(COMMAND_CONFIG_NODE.c_str()).attribute("path").as_string();
    
    // make sure it exists
    if( boost::filesystem::exists( temp_str ) == false ){
        std::cerr << "error:  " << temp_str << " does not exist." << std::endl;
        return;
    }

    // Parse the command file
    CMD::A_Command_Parser::ptr_t command_parser = CMD::A_Command_Parser_Factory::Initialize( temp_str );

    // Make sure the parser is not null
    if( command_parser == nullptr ){
        std::cerr << "error: " << temp_str << " parsed with errors." << std::endl;
        return;
    }
    else{
        // Set the parser
        m_current_configuration.Set_Command_Parser(command_parser);
    }

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
    m_current_configuration.Set_Command_Queue_Max_Size( temp_int );

    // Set valid
    m_is_valid = true;
}



} // End of CLI Namespace

