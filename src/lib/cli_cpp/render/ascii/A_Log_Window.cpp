/**
 * @file    A_Log_Window.cpp
 * @author  Marvin Smith
 * @date   5/30/2015
*/
#include "A_Log_Window.hpp"

// CLI Libraries
#include "../../utility/ANSI_Utilities.hpp"
#include "../../utility/Log_Utilities.hpp"

// C++ Standard Libraries
#include <cstdio>
#include <cstdlib>
#include <fstream>

namespace CLI{
namespace RENDER{

/**********************************/
/*          Constructor           */
/**********************************/
A_Log_Window::A_Log_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver)
  : An_ASCII_Render_Window_Base(render_driver),
    m_class_name("A_Log_Window"),
    m_stdout_pipe_thread_shutdown(false),
    m_stderr_pipe_thread_shutdown(false),
    m_previous_log_data_size(0)
{
    // Configure the pipes
    Configure_Pipes();
    
    // Set the header
    m_buffer_data[0] = UTILS::ANSI_CLEARSCREEN + UTILS::ANSI_RESETCURSOR + "     " + m_render_driver->Get_CLI_Title() + UTILS::ANSI_NEWLINE;
    
    // Titles
    std::vector<std::string> titles;
    titles.push_back("Pipe");
    titles.push_back("Message");
    
    std::vector<int> widths;
    widths.push_back(9);
    widths.push_back( m_render_driver->Get_Window_Cols() - m_render_driver->Get_Min_Content_Col() - 9);

    // Build the print table
    m_print_table = std::make_shared<UTILS::An_ASCII_Print_Table>(  titles,
                                                                    widths, 
                                                                    UTILS::An_ASCII_Print_Table_Config(false,false) );
}


/*********************************/
/*          Destructor           */
/*********************************/
A_Log_Window::~A_Log_Window()
{
    // Set flags
    m_stdout_pipe_thread_shutdown = true;
    m_stderr_pipe_thread_shutdown = true;
    
    // Pipe message to unlock reads
    if( m_render_driver->Get_Redirect_Stdout_Flag() == true ){
        std::cout << "End of Logging" << std::endl;
    }

    // Join any running threads
    if( m_stdout_pipe_thread.joinable() ){
        m_stdout_pipe_thread.join();
    }
    if( m_stderr_pipe_thread.joinable() ){
        m_stderr_pipe_thread.join();
    }
    
}


/*****************************/
/*         Refresh           */
/*****************************/
void A_Log_Window::Refresh()
{
    // Define row info
    const int min_row = m_render_driver->Get_Min_Content_Row();
    const int max_row = m_render_driver->Get_Window_Rows() - 4;
    const int min_col = m_render_driver->Get_Min_Content_Col();

    // iterate over new items
    for( int i=m_previous_log_data_size; i<(int)m_log_data.size(); i++ ){

        // Entry
        std::string pipe_name = "stdout";
        if( std::get<0>( m_log_data[i] ) == -1 ){
            pipe_name = "";
        } else if( std::get<0>( m_log_data[i] ) != STDOUT_FILENO ){
            pipe_name = "stderr";
        }
    
        // Create new string
        std::string new_data = UTILS::String_Trim(std::get<1>(m_log_data[i]));

        //Add new content
        m_print_table->Add_Entry( i, 0, pipe_name );
        m_print_table->Add_Entry( i, 1, new_data );
        
        // Print the table
        m_print_table->Print_Table( m_buffer_data, 
                                    min_row,     
                                    max_row, 
                                    min_col );
    }

    // Update the previous size
    m_previous_log_data_size = m_log_data.size();
}


/**********************************/
/*        Configure Pipes         */
/**********************************/
void A_Log_Window::Configure_Pipes()
{
    if( this->m_render_driver->Get_Redirect_Stdout_Flag() == true ){
        m_stdout_pipe_thread = std::thread( &A_Log_Window::Pipe_Thread_Runner, 
                                            STDOUT_FILENO, 
                                            std::ref(m_stdout_pipe_thread_shutdown),
                                            std::ref(m_log_data),
                                            std::ref(*this));
    }

}

/*****************************************/
/*          Pipe Thread Runner           */
/*****************************************/
void A_Log_Window::Pipe_Thread_Runner( const int& fd, 
                                       bool& shutdown_flag,
                                       std::vector<std::tuple<int,std::string>>& buffer_data,
                                       A_Log_Window& log_window )
{

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

    // Create pipe
    int out_pipe[2];

    // Duplicate
    int saved_out = dup( fd );
    
    // Create pipe
    if( pipe( out_pipe ) != 0 ){
        BOOST_LOG_TRIVIAL(error) << "Unable to redirect output. Killing thread.";
        return;
    }

    // Duplicate
    dup2( out_pipe[1], fd );

    // Close
    close(out_pipe[1]);

    // Create buffer
    const int MAX_LEN = 500;
    char buffer[MAX_LEN+1] = {0};
    int bytes_read;
    std::vector<std::string> split_string_list;

    // Iterate until closed
    while( shutdown_flag != true ){

        // Read from the buffer
        bytes_read = read( out_pipe[0], buffer, MAX_LEN );

        // Split the list
        split_string_list = UTILS::String_Split( std::string(buffer).substr(0,bytes_read),
                                                 "\n");

        // Add to stdout
        for( int i=0; i<(int)split_string_list.size(); i++ ){ 
            if( i == 0 ){
                buffer_data.push_back( std::make_tuple(fd, split_string_list[i]));
            } else {
                buffer_data.push_back( std::make_tuple(-1, split_string_list[i]));
            }
        }

        // refresh the log window
        log_window.Refresh();
    }

    // reconfigure
    dup2(saved_out, fd );

}


} // End of RENDER Namespace
} // End of CLI    Namespace
