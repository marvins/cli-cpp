#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/22/2015
#

#--------------------------------------#
#-        Render Module Sources       -#
#--------------------------------------#
set( LIB_CLI_RENDER_MODULE_SOURCES
    A_Render_Driver_Context_ASCII.cpp
    A_Render_Driver_Context_Base.cpp
    A_Render_Driver_Context_Factory.cpp
    A_Render_Driver_Context_NCurses.cpp
    A_Render_Manager_ASCII.cpp
    A_Render_Manager_Base.cpp
    A_Render_Manager_NCurses.cpp
    A_Render_Manager_Factory.cpp
    A_Render_State.cpp
    ascii/An_ASCII_Help_Menu.cpp
    ascii/An_ASCII_History_Window.cpp
    ascii/An_ASCII_History_Window_Configuration.cpp
)


#-------------------------------#
#-      CLI Module Headers     -#
#-------------------------------#
set( LIB_CLI_RENDER_MODULE_HEADERS
    A_Render_Driver_Context_ASCII.hpp
    A_Render_Driver_Context_Base.hpp
    A_Render_Driver_Context_Factory.hpp
    A_Render_Driver_Context_NCurses.hpp
    A_Render_Manager_ASCII.hpp
    A_Render_Manager_Base.hpp
    A_Render_Manager_NCurses.hpp
    A_Render_Manager_Factory.hpp
    A_Render_State.hpp
    ascii/An_ASCII_Help_Menu.hpp
    ascii/An_ASCII_History_Window.hpp
    ascii/An_ASCII_History_Window_Configuration.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_RENDER_OBJ
                OBJECT
                    ${LIB_CLI_RENDER_MODULE_HEADERS}
                    ${LIB_CLI_RENDER_MODULE_SOURCES}
)

