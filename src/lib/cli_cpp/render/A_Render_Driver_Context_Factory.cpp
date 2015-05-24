/**
 * @file    A_Render_Driver_Context_Factory.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Render_Driver_Context_Factory.hpp"

// CLI Libraries
#include "A_Render_Driver_Context_ASCII.hpp"
#include "A_Render_Driver_Context_NCurses.hpp"

namespace CLI{
namespace RENDER{


/*************************/
/*      Initialize       */
/*************************/
A_Render_Driver_Context_Base::ptr_t A_Render_Driver_Context_Factory::Initialize( const CORE::ConnectionType& conn_type,
                                                                                 const int& window_rows,
                                                                                 const int& window_cols )
{
    // Test the NCurses Type
    if( conn_type == CORE::ConnectionType::LOCAL )
    {
        return std::make_shared<A_Render_Driver_Context_NCurses>();
    }

    // Test the ASCII Type
    if( conn_type == CORE::ConnectionType::SOCKET ){
        return std::make_shared<A_Render_Driver_Context_ASCII>( window_rows,
                                                                window_cols );
    }

    // Return null
    return nullptr;
}


} // End of RENDER Namespace
} // End of CLI    Namespace

