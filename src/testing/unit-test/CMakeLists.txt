#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/20/2015
#
#    Purpose:  Constructs the CLI-CPP Unit-Test Project
#

#   Configure C++11
set( CMAKE_CXX_FLAGS "-std=c++11 -Wall -ldl" )

#---------------------------------#
#-     Change the Output Path    -#
#---------------------------------#
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
SET( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )

#-------------------------------------#
#-     Find Boost C++ Libraries      -#
#-------------------------------------#
ADD_DEFINITIONS(-DBOOST_LOG_DYN_LINK)
find_package( Boost REQUIRED
                COMPONENTS
                    system
                    filesystem
                    regex
                    log
                    thread
)
include_directories( ${Boost_INCLUDE_DIRS})




#-------------------------------------------#
#-      Define the GoogleTest Sources      -#
#-------------------------------------------#
set( GOOGLETEST_SOURCES
    thirdparty/googletest/include/gtest/gtest.h
    thirdparty/googletest/include/gtest/gtest-death-test.h
    thirdparty/googletest/include/gtest/gtest-message.h
    thirdparty/googletest/include/gtest/gtest-param-test.h
    thirdparty/googletest/include/gtest/gtest_pred_impl.h
    thirdparty/googletest/include/gtest/gtest-printers.h
    thirdparty/googletest/include/gtest/gtest_prod.h
    thirdparty/googletest/include/gtest/gtest-test-part.h
    thirdparty/googletest/include/gtest/gtest-spi.h
    thirdparty/googletest/include/gtest/gtest-typed-test.h
    thirdparty/googletest/include/gtest/internal/gtest-death-test-internal.h
    thirdparty/googletest/include/gtest/internal/gtest-filepath.h
    thirdparty/googletest/include/gtest/internal/gtest-internal.h
    thirdparty/googletest/include/gtest/internal/gtest-linked_ptr.h
    thirdparty/googletest/include/gtest/internal/gtest-param-util.h
    thirdparty/googletest/include/gtest/internal/gtest-param-util-generated.h
    thirdparty/googletest/include/gtest/internal/gtest-string.h
    thirdparty/googletest/include/gtest/internal/gtest-type-util.h
    thirdparty/googletest/include/gtest/internal/gtest-port.h
    thirdparty/googletest/src/gtest.cc
    thirdparty/googletest/src/gtest-death-test.cc
    thirdparty/googletest/src/gtest-filepath.cc
    thirdparty/googletest/src/gtest-internal-inl.h
    thirdparty/googletest/src/gtest-port.cc
    thirdparty/googletest/src/gtest-printers.cc
    thirdparty/googletest/src/gtest-test-part.cc
)
include_directories(thirdparty/googletest/include)
include_directories(thirdparty/googletest)

#--------------------------------------------#
#-      Include the CLI Library Headers     -#
#--------------------------------------------#
include_directories( "../../lib")
find_library( LIB_CLI_CPP
                NAMES
                    cli_cpp
                PATHS
                    ${CMAKE_BINARY_DIR}/lib
)

#--------------------------------------------#
#-      Define the Unit-Test Sources        -#
#--------------------------------------------#
set( CLI_CPP_TEST_SOURCES
        cmd/TEST_A_CLI_Command.cpp
        cmd/TEST_A_Command.cpp
        cmd/TEST_A_Command_Alias.cpp
        cmd/TEST_A_Command_Argument.cpp
        cmd/TEST_A_Command_Parser.cpp
        cmd/TEST_A_Command_Parser_Factory.cpp
        cmd/TEST_A_Command_Variable.cpp
        event/TEST_An_Event_Queue.cpp
        event/TEST_Event_Manager.cpp
        event/TEST_Event_Manager_Config.cpp
        io/TEST_A_CLI_Configuration_File_Parser.cpp
        render/TEST_A_Render_State_Factory.cpp
        utility/TEST_An_ASCII_Print_Table.cpp
        utility/TEST_Filesystem_Utilities.cpp
        utility/TEST_String_Utilities.cpp
        UNIT_TEST_ONLY/Command_Parser.hpp
        UNIT_TEST_ONLY/Command_Parser.cpp
)


#-----------------------------------------#
#-      Define the Library Headers       -#
#-----------------------------------------#
set( CLI_CPP_TEST_MAIN
    unit_test_main.cpp
)


#-----------------------------------#
#-      Build the Executable       -#
#-----------------------------------#
add_executable( cli_cpp_unit_tests
                ${CLI_CPP_TEST_MAIN}
                ${CLI_CPP_TEST_SOURCES}
                ${GOOGLETEST_SOURCES}
)

#------------------------------------#
#-      Link Other Libraries        -#
#------------------------------------#
target_link_libraries( cli_cpp_unit_tests 
                       cli_cpp
)
#${LIB_CLI_CPP}


