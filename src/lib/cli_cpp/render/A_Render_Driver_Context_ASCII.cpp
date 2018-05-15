/**
 * @file    A_Render_Driver_Context_ASCII.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Render_Driver_Context_ASCII.hpp"

namespace CLI{
namespace RENDER{


/****************************/
/*      Constructor         */
/****************************/
Render_Driver_Config_ASCII::Render_Driver_Config_ASCII( const std::string&         cli_title,
                                                        bool                       redirect_stdout,
                                                        bool                       redirect_stderr,
                                                        int                        window_rows,
                                                        int                        window_cols,
                                                        int                        min_content_row,
                                                        int                        min_content_col,
                                                        std::chrono::milliseconds  async_tab_refresh )
  : Render_Driver_Config_Base( cli_title,
                               redirect_stdout,
                               redirect_stderr ),
    m_class_name("Render_Driver_Config_ASCII"),
    m_window_rows(window_rows),
    m_window_cols(window_cols),
    m_min_content_row(min_content_row),
    m_min_content_col(min_content_col),
    m_async_tab_refresh(async_tab_refresh)
{}

/*************************/
/*      Constructor      */
/*************************/
A_Render_Driver_Context_ASCII::A_Render_Driver_Context_ASCII( Render_Driver_Config_Base::ptr_t config )
  : A_Render_Driver_Context_Base( config ),
    m_class_name("A_Render_Driver_Context_ASCII")
{
    m_config = std::dynamic_pointer_cast<Render_Driver_Config_ASCII>(config);
    
    m_cli_title = m_config->Get_CLI_Title();
    m_window_rows = m_config->Get_Window_Rows();
    m_window_cols = m_config->Get_Window_Cols();
    m_min_content_row = m_config->Get_Min_Content_Row();
    m_min_content_col = m_config->Get_Min_Content_Col();
    
}


/***************************************/
/*       Set the CLI Window Size       */
/***************************************/
void A_Render_Driver_Context_ASCII::Set_CLI_Window_Size( int rows,
                                                         int cols )
{
    m_window_rows = rows;
    m_window_cols = cols;
}


/********************************************/
/*      Set the CLI Min Content Bounds      */
/********************************************/
void A_Render_Driver_Context_ASCII::Set_CLI_Window_Min_Content_Bounds( int row,
                                                                       int col )
{
    m_min_content_row = row;
    m_min_content_col = col;
}


} // End of RENDER Namespace
} // End of CLI    Namespace 

