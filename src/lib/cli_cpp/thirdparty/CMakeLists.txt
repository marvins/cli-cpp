#
#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    5/22/2015
#

#--------------------------------------#
#-      ThirdParty Module Sources     -#
#--------------------------------------#
set( LIB_CLI_THIRDPARTY_MODULE_SOURCES
    ncurses/An_NCurses_Table.cpp
    ncurses/NCurses_Utilities.cpp
    pugixml/src/pugixml.cpp
)


#-------------------------------#
#-      CLI Module Headers     -#
#-------------------------------#
set( LIB_CLI_THIRDPARTY_MODULE_HEADERS
    ncurses/An_NCurses_Table.hpp
    ncurses/NCurses_Utilities.hpp
    pugixml.hpp
    pugixml/src/pugixml.hpp
    pugixml/src/pugiconfig.hpp
)


#--------------------------------#
#-      Build the Library       -#
#--------------------------------#
add_library( LIB_CLI_THIRDPARTY_OBJ
                OBJECT
                    ${LIB_CLI_THIRDPARTY_MODULE_HEADERS}
                    ${LIB_CLI_THIRDPARTY_MODULE_SOURCES}
)

