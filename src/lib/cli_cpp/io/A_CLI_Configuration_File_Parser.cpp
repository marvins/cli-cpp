/**
 * @file    A_CLI_Configuration_File_Parser.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_CLI_Configuration_File_Parser.hpp"

// CLI Libraries
#include "../cli/A_Connection_Manager_Socket_Config.hpp"
#include "../cmd/A_Command_Queue_Config.hpp"
#include "../cmd/A_Command_Parser_Factory.hpp"
#include "../thirdparty/pugixml.hpp"
#include "../utility/Log_Utilities.hpp"
#include "CLI_Configuration_File_Parser_Utilities.hpp"


// C++ Standard Libraries
#include <iostream>
#include <sstream>
#include <stdexcept>


// Boost Libraries
#include <boost/filesystem.hpp>


namespace CLI{
namespace IO{
namespace CONFIG{

/************************************/
/*          Constructor             */
/************************************/
A_CLI_Configuration_File_Parser::A_CLI_Configuration_File_Parser( const std::string& config_path )
  : m_class_name("A_CLI_Configuration_File_Parser"),
    m_config_pathname(config_path),
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
    
    // Create the pugixml parser
    XML::A_CLI_Config_Parser_PugiXML pugi_parser(m_config_pathname);

    m_is_valid = pugi_parser.Is_Valid();
    if( m_is_valid )
    {
        m_current_configuration = pugi_parser.Get_CLI_Manager_Config();
    }
}


/**************************************************/
/*          Write the Configuration File          */
/**************************************************/
void A_CLI_Configuration_File_Parser::Write()
{

}


} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

