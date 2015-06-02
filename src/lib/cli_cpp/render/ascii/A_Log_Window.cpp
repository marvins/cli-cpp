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
    m_stderr_pipe_thread_shutdown(false)
{
    // Configure the pipes
    Configure_Pipes();
    
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
    const int max_row = m_render_driver->Get_Window_Rows();

    // Shift Data
    for( int row = min_row; row < (max_row-1); row++ )
    {
        m_buffer_data[row] = m_buffer_data[row+1];
    }

    //Add new content
    if( std::get<0>(m_log_data.back()) == 0 ){
        m_buffer_data[max_row-1] = std::get<1>(m_log_data) + UTILS::ANSI_NEWLINE;
    } else {    
        m_buffer_data[max_row-1] = UTILS::ANSI_RED + std::get<1>(m_log_data) + UTILS::ANSI_RESET + UTILS::ANSI_NEWLINE;
    }
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
                                            std::ref(this));
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

    // Iterate until closed
    while( shutdown_flag != true ){

        // Read from the buffer
        bytes_read = read( out_pipe[0], buffer, MAX_LEN );

        // Add to stdout
        buffer_data.push_back( std::string(buffer).substr(0,bytes_read) );

        // refresh the log window
        log_window.Refresh();
    }

    // reconfigure
    dup2(saved_out, fd );

}


} // End of RENDER Namespace
} // End of CLI    Namespace
