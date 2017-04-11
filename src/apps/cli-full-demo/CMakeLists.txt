#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    10/26/2016
#
#    Purpose:  Constructs the CLI-CPP Sample Full App Project
#


#   Configure C++11
set( CMAKE_CXX_FLAGS "-std=c++11 -Wall" )

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

if( Boost_FOUND )
    message("Boost Found")
    message("Boost Include Dirs: ${Boost_INCLUDE_DIRS}")
endif()

#----------------------------------#
#-    Define our demo sources     -#
#----------------------------------#
set( CLI_FULL_APP_SOURCES
     main.cpp
     core/State_Manager.cpp
     handlers/A_User_Session_Event_Handler.cpp
     handlers/A_System_Command_Response_Handler.cpp
     render/A_User_Status_Render_Window.cpp
     utils/Init_Utilities.cpp
)     


#----------------------------------#
#-    Define our demo headers     -#
#----------------------------------#
set( CLI_FULL_APP_HEADERS
     core/State_Manager.hpp
     handlers/A_User_Session_Event_Handler.hpp
     handlers/A_System_Command_Response_Handler.hpp
     render/A_User_Status_Render_Window.hpp
     utils/Init_Utilities.hpp
)


#----------------------------------#
#-      Include the library       -#
#----------------------------------#
include_directories(../../lib)

#----------------------------------#
#-      Build the Executable      -#
#----------------------------------#
add_executable( cli-full-demo
                ${CLI_FULL_APP_SOURCES}
                ${CLI_FULL_APP_HEADERS}
)


#-------------------------------------#
#-      Link Required Libraries      -#
#-------------------------------------#
target_link_libraries( cli-full-demo
                       cli_cpp
                     )


