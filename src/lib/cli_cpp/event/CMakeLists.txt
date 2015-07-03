#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/2/2015
#

#---------------------------------#
#-      Event Module Sources     -#
#---------------------------------#
set( LIB_CLI_EVENT_MODULE_SOURCES
    A_CLI_Event_Handler_Base.cpp
    A_Connection_Manager_Event_Handler.cpp
    A_Render_Manager_Event_Handler.cpp
    An_Event_Queue.cpp
    Event_Manager.cpp
)


#---------------------------------#
#-      Event Module Headers     -#
#---------------------------------#
set( LIB_CLI_EVENT_MODULE_HEADERS
    ../event.hpp
    A_CLI_Event_Handler_Base.hpp
    A_Connection_Manager_Event_Handler.hpp
    A_Render_Manager_Event_Handler.hpp
    An_Event_Queue.hpp
    Event_Manager.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_EVENT_OBJ
                OBJECT
                    ${LIB_CLI_EVENT_MODULE_HEADERS}
                    ${LIB_CLI_EVENT_MODULE_SOURCES}
)

