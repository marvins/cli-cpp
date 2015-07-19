#    File:    CMakeLists.txt
#    Author:  Marvin Smith
#    Date:    7/13/2015
#
#    Purpose:  Constructs the CLI-CPP Configuration File Generator Application
#


#   Configure C++11
set( CMAKE_CXX_FLAGS "-std=c++11 -Wall" )

#---------------------------------#
#-     Change the Output Path    -#
#---------------------------------#
SET( EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin )
SET( LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib )


#----------------------------------#
#-    Define our demo sources     -#
#----------------------------------#
set( CLI_CPP_CONFIG_GENERATOR_SOURCES
     cli-cpp-config-generator.cpp
)


#-------------------------------------#
#-    Include the Path to CLI-CPP    -#
#-------------------------------------#
include_directories( ${CMAKE_SOURCE_DIR}/src/lib )

#----------------------------------#
#-      Build the Executable      -#
#----------------------------------#
add_executable( cli-cpp-config-generator
                ${CLI_CPP_CONFIG_GENERATOR_SOURCES}
)


#-------------------------------------#
#-      Link Required Libraries      -#
#-------------------------------------#
target_link_libraries( cli-cpp-config-generator
                       cli_cpp
                     )


