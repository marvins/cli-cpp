/**
 * @file    System_Utilities.cpp
 * @author  Marvin Smith
 * @date    5/20/2015
 */
#include "System_Utilities.hpp"

// CLI Libraries
#include <cli_cpp/utility/String_Utilities.hpp>

// C++ Standard Libraries
#include <cstdio>
#include <sstream>

/*************************************************/
/*         Execute Generic Shell Command         */
/*************************************************/
int Execute_Command( const std::string&  command,
                     std::string&        output,
                     const std::string&  mode )
{
    // Create the stringstream
    std::stringstream sout;

    // Run Popen
    FILE *in;
    char buff[512];

    // Test output
    if(!(in = popen(command.c_str(), mode.c_str()))){
        return 1;
    }

    // Parse output
    while(fgets(buff, sizeof(buff), in)!=NULL){
        sout << buff;
    }

    // Close
    int exit_code = pclose(in);

    // set output
    output = sout.str();

    // Return exit code
    return exit_code;
}

/*************************************************/
/*                  Ping Command                 */
/*************************************************/
bool Ping( const std::string& address,
           const int&         max_attempts,
           std::string&       details )
{
    // Format a command string
    std::string command = "ping -c " + CLI::UTILS::num2str(max_attempts) + " " + address + " 2>&1";

    // Execute the ping command
    int code = Execute_Command( command, details );

    return (code == 0);
}


/*************************************/
/*          Netstat Command          */
/*************************************/
int Netstat( const int& port_number,
             const std::string& protocol,
             std::string& details )
{

    // Format the command string
    std::string command = "netstat -an | grep ";
    
    if( protocol == "tcp" | protocol == "TCP" ){
        command += "tcp";
    }
    if( protocol == "udp" | protocol == "UD" ){
        command += "udp";
    }

    //execute command
    int code = Execute_Command( command, details );

    return (code == 0); 
}
