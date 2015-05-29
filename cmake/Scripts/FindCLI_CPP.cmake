#    File:     FindCLI_CPP.cmake
#    Author:   Marvin Smith
#    Date:     5/29/2015
#
#    Purpose: Enable discovery of CLI-CPP project by outside applications.
#
#   User-Defined Variables
#   CLI_CPP_LIB_DIR
#   CLI_CPP_INC_DIR
#
#   Variables Set By Script:
#
#   CLI_CPP_FOUND
#   CLI_CPP_INCLUDES
#   CLI_CPP_LIBRARIES
#


#
#   Look for shared object
#
find_library( CLI_CPP_LIBRARY
                cli_cpp
              PATHS
                ${CLI_CPP_LIB_DIR}
)

message("LIB: ${CLI_CPP_LIBRARY}")


#---------------------------------------------------#
#-      Make sure the shared object was found      -#
#---------------------------------------------------#
if( EXISTS ${CLI_CPP_LIBRARY} )
    SET( CLI_CPP_LIBRARIES ${CLI_CPP_LIBRARY} )
else()
    message("Unable to find Library.  Base: ${CLI_CPP_BASE}")
    unset(CLI_CPP_FOUND)
    return()
endif()

#-----------------------------------------#
#-            Look for includes          -#
#-----------------------------------------#
find_path( CLI_CPP_HPP 
            NAMES
                cli_cpp.hpp
            PATHS
                ${CLI_CPP_INC_DIR}
)
message("CLI_CPP_HPP ${CLI_CPP_HPP}")

#------------------------------------------------------------#
#-          Make sure the sub-directory is present          -#
#------------------------------------------------------------#
if( NOT EXISTS "${CLI_CPP_HPP}/cli_cpp" )
    message("Unable to find cli_cpp include directory.")
    unset( CLI_CPP_FOUND )    
    return()
else()
    set( CLI_CPP_INCLUDES ${CLI_CPP_HPP})
endif()


#--------------------------------#
#-       Configure Outputs      -#
#--------------------------------#
set( CLI_CPP_FOUND TRUE )

