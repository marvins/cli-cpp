#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/22/2015
#

#-----------------------------------#
#-      Utility Module Sources     -#
#-----------------------------------#
set( LIB_CLI_UTILITY_MODULE_SOURCES
     An_ASCII_Print_Table.cpp
     Filesystem_Utilities.cpp
     Log_Utilities.cpp
     String_Utilities.cpp
     System_Utilities.cpp
     Telnet_Utilities.cpp
)


#-----------------------------------#
#-      Command Module Headers     -#
#-----------------------------------#
set( LIB_CLI_UTILITY_MODULE_HEADERS
     An_ASCII_Print_Table.hpp
     ANSI_Utilities.hpp
     Filesystem_Utilities.hpp
     Log_Utilities.hpp
     Stopwatch.hpp
     String_Utilities.hpp
     System_Utilities.hpp
     Telnet_Utilities.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_UTILITY_OBJ
                OBJECT
                    ${LIB_CLI_UTILITY_MODULE_HEADERS}
                    ${LIB_CLI_UTILITY_MODULE_SOURCES}
)

