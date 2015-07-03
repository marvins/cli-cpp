#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/22/2015
#

#-------------------------------#
#-      CLI Module Sources     -#
#-------------------------------#
set( LIB_CLI_CLI_MODULE_SOURCES
     A_CLI_Manager.cpp
     A_CLI_Manager_Factory.cpp
     A_CLI_Manager_Configuration.cpp
     A_Command_Response_Handler_Base.cpp
     A_Connection_Manager_Base.cpp
     A_Connection_Manager_Base_Config.cpp
     A_Connection_Manager_Socket.cpp
     A_Connection_Manager_Socket_Config.cpp
     A_Connection_Manager_Factory.cpp
)


#-------------------------------#
#-      CLI Module Headers     -#
#-------------------------------#
set( LIB_CLI_CLI_MODULE_HEADERS
     A_CLI_Manager.hpp
     A_CLI_Manager_Factory.hpp
     A_CLI_Manager_Configuration.hpp
     A_Command_Response_Handler_Base.hpp
     A_Connection_Manager_Base.hpp
     A_Connection_Manager_Base_Config.hpp
     A_Connection_Manager_Socket.hpp
     A_Connection_Manager_Socket_Config.hpp
     A_Connection_Manager_Factory.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_CLI_OBJ
                OBJECT
                    ${LIB_CLI_CLI_MODULE_HEADERS}
                    ${LIB_CLI_CLI_MODULE_SOURCES}
)

