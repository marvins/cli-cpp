/**
 * @file    A_Command_Parser_Factory.cpp
 * @author  Marvin Smith
 * @date    6/8/2015
*/
#include <gtest/gtest.h>

// CLI CPP Libraries
#include <cli_cpp/cmd/A_Command_Parser_Factory.hpp>


/*****************************************************************/
/*     Test the CLI Parser Factory on an invalid config path     */
/*****************************************************************/
TEST( A_Command_Parser_Factory, Initialize_invalid_config_path )
{
    // Define an invalid configuration file
    std::string config_path = "path_that_doesnt_exist.xml";

    // Create the parser
    CLI::CMD::A_Command_Parser::ptr_t parser = CLI::CMD::A_Command_Parser_Factory::Initialize( config_path );

    // Make sure it is null
    ASSERT_EQ( parser, nullptr );

}

