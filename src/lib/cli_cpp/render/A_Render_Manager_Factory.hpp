/**
 * @file    A_Render_Manager_Factory.hpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#ifndef __CLI_CPP__RENDER_A_RENDER_MANAGER_FACTORY_HPP__
#define __CLI_CPP__RENDER_A_RENDER_MANAGER_FACTORY_HPP__

// CLI Libraries
#include "../core/ConnectionType.hpp"
#include "A_Render_Driver_Context_Base.hpp"
#include "A_Render_Manager_Base.hpp"

// C++ Standard Libraries
#include <string>
#include <vector>

namespace CLI{
namespace RENDER{

class A_Render_Manager_Factory
{
    public:
        
        /**
         * Initialize
        */
        static A_Render_Manager_Base::ptr_t  Initialize( CORE::ConnectionType const&             conn_type,
                                                         const std::string&                      cli_title,
                                                         CMD::A_Command_Parser::ptr_t            command_parser,
                                                         A_Render_Driver_Context_Base::ptr_t     render_context );


}; // End of A_Render_Manager_Factory

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
