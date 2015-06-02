/**
 * @file    A_Render_Manager_Factory.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Render_Manager_Factory.hpp"

// CLI Libraries
#include "A_Render_Manager_ASCII.hpp"

// C++ Standard Libraries
#include <iostream>


namespace CLI{
namespace RENDER{

/****************************/
/*        Initialize        */
/****************************/
A_Render_Manager_Base::ptr_t A_Render_Manager_Factory::Initialize( CORE::ConnectionType const&             connection_type,
                                                                   const std::string&                      cli_title,
                                                                   CMD::A_Command_Parser::ptr_t            command_parser,
                                                                   A_Render_Driver_Context_Base::ptr_t     render_driver )
{
    // Create the pointer
    RENDER::A_Render_Manager_Base::ptr_t render_manager = nullptr;
    
    // Create the ASCII Render
    if( connection_type == CORE::ConnectionType::SOCKET ){
        render_manager = std::make_shared<RENDER::A_Render_Manager_ASCII>( render_driver, command_parser );

    }

    // Return Null
    else{
        return nullptr;
    }

    // Return the manager
    return render_manager;
}

} // End of RENDER Namespace
} // End of CLI    Namespace

