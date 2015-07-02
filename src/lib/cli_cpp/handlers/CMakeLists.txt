#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/2/2015
#

#-----------------------------------#
#-      Handler Module Sources     -#
#-----------------------------------#
set( LIB_CLI_HANDLERS_MODULE_SOURCES
   A_CLI_Resize_Command_Response_Handler.cpp 
)


#-----------------------------------#
#-      Handler Module Headers     -#
#-----------------------------------#
set( LIB_CLI_HANDLERS_MODULE_HEADERS
   A_CLI_Resize_Command_Response_Handler.hpp 
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_HANDLERS_OBJ
                OBJECT
                    ${LIB_CLI_HANDLERS_MODULE_HEADERS}
                    ${LIB_CLI_HANDLERS_MODULE_SOURCES}
)

