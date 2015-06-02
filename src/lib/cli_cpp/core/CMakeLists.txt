#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/22/2015
#

#--------------------------------#
#-      Core Module Sources     -#
#--------------------------------#
set( LIB_CLI_CORE_MODULE_SOURCES
     A_CLI_Event_Handler_Base.cpp
     A_Connection_Manager_Event_Handler.cpp
     A_Render_Manager_Event_Handler.cpp
     ConnectionType.cpp
     Event_Manager.cpp
)


#--------------------------------#
#-      Core Module Headers     -#
#--------------------------------#
set( LIB_CLI_CMD_MODULE_HEADERS
     A_CLI_Event_Handler_Base.hpp
     A_Connection_Manager_Event_Handler.hpp
     A_Render_Manager_Event_Handler.hpp
     ConnectionType.hpp
     Event_Manager.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_CORE_OBJ
                OBJECT
                    ${LIB_CLI_CORE_MODULE_HEADERS}
                    ${LIB_CLI_CORE_MODULE_SOURCES}
)

