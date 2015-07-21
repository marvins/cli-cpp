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
#include "A_Render_Driver_Context_Factory.hpp"
#include "A_Render_State_Factory.hpp"
#include "ascii/A_General_Help_Window.hpp"
#include "ascii/A_Log_Window.hpp"
#include "ascii/A_Main_Window.hpp"
#include "ascii/A_Variable_List_Window.hpp"
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
A_Render_Manager_ASCII::A_Render_Manager_ASCII( const int&                    instance_id,
                                                CMD::A_Command_Parser::ptr_t  command_parser,
                                                CMD::A_Command_Queue::ptr_t   command_queue )
 :  A_Render_Manager_Base( instance_id,
                           command_parser,
                           command_queue ),
    m_class_name("A_Render_Manager_ASCII"),
    m_current_window(0),
    m_help_window_mode(false)
{
    // Cast the driver
    A_Render_Driver_Context_Base::ptr_t render_driver = A_Render_Driver_Context_Factory::Create_Instance();
    m_render_driver_context = std::dynamic_pointer_cast<A_Render_Driver_Context_ASCII>(render_driver);
    
    // Local Rendering State
    m_render_state = A_Render_State_Factory::Instance_Of( instance_id );

    // Make sure it is not null
    if( m_render_state == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render-State is currently null. Expect Failure. Func: " << __func__ << ", File: " << __FILE__ << ", Line: " << __LINE__;
    }

}




/********************************/
/*      Initialize Curses       */
/********************************/
void A_Render_Manager_ASCII::Initialize()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;


    // Cast the driver
    A_Render_Driver_Context_ASCII::ptr_t driver_context = std::dynamic_pointer_cast<A_Render_Driver_Context_ASCII>( m_render_driver_context);
    
    // Make sure it is not null
    if( driver_context == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "driver-context is currently null. Expect a big seg fault.";
    }

    // Make sure the command-parser is not null
    if( m_command_parser == nullptr ){
        BOOST_LOG_TRIVIAL(fatal) << "Command-Parser is null. Expect a seg fault. File: " << __FILE__ << ", Line: " << __LINE__;
    }

    // Add the main window [0]
    m_window_list.push_back(std::make_shared<A_Main_Window>( driver_context,
                                                             m_render_state->Get_Command_History()));
    
    // Add the help window [1]
    m_window_list.push_back(std::make_shared<A_General_Help_Window>( driver_context,
                                                                     m_command_parser ));

    // Add the log window [2]
    m_window_list.push_back(std::make_shared<A_Log_Window>( driver_context ));
    
    
    // Add the alias list window [3]
    m_window_list.push_back(std::make_shared<An_Alias_List_Window>( driver_context, 
                                                                    m_command_parser ));

    // Add the variable list window [4]
    m_window_list.push_back(std::make_shared<A_Variable_List_Window>( driver_context,
                                                                      m_command_parser ));

    
    // Create the CLI Man Pages
    for( size_t i=0; i<m_command_parser->Get_CLI_Command_List().size(); i++ ){
        m_help_windows.push_back(std::make_shared<A_CLI_Command_Detailed_Help_Window>( driver_context,
                                                                                        m_command_parser->Get_CLI_Command_List()[i] ));
    }

    

    
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
    m_help_windows.clear();

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/****************************/
/*      Get the buffer      */
/****************************/
std::vector<std::string> A_Render_Manager_ASCII::Get_Console_Buffer()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Lock the mutex
    m_refresh_mutex.lock();
    
    
    // Refresh
    Refresh();

    
    // Get the data
    std::vector<std::string> output;
    if( m_help_window_mode == false ){
        output = m_window_list[m_current_window]->Get_Buffer_Data();
    }
    else {
        output = m_help_windows[m_current_window]->Get_Buffer_Data();
    }
    
    // Unlock the mutex
    m_refresh_mutex.unlock();
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Return the current window
    return output;
}


/**************************************/
/*       Set the CLI Window Size      */
/**************************************/
void A_Render_Manager_ASCII::Set_CLI_Window_Size( const int& rows,
                                                  const int& cols )
{
    // Lock the mutex
    m_refresh_mutex.lock();

    
    // Update Driver
    m_render_driver_context->Set_CLI_Window_Size( rows, cols );

    
    // Unlock the mutex
    m_refresh_mutex.unlock();

}



/********************************/
/*      Refresh the screen      */
/********************************/
void A_Render_Manager_ASCII::Refresh()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    

    // Pick the right window
    An_ASCII_Render_Window_Base::ptr_t ref;
    if( m_help_window_mode == true ){
        ref = m_help_windows[m_current_window];
    } else {
        ref = m_window_list[m_current_window];
    }


    // Update the buffer data
    ref->Update_Buffer_Data();


    // Print the Header onto the Current Buffer Data
    Print_Header(ref->Get_Buffer_Data());


    // Print the CLI Onto the Current Buffer Data
    Print_CLI(ref->Get_Buffer_Data());

    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/*******************************/
/*      Print the Header       */
/*******************************/
void A_Render_Manager_ASCII::Print_Header( std::vector<std::string>& print_buffer )
{
    
    // Pick the right window
    An_ASCII_Render_Window_Base::ptr_t ref;
    if( m_help_window_mode == true ){
        ref = m_help_windows[m_current_window];
    } else {
        ref = m_window_list[m_current_window];
    }
    
    // Get the CLI Title
    std::string cli_title = "   " + m_render_driver_context->Get_CLI_Title();
    
    
    // Status Code String
    std::string status_code_string = Get_Header_Status_Bar_Text();

    // Status Mode String
    std::string status_mode_string = Get_Header_Mode_Bar_Text();

    
    // Find the title length
    int title_length = std::min((int)cli_title.size(), m_render_driver_context->Get_Window_Cols() * 3/8);
    int title_width  = m_render_driver_context->Get_Window_Cols() * 3 / 8;
    
    // Define the first title part
    std::string title_header = cli_title.substr( 0, title_length);
    title_header.resize(title_width, ' ');

    // Append the status text
    title_header += status_mode_string + UTILS::ANSI_RESET + "  " + status_code_string + UTILS::ANSI_RESET;
    
    // Set the header
    print_buffer[0] = UTILS::ANSI_CLEARSCREEN + UTILS::ANSI_RESETCURSOR + title_header + UTILS::ANSI_NEWLINE;
    
    // Set the titlebar
    print_buffer[1] = "   " + UTILS::ANSI_BLUE + ref->Get_Window_Title() + UTILS::ANSI_RESET + UTILS::ANSI_NEWLINE;
    
}


/**********************************************/
/*          Get Header Status Bar Text        */
/**********************************************/
std::string A_Render_Manager_ASCII::Get_Header_Status_Bar_Text()const
{

    // Make sure the driver is not null
    if( m_render_state == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render-State is currently null. Expect a seg fault. Method: " << __func__ << ", File: " << __FILE__ << ", Line: " << __LINE__;
    } 
    if( m_render_driver_context == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render-Driver Context is null. Method: " << __func__ << ", File: " << __FILE__ << ", Line: " << __LINE__;
    }


    // Create output
    std::string output;

    // Define the window size
    int status_bar_width = m_render_driver_context->Get_Window_Cols()/4;


    // Check if we are currently sleeping
    if( m_render_state->Get_Sleep_Mode() == true ){
         output = UTILS::ANSI_BACK_BLUE + UTILS::ANSI_WHITE + UTILS::Format_String("Sleeping",
                                                                                   status_bar_width);
    }

    // Check if we are waiting on user input
    else if( m_render_state->Get_Pause_Mode() == true ){
        output = UTILS::ANSI_BACK_RED + UTILS::ANSI_WHITE + UTILS::Format_String("Waiting on User Input",
                                                                                 status_bar_width);
    }

    // Check if we are waiting for a command response
    else if( m_render_driver_context->Check_Waiting_Command_Response() == true ){
         output = UTILS::ANSI_BACK_RED + UTILS::ANSI_WHITE + UTILS::Format_String("Waiting for Command Response",
                                                                                  status_bar_width);
    } 
    
    // Otherwise, we are in a standard configuration
    else {
        output = UTILS::ANSI_BACK_WHITE + UTILS::ANSI_BLACK + UTILS::Format_String( "Ready", 
                                                                                    status_bar_width );
    }
    

    // Return the output
    return output;
}



/********************************************/
/*          Get Header Mode Bar Text        */
/********************************************/
std::string A_Render_Manager_ASCII::Get_Header_Mode_Bar_Text()const
{

    // Create output
    std::string output;

    // Define the window size
    int mode_bar_width = m_render_driver_context->Get_Window_Cols()/4;


    // Check if we are currently in a script
    if( m_render_state->Get_Active_Command_Queue_Size() > 0 )
    {
        output = UTILS::ANSI_BACK_BLUE + UTILS::ANSI_WHITE + UTILS::Format_String("CLI Script Mode", 
                                                                                  mode_bar_width );
    }

    // Otherwise, we are in a standard configuration
    else {
        output = UTILS::ANSI_BACK_GREEN + UTILS::ANSI_BLACK + UTILS::Format_String( "CLI Text Input Mode", 
                                                                                    mode_bar_width );
    }
    

    // Return the output
    return output;
}



/********************************/
/*          Print the CLI       */
/********************************/
void A_Render_Manager_ASCII::Print_CLI( std::vector<std::string>& print_buffer )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Set the buffer row
    int cli_row = m_render_driver_context->Get_Window_Rows() - 2;
    
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
    
    // Lock the mutex
    m_refresh_mutex.lock();
    
    // Set the flag
    m_render_driver_context->Set_Waiting_Command_Response( response );
    
    // Unlock the mutex
    m_refresh_mutex.unlock();
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/**************************************************/
/*      Check the waiting response flag value     */
/**************************************************/
bool A_Render_Manager_ASCII::Check_Waiting_Command_Response(){
    
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;


    // Lock the mutex
    m_refresh_mutex.lock();


    // Get the value
    bool output = m_render_driver_context->Check_Waiting_Command_Response();


    // Unlock the mutex
    m_refresh_mutex.unlock();


    // Return
    return output;
}
        
/******************************************************/
/*          Set the CLI Detailed Help Window          */
/******************************************************/
bool A_Render_Manager_ASCII::Set_CLI_Detailed_Help_Window( const std::string& command_name )
{
    // Iterate over help windows, looking for a match
    for( size_t i=0; i<m_help_windows.size(); i++ ){
        
        // Check the name match
        if( m_help_windows[i]->Is_Matching_Name( command_name ) == true ){
            m_help_window_mode = true;
            m_current_window = i;
            return true;
        }
    }
    return false;
}


/*********************************************/
/*          Register Render Window           */
/*********************************************/
int A_Render_Manager_ASCII::Register_Custom_Render_Window( An_ASCII_Render_Window_Base::ptr_t render_window )
{
    // Make sure the driver context is not null
    if( m_render_driver_context == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render-Driver Context is null. Expect a seg fault.  File: " << __FILE__ << ", Class: " << m_class_name << ", Method: " << __func__ << ", Line: " << __LINE__;
    }

    // Attach the driver
    render_window->Set_Render_Driver_Context( std::dynamic_pointer_cast<A_Render_Driver_Context_ASCII>(m_render_driver_context) );
    
    // Add to the window
    m_window_list.push_back( render_window );

    // return the id
    return (m_window_list.size()-1);

}


} // End of RENDER Namespace
} // End of CLI    Namespace

