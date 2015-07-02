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
                                                              const int&   window_rows,
                                                              const int&   window_cols,
                                                              const int&   min_content_row,
                                                              const int&   min_content_col,
                                                              const bool&  redirect_stdout,
                                                              const bool&  redirect_stderr )
  : A_Render_Driver_Context_Base( cli_title, 
                                  redirect_stdout,
                                  redirect_stderr ),
    m_class_name("A_Render_Driver_Context_ASCII"),
    m_window_rows(window_rows),
    m_window_cols(window_cols),
    m_min_content_row(min_content_row),
    m_min_content_col(min_content_col)
{
}


/***************************************/
/*       Set the CLI Window Size       */
/***************************************/
void A_Render_Driver_Context_ASCII::Set_CLI_Window_Size( const int& rows,
                                                         const int& cols )
{
    m_window_rows = rows;
    m_window_cols = cols;
}


/********************************************/
/*      Set the CLI Min Content Bounds      */
/********************************************/
void A_Render_Driver_Context_ASCII::Set_CLI_Window_Min_Content_Bounds( const int& row,
                                                                       const int& col )
{
    m_min_content_row = row;
    m_min_content_col = col;
}


} // End of RENDER Namespace
} // End of CLI    Namespace 

