/**
 * @file    TEST_Filesystem_Utilities.cpp
 * @author  Marvin Smith
 * @date    7/20/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/utility/Filesystem_Utilities.hpp>

/*******************************************/
/*       Test the File Exists Command      */
/*******************************************/
TEST( Filesystem_Utilities, Path_Exists )
{
    /////////////////////////////////////
    // Test 01 - Path that does not exist
    ASSERT_FALSE( CLI::FS::Path_Exists(""));
    ASSERT_FALSE( CLI::FS::Path_Exists( "file-i-know-does-not-exist.") );

    
    /////////////////////////////////////
    // Test 02 - Path that does exist
#ifdef __UNIX__
    ASSERT_TRUE( CLI::FS::Path_Exists("/etc/hosts" ) );
    ASSERT_TRUE( CLI::FS::Path_Exists("CMakeLists.txt") );
#endif

}


