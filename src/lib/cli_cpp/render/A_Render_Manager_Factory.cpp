/**
 * @file    A_Render_Manager_Factory.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Render_Manager_Factory.hpp"

// CLI Libraries
#include "A_Render_Manager_ASCII.hpp"
#include "A_Render_Manager_NCurses.hpp"

namespace CLI{
namespace RENDER{

/****************************/
/*        Initialize        */
/****************************/
A_Render_Manager_Base::ptr_t A_Render_Manager_Factory::Initialize( CORE::ConnectionType const&             connection_type,
                                                                   const std::string&                      cli_title,
                                                                   std::vector<CMD::A_Command> const&      command_list,
                                                                   std::vector<CMD::A_CLI_Command> const&  cli_command_list,
                                                                   A_Render_Driver_Context_Base::ptr_t     render_driver )
{
    // Create the pointer
    RENDER::A_Render_Manager_Base::ptr_t render_manager = nullptr;

    // Create the ASCII Render
    if( connection_type == CORE::ConnectionType::SOCKET ){
        render_manager = std::make_shared<RENDER::A_Render_Manager_ASCII>( render_driver );

    }

    // Create the NCurses Render
    else if( connection_type == CORE::ConnectionType::LOCAL ){
        render_manager = std::make_shared<RENDER::A_Render_Manager_NCurses>( render_driver );
    }

    // Return Null
    else{
        return nullptr;
    }


    // Set the title
    render_manager->Set_CLI_Title( cli_title );

   
    // Set the command lists
    render_manager->Update_Command_List( command_list );
    render_manager->Update_CLI_Command_List( cli_command_list );

    
    // Return the manager
    return render_manager;
}

} // End of RENDER Namespace
} // End of CLI    Namespace

