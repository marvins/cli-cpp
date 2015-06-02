/**
 * @file    A_Log_Window.cpp
 * @author  Marvin Smith
 * @date   5/30/2015
*/
#include "A_Log_Window.hpp"

namespace CLI{
namespace RENDER{

/**********************************/
/*          Constructor           */
/**********************************/
A_Log_Window::A_Log_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver)
  : An_ASCII_Render_Window_Base(render_driver),
    m_class_name("A_Log_Window")
{
}


} // End of RENDER Namespace
} // End of CLI    Namespace
