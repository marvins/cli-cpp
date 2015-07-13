#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/22/2015
#

#--------------------------------#
#-      Core Module Sources     -#
#--------------------------------#
set( LIB_CLI_CORE_MODULE_SOURCES
     ConnectionType.cpp
)


#--------------------------------#
#-      Core Module Headers     -#
#--------------------------------#
set( LIB_CLI_CMD_MODULE_HEADERS
     CLI_Event_Type.hpp
     ConnectionType.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_CORE_OBJ
                OBJECT
                    ${LIB_CLI_CORE_MODULE_HEADERS}
                    ${LIB_CLI_CORE_MODULE_SOURCES}
)

