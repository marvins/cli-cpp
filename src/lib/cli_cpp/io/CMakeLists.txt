#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    6/30/2015
#

#------------------------------#
#-      IO Module Sources     -#
#------------------------------#
set( LIB_CLI_IO_MODULE_SOURCES
     A_CLI_Configuration_File_Parser.cpp
     CLI_Script_Loader.cpp
     CLI_Configuration_File_Parser_Utilities.cpp
)


#------------------------------#
#-      IO Module Headers     -#
#------------------------------#
set( LIB_CLI_IO_MODULE_HEADERS
     A_CLI_Configuration_File_Parser.hpp
     CLI_Script_Loader.hpp
     CLI_Configuration_File_Parser_Utilities.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_IO_OBJ
                OBJECT
                    ${LIB_CLI_IO_MODULE_HEADERS}
                    ${LIB_CLI_IO_MODULE_SOURCES}
)

