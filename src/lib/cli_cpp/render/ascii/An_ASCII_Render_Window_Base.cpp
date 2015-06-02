/**
 * @file    An_ASCII_Render_Window_Base.cpp
 * @author  Marvin Smith
 * @date    5/30/2015
*/
#include "An_ASCII_Render_Window_Base.hpp"

// CLI Libraries
#include "../../utility/ANSI_Utilities.hpp"


namespace CLI{
namespace RENDER{

/**********************************/
/*          Constructor           */
/**********************************/
An_ASCII_Render_Window_Base::An_ASCII_Render_Window_Base( A_Render_Driver_Context_ASCII::ptr_t render_driver )
   :  m_render_driver(render_driver),
      m_class_name("An_ASCII_Render_Window_Base")
{
    // Set the buffer size
    m_buffer_data = std::vector<std::string>( render_driver->Get_Window_Rows(), UTILS::ANSI_NEWLINE );

}


} // End of RENDER Namespace
} // End of CLI    Namespace

