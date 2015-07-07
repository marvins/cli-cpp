/**
 * @file    A_Network_Asset_Command_Response_Handler.cpp
 * @author  Marvin Smith
 * @date    5/24/2015
 */
#include "A_Network_Asset_Command_Response_Handler.hpp"

// Demo Libraries
#include "../utils/System_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>

/**********************************/
/*          Constructor           */
/**********************************/
A_Network_Asset_Command_Response_Handler::A_Network_Asset_Command_Response_Handler( Network_Scanner::ptr_t network_scanner )
  : CLI::A_Command_Response_Handler_Base(),
    m_class_name("A_Network_Asset_Command_Response_Handler"),
    m_network_scanner(network_scanner)
{
}


/****************************************/
/*         Check if Supported           */
/****************************************/
bool A_Network_Asset_Command_Response_Handler::Is_Supported( CLI::CMD::A_Command_Result const& result ) const
{
    // Check the name
    if( result.Get_Command().Get_Name() == "add-network-asset" ){
        return true;
    }

    // Return false
    return false;
}

/****************************************/
/*          Process the Command         */
/****************************************/
void A_Network_Asset_Command_Response_Handler::Process_Command( CLI::CMD::A_Command_Result::ptr_t response )
{



    
}


