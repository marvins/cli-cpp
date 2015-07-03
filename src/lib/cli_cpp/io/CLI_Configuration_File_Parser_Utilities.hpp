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


} // End of XML    Namespace
} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

#endif
