/**
 * @file    A_Render_Manager_ASCII.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Render_Manager_ASCII.hpp"

// C++ Standard Libraries
#include <algorithm>
#include <iostream>
#include <memory>
#include <sstream>

// CLI Libraries
#include "ascii/A_General_Help_Window.hpp"
#include "ascii/A_Log_Window.hpp"
#include "ascii/A_Main_Window.hpp"
#include "ascii/An_Alias_List_Window.hpp"
#include "../utility/ANSI_Utilities.hpp"
#include "../utility/Log_Utilities.hpp"
#include "../utility/String_Utilities.hpp"

namespace CLI{
namespace RENDER{

const std::string BUFFER_NEWLINE = "\n\r";

/****************************/
/*      Constructor         */
/****************************/
A_Render_Manager_ASCII::A_Render_Manager_ASCII( A_Render_Driver_Context_Base::ptr_t driver_context,
                                                CMD::A_Command_Parser::ptr_t        command_parser )
 :  A_Render_Manager_Base( command_parser ),
    m_class_name("A_Render_Manager_ASCII"),
    m_current_window(0)
{
    // Cast the driver
    m_render_driver_context = std::dynamic_pointer_cast<A_Render_Driver_Context_ASCII>(driver_context);

    // Create new render state
    m_render_state.reset(new A_Render_State( CORE::ConnectionType::SOCKET, 
                                             m_command_history,
                                             m_command_parser ));
}




/********************************/
/*      Initialize Curses       */
/********************************/
void A_Render_Manager_ASCII::Initialize()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

    // Set the size
    m_render_state->Set_Window_Size( m_render_driver_context->Get_Window_Rows(), 
                                     m_render_driver_context->Get_Window_Cols() );

    // Add the main window
    m_window_list.push_back(std::make_shared<A_Main_Window>( m_render_driver_context,
                                                             m_command_history ));
    
    // Add the help window
    m_window_list.push_back(std::make_shared<A_General_Help_Window>( m_render_driver_context,
                                                                     m_command_parser->Get_CLI_Command_List(),
                                                                     m_command_parser->Get_Command_List() ));

    // Add the log window
    m_window_list.push_back(std::make_shared<A_Log_Window>( m_render_driver_context ));
    
    
    // Add the alias list window
    m_window_list.push_back(std::make_shared<An_Alias_List_Window>( m_render_driver_context, 
                                                                    m_command_parser ));

    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

}

/********************************/
/*        Finalize Curses       */
/********************************/
void A_Render_Manager_ASCII::Finalize()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Clear out the windows
    m_window_list.clear();

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/****************************/
/*      Get the buffer      */
/****************************/
std::vector<std::string>& A_Render_Manager_ASCII::Get_Console_Buffer()
{
    // Return the current window
    return m_window_list[m_current_window]->Get_Buffer_Data();
}


/********************************/
/*      Refresh the screen      */
/********************************/
void A_Render_Manager_ASCII::Refresh()
{
    // Update the buffer data
    m_window_list[m_current_window]->Update_Buffer_Data();

    // Print the CLI Onto the Current Buffer Data
    Print_CLI(m_window_list[m_current_window]->Get_Buffer_Data());
    
}


/********************************/
/*          Print the CLI       */
/********************************/
void A_Render_Manager_ASCII::Print_CLI( std::vector<std::string>& print_buffer )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Set the buffer row
    int cli_row = m_render_state->Get_Rows() - 2;

    
    // Get the cursor text
    const std::string cursor_text = m_render_state->Get_Cursor_Text();
    const int cli_prompt_pos = m_render_state->Get_Cursor_Pos();

    // Write the Cursor Text
    std::string output = "   ";
    output += UTILS::ANSI_GREEN + std::string("cmd: ") + UTILS::ANSI_RESET;
    
    // Don't do this if the cursor is at 0
    if( cli_prompt_pos > 0 ){
        output += cursor_text.substr(0,cli_prompt_pos);
    }

    // Print the text
    if( (int)cursor_text.size() > 0 && cli_prompt_pos < (int)cursor_text.size() ){
        output += UTILS::ANSI_BACK_WHITE + UTILS::ANSI_BLACK + cursor_text[cli_prompt_pos] + UTILS::ANSI_RESET;
    } else {
        output += UTILS::ANSI_BACK_WHITE + UTILS::ANSI_BLACK + " " + UTILS::ANSI_RESET;
    }

    // Don't do this if we are at the end
    if( cli_prompt_pos < (int)cursor_text.size()){
        output += cursor_text.substr(cli_prompt_pos+1);
    }


    // Copy to the buffer
    print_buffer[cli_row+0] = output + BUFFER_NEWLINE +  UTILS::ANSI_CURSORINVIS;

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}

/****************************************************/
/*      Set the Command Waiting Response Values     */
/****************************************************/
void A_Render_Manager_ASCII::Set_Waiting_Command_Response( const CMD::A_Command_Result::ptr_t response )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    m_render_driver_context->Set_Waiting_Command_Response( response );
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/**************************************************/
/*      Check the waiting response flag value     */
/**************************************************/
bool A_Render_Manager_ASCII::Check_Waiting_Command_Response(){
    
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    return m_render_driver_context->Check_Waiting_Command_Response();
}
        



} // End of RENDER Namespace
} // End of CLI    Namespace

