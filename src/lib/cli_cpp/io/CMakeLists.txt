#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    6/30/2015
#

#------------------------------#
#-      IO Module Sources     -#
#------------------------------#
set( LIB_CLI_IO_MODULE_SOURCES
     CLI_Script_Loader.cpp
)


#------------------------------#
#-      IO Module Headers     -#
#------------------------------#
set( LIB_CLI_IO_MODULE_HEADERS
     CLI_Script_Loader.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_IO_OBJ
                OBJECT
                    ${LIB_CLI_IO_MODULE_HEADERS}
                    ${LIB_CLI_IO_MODULE_SOURCES}
)

