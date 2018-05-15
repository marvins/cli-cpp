/**
 * @file    A_CLI_Detailed_Help_Command_Response_Handler.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
 */
#include "A_CLI_Detailed_Help_Command_Response_Handler.hpp"


// CLI Libraries
#include "../render/A_Render_Manager_Factory.hpp"
#include "../utility/Log_Utilities.hpp"


// C++ Standard Libraries
#include <iostream>

namespace CLI{
namespace HANDLER{

/**********************************/
/*          Constructor           */
/**********************************/
A_CLI_Detailed_Help_Command_Response_Handler::A_CLI_Detailed_Help_Command_Response_Handler()
  : CLI::A_Command_Response_Handler_Base(),
    m_class_name("A_CLI_Detailed_Help_Command_Response_Handler")
{
}


/****************************************/
/*         Check if Supported           */
/****************************************/
bool A_CLI_Detailed_Help_Command_Response_Handler::Is_Supported( CLI::CMD::A_Command_Result const& result ) const
{
    // Check the name
    if( result.Get_Command().Get_Name() == "help" ||
        result.Get_Command().Get_Name() == "?" ){
        return true;
    }

    // Return false
    return false;
}

/****************************************/
/*          Process the Command         */
/****************************************/
void A_CLI_Detailed_Help_Command_Response_Handler::Process_Command( CLI::CMD::A_Command_Result::ptr_t response,
                                                                    const bool&                       wait_on_response )
{

    // Get the instance ID
    int instance = response->Get_Instance_ID();

    // Get the render manager
    RENDER::A_Render_Manager_Base::ptr_t render_manager = RENDER::A_Render_Manager_Factory::Instance_Of( instance,
                                                                                                         CORE::SessionType::UNKNOWN );

    // Make sure the render manager is valid
    if( render_manager == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render-Manager returned for instance " << instance << " is null.";
        return;
    }


    // Check the number of arguments
    int nargs = response->Get_Argument_Value_Count();
    

    // If there are no arguments, just set the help window
    if( nargs == 0 ){
        render_manager->Set_Current_Window(1);
        response->Set_System_Response( "Opening General Help Window" );
        return;
    }

    // Get the next argument
    std::string help_page = response->Get_Argument_Value<std::string>(0);

    // Check if the page is supported
    if( render_manager->Set_CLI_Detailed_Help_Window( help_page ) == false ){
        response->Set_System_Response( "Unable to find appropriate help window.");
    } else {
        response->Set_System_Response( "Success" );
    }   
}

} // End of HANDLER Namespace
} // End of CLI     Namespace

