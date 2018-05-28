/**
 * @file    TEST_A_CLI_Configuration_File_Parser.cpp
 * @author  Marvin Smith
 * @date    5/10/2018
 */
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/io/A_CLI_Configuration_File_Parser.hpp>
#include <cli_cpp/utility/Log_Utilities.hpp>

// C++ Libraries
#include <iostream>


/**************************************************/
/*          Test the Parser (Valid File)          */
/**************************************************/
TEST( A_CLI_Configuration_File_Parser, Constructor_Valid_Path )
{
    // Config Pathname
    const std::string config_path = "data/CLI_Manager_Configuration.xml";
    
    // Create a Config-Parser
    auto parser = CLI::IO::CONFIG::A_CLI_Configuration_File_Parser( config_path );
   
    
    // Log the config
   auto cli_config = parser.Get_CLI_Manager_Configuration();
    LOG_FUNC_TRACE(cli_config.To_Log_String());
    
    // Check the validity
    ASSERT_TRUE( parser.Is_Valid() );
    
    
}
