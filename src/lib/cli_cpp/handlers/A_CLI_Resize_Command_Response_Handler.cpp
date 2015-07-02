/**
 * @file    A_CLI_Resize_Command_Response_Handler.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
 */
#include "A_CLI_Resize_Command_Response_Handler.hpp"


// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace HANDLER{

/**********************************/
/*          Constructor           */
/**********************************/
A_CLI_Resize_Command_Response_Handler::A_CLI_Resize_Command_Response_Handler( RENDER::A_Render_Manager_Base::ptr_t render_manager )
  : CLI::A_Command_Response_Handler_Base(),
    m_class_name("A_CLI_Resize_Command_Response_Handler"),
    m_render_manager(render_manager)
{
}


/****************************************/
/*         Check if Supported           */
/****************************************/
bool A_CLI_Resize_Command_Response_Handler::Is_Supported( CLI::CMD::A_Command_Result const& result ) const
{
    // Check the name
    if( result.Get_Command().Get_Name() == "cli-resize" ){
        return true;
    }

    // Return false
    return false;
}

/****************************************/
/*          Process the Command         */
/****************************************/
void A_CLI_Resize_Command_Response_Handler::Process_Command( CLI::CMD::A_Command_Result::ptr_t response ){


    std::cout << "Inside A_CLI_Resize_Command_Response_Handler" << std::endl;

    // Define our values
    int rows         = response->Get_Argument_Value<int>( 0 );
    int cols         = response->Get_Argument_Value<int>( 1 );
    

    // Check the dimensions
    if( rows <= 0 ){
        response->Set_System_Response( "Rows cannot be less than 1." );
        return;
    }
    if( cols <= 0 ){
        response->Set_System_Response( "Columns cannot be less than 1." );
        return;
    }

    // Set the size
    m_render_manager->Set_CLI_Window_Size( rows, cols );

    // Set response
    response->Set_System_Response("Resized window.");
    
}

} // End of HANDLER Namespace
} // End of CLI     Namespace

