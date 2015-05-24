# CLI-C++ #

A Command-Line Interface (CLI) for use in C++ programs.

## Overview ##

The purpose of this project is to provide C++ programmers with a Command-Line Interface which they can 
tie into their existing projects.  This seeks to allow connecting to your application via the local 
process or via a TCP socket.  

All arguments are controlled via a configuration file which consists of several CLI commands plus the user-defined
commands.  The command name, arguments, types, and response expectations can be provided.

## Building ##

CLI-CPP has some basic requirements.  I have only 
tested this on Linux (Ubuntu/Fedora) and MacOS X with MacPorts

### Dependencies ###
 - Boost
 - NCurses
 - pthreads (`std::thread`)
 

### Compiling ###

CLI-CPP is constructed using the CMake build system.  Just do the following.

    mkdir -p release
    pushd release
    cmake ..
    make 
    popd

