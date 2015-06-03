/** 
 * @file    A_Log_Window.hpp
 * @author  Marvin Smith
 * @date    5/30/2015
*/
#ifndef __CLI_CPP_LIB_RENDER_ASCII_A_LOG_WINDOW_HPP__
#define __CLI_CPP_LIB_RENDER_ASCII_A_LOG_WINDOW_HPP__

// CLI Libraries
#include "An_ASCII_Render_Window_Base.hpp"
#include "../../utility/An_ASCII_Print_Table.hpp"


// C++ Standard Libraries
#include <memory>
#include <mutex>
#include <string>
#include <thread>
#include <tuple>
#include <vector>

namespace CLI{
namespace RENDER{

 
/**
 * @class A_Log_Window
*/
class A_Log_Window : public An_ASCII_Render_Window_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Log_Window> ptr_t;


        /**
         * @brief Constructor
        */
        A_Log_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver );
    
        
        /**
         * @brief Destructor
        */
        ~A_Log_Window();
        

        /**
         * @brief Refresh the window
        */
        void Refresh();


    private:

        /**
         * @brief Configure Standard output and standard error
         */
        void Configure_Pipes();

        /**
         * @brief Pipe Thread Runner
        */
        static void Pipe_Thread_Runner( const int&  fd, 
                                        bool& shutdown_flag, 
                                        std::vector<std::tuple<int,std::string>>& buffer_data,
                                        A_Log_Window&  log_window );

        
        /// Class Name
        std::string m_class_name;

        /// Pipe Thread
        std::thread m_stdout_pipe_thread;
        std::thread m_stderr_pipe_thread;

        /// Run Flags
        bool m_stdout_pipe_thread_shutdown;
        bool m_stderr_pipe_thread_shutdown;

        /// Buffers
        std::vector<std::tuple<int,std::string>> m_log_data;
        int m_previous_log_data_size;

        /// ASCII Print Window
        UTILS::An_ASCII_Print_Table::ptr_t m_print_table;
    
        /// Mutex
        std::mutex m_mutex;

}; // End of A_Log_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
