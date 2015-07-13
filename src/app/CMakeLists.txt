#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/20/2015
#
#    Purpose:  Constructs the CLI-CPP Sample App Project
#


#   Configure C++11
set( CMAKE_CXX_FLAGS "-std=c++11 -Wall" )

#---------------------------------#
#-     Change the Output Path    -#
#---------------------------------#
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
SET( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )


#----------------------------------#
#-    Define our demo sources     -#
#----------------------------------#
set( CLI_APP_SOURCES
     main.cpp
     cli/A_Netstat_Command_Response_Handler.cpp
     cli/A_Network_Asset_Command_Response_Handler.cpp
     cli/A_Ping_Command_Response_Handler.cpp
     cli/A_System_Command_Response_Handler.cpp
     core/State_Manager.cpp
     render/A_Network_Status_Render_Window.cpp
     utils/Init_Utilities.cpp
     utils/Network_Scanner.cpp
     utils/System_Utilities.cpp
)

#----------------------------------#
#-    Define our demo headers     -#
#----------------------------------#
set( CLI_APP_HEADERS
     cli/A_Netstat_Command_Response_Handler.hpp
     cli/A_Network_Asset_Command_Response_Handler.hpp
     cli/A_Ping_Command_Response_Handler.hpp
     cli/A_System_Command_Response_Handler.hpp
     core/State_Manager.hpp
     render/A_Network_Status_Render_Window.hpp
     utils/Init_Utilities.hpp
     utils/Network_Scanner.hpp
     utils/System_Utilities.hpp
)

#----------------------------------#
#-      Include the library       -#
#----------------------------------#
include_directories(../lib)

#----------------------------------#
#-      Build the Executable      -#
#----------------------------------#
add_executable( cli-network-tester
                ${CLI_APP_SOURCES}
                ${CLI_APP_HEADERS}
)


#-------------------------------------#
#-      Link Required Libraries      -#
#-------------------------------------#
target_link_libraries( cli-network-tester 
                       cli_cpp
                     )


