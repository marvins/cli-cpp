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
 - pthreads (`std::thread`)
 

### Compiling ###

CLI-CPP is constructed using the CMake build system.  Just do the following.

    mkdir -p release
    pushd release
    cmake ..
    make 
    popd


###  Test Application ###

CLI-CPP comes with a basic test application to demonstrate core capabilities.  To run...

    cd release
    ./bin/cli-network-tester ../data/CLI_Manager_Configuration.xml

    # On a separate terminal, 
    telnet localhost 12344


For the demo, the supported commands are shown below.  Note that tab-complete currently only works for the 
command and not yet arguments.

1.  ?, help
  -  Print Help
2. bye
  -  Log out of the terminal
3. system-shutdown
  - Shut down application.
4. ping <host-required> <num-tries optional>
  - ping a network address.


### CLI Main Window ###

![CLI Main Window](docs/images/CLI-Main.png "CLI Main Window")

### CLI Help Menu (?, help)###

![CLI Help Window](docs/images/CLI-Help.png "CLI Help Window")

### CLI Ping Command ###

![CLI Ping Command](docs/images/Ping-Demo.png "CLI Ping Command Waiting")

### CLI Ping Command Complete ###
![CLI Ping Command](docs/images/CLI_PING_COMPLETE.png "CLI Ping Command Complete")

