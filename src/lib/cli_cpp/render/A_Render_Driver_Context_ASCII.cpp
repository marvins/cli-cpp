/**
 * @file    A_Render_Driver_Context_ASCII.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Render_Driver_Context_ASCII.hpp"

namespace CLI{
namespace RENDER{

/*************************/
/*      Constructor      */
/*************************/
A_Render_Driver_Context_ASCII::A_Render_Driver_Context_ASCII( const std::string& cli_title,
                                                              const int& window_rows,
                                                              const int& window_cols,
                                                              const int& min_content_row,
                                                              const int& min_content_col)
  : A_Render_Driver_Context_Base(cli_title),
    m_class_name("A_Render_Driver_Context_ASCII"),
    m_window_rows(window_rows),
    m_window_cols(window_cols),
    m_min_content_row(min_content_row),
    m_min_content_col(min_content_col)
{
}



} // End of RENDER Namespace
} // End of CLI    Namespace 

