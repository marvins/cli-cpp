/**
 * @file    A_Render_Driver_Context_Factory.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Render_Driver_Context_Factory.hpp"

// CLI Libraries
#include "A_Render_Driver_Context_ASCII.hpp"

namespace CLI{
namespace RENDER{


/*************************/
/*      Initialize       */
/*************************/
A_Render_Driver_Context_Base::ptr_t A_Render_Driver_Context_Factory::Initialize( const CORE::ConnectionType& conn_type,
                                                                                 const std::string&          cli_title,
                                                                                 const int&                  window_rows,
                                                                                 const int&                  window_cols )
{
    // Set the min content row
    int min_content_row = 2;
    int min_content_col = 1;

    // Test the ASCII Type
    if( conn_type == CORE::ConnectionType::SOCKET ){
        return std::make_shared<A_Render_Driver_Context_ASCII>( cli_title,
                                                                window_rows,
                                                                window_cols,
                                                                min_content_row,
                                                                min_content_col);
    }

    // Return null
    return nullptr;
}


} // End of RENDER Namespace
} // End of CLI    Namespace

