/**
 * @file    CLI_Configuration_File_Parser_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef __CLI_CPP_IO_CONFIGURATION_FILE_PARSER_UTILITIES_HPP__
#define __CLI_CPP_IO_CONFIGURATION_FILE_PARSER_UTILITIES_HPP__

// CLI Libraries
#include "../cli/A_Connection_Manager_Base_Config.hpp"
#include "../core/ConnectionType.hpp"
#include "../event/Event_Manager_Config.hpp"
#include "../thirdparty/pugixml.hpp"


namespace CLI{
namespace IO{
namespace CONFIG{
namespace XML{


/**
 * @brief Load the Event-Manager XML settings.
 *
 * @param[in] event_node Event-Manager configuration node.
 *
 * @return Event-Manager configuration object.
*/
EVT::Event_Manager_Config  Load_Event_Manager_Config_XML_Node( pugi::xml_node& event_node );


/**
 * @brief Load the Logging XML Settings
 *
 * If the create_if_missing flag is true, then the output arguments also will become the
 * default arguments should they be set.
 *
 * @param[in/out] root_node         Base node to get log node and then modify or read.
 * @param[in]     create_if_missing Create missing xml nodes in file.  If true, then the remaining args become the defaults.
 * @param[in/out] logging_enabled   Flag if we want to allow logging.
 * @param[in/out] log_path          Path to log file.
 * @param[in/out] log_severity      Logging severity.
 * @param[in/out] logfile_enabled   Flag if log file is allowed.
 *
 * @return True if successful, false if failed.
*/
bool Load_Logging_Config_XML_Node( pugi::xml_node& root_node,
                                   bool const&     create_if_missing,
                                   bool&           logging_enabled,
                                   std::string&    log_path,
                                   std::string&    log_severity,
                                   bool&           logfile_enabled );
                                   

/**
 * @brief Load the Connection XML Node
 *
 * @param[in/out] root_node         Base node to get connection information for.
 * @param[in]     create_if_missing Create the nodes in the xml node if missing.
 * @param[in/out] cli_conn_type     CLI Connection Type value.
 * @param[in/out] connection_manager_config Connection-Manager configuration options.
 * @param[in/out] window_rows       Number of CLI Window Rows.
 * @param[in/out] window_cols       Number of CLI Window Columns.
 *
 * @return True if successful, false otherwise.
*/
bool Load_Connection_Config_XML_Nodes( pugi::xml_node&                          root_node,
                                       bool const&                              create_if_missing,
                                       A_Connection_Manager_Base_Config::ptr_t& connection_manager_config );


} // End of XML    Namespace
} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

#endif
