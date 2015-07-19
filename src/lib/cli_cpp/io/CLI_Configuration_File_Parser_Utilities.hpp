/**
 * @file    CLI_Configuration_File_Parser_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef __CLI_CPP_IO_CONFIGURATION_FILE_PARSER_UTILITIES_HPP__
#define __CLI_CPP_IO_CONFIGURATION_FILE_PARSER_UTILITIES_HPP__

// CLI Libraries
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
 *
 * @return True if successful, false if failed.
*/
bool Load_Logging_Config_XML_Node( pugi::xml_node& root_node,
                                   bool const&     create_if_missing,
                                   bool&           logging_enabled,
                                   std::string&    log_path,
                                   std::string&    log_severity );
                                   


} // End of XML    Namespace
} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

#endif
