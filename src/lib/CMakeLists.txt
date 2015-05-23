#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/20/2015
#
#    Purpose:  Constructs the CLI-CPP Library Project
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



#--------------------------------------#
#-       Find NCurses Libraries       -#
#--------------------------------------#
find_package( Curses REQUIRED )

include_directories(${CURSES_INCLUDE_DIR})

#-------------------------------------#
#-     Import the CLI Libraries      -#
#-------------------------------------#
add_subdirectory(cli_cpp)

#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( cli_cpp SHARED
             $<TARGET_OBJECTS:LIB_CLI_CORE_OBJ>
             $<TARGET_OBJECTS:LIB_CLI_CLI_OBJ>
             $<TARGET_OBJECTS:LIB_CLI_CMD_OBJ>
             $<TARGET_OBJECTS:LIB_CLI_RENDER_OBJ>
             $<TARGET_OBJECTS:LIB_CLI_THIRDPARTY_OBJ>
             $<TARGET_OBJECTS:LIB_CLI_UTILITY_OBJ>
)


#------------------------------------#
#-      Link Other Libraries        -#
#------------------------------------#
target_link_libraries( cli_cpp 
                       ${Boost_LIBRARIES}
                       ${CURSES_LIBRARIES} 
                       pthread )


