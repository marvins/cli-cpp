/**
 * @file    A_Netstat_Command_Response_Handler.cpp
 * @author  Marvin Smith
 * @date    5/24/2015
 */
#include "A_Netstat_Command_Response_Handler.hpp"

// Demo Libraries
#include "../utils/System_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>

/**********************************/
/*          Constructor           */
/**********************************/
A_Netstat_Command_Response_Handler::A_Netstat_Command_Response_Handler()
  : CLI::A_Command_Response_Handler_Base()
{
}


/****************************************/
/*         Check if Supported           */
/****************************************/
bool A_Netstat_Command_Response_Handler::Is_Supported( CLI::CMD::A_Command_Result const& result ) const
{
    // Check the name
    if( result.Get_Command().Get_Name() == "check-port-status" ){
        return true;
    }

    // Return false
    return false;
}

/****************************************/
/*          Process the Command         */
/****************************************/
void A_Netstat_Command_Response_Handler::Process_Command( CLI::CMD::A_Command_Result::ptr_t response ){

    // Define our values
    int port_number         = response->Get_Argument_Value<int>( 0 );
    std::string protocol    = response->Get_Argument_Value<std::string>(1);
    std::string details;


    // Run the command
    bool result = Netstat( port_number, protocol, details );

    if( result == true ){
        response->Set_System_Response( "Port is open.");
    }
    else{
        response->Set_System_Response( "Port is not open. Details: " + details );
    }
    
}


