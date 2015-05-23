#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/22/2015
#

#-----------------------------------#
#-      Command Module Sources     -#
#-----------------------------------#
set( LIB_CLI_CMD_MODULE_SOURCES
     A_CLI_Command.cpp
     A_Command.cpp
     A_Command_Argument.cpp
     A_Command_History.cpp
     A_Command_History_Entry.cpp
     A_Command_Parser.cpp
     A_Command_Parser_Factory.cpp
     A_Command_Queue.cpp
     A_Command_Result.cpp
     CommandArgumentType.cpp
     CommandParseStatus.cpp
)


#-----------------------------------#
#-      Command Module Headers     -#
#-----------------------------------#
set( LIB_CLI_CMD_MODULE_HEADERS
     A_CLI_Command.hpp
     A_Command.hpp
     A_Command_Argument.hpp
     A_Command_History.hpp
     A_Command_History_Entry.hpp
     A_Command_Parser.hpp
     A_Command_Parser_Factory.hpp
     A_Command_Queue.hpp
     A_Command_Result.hpp
     CommandArgumentType.hpp
     CommandParseStatus.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_CMD_OBJ
                OBJECT
                    ${LIB_CLI_CMD_MODULE_HEADERS}
                    ${LIB_CLI_CMD_MODULE_SOURCES}
)

