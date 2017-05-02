/**
 * @file    A_Render_Manager_ASCII.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __CLI_A_CONSOLE_RENDER_MANAGER_ASCII_HPP__
#define __CLI_A_CONSOLE_RENDER_MANAGER_ASCII_HPP__

// C++ Standard Libraries
#include <chrono>
#include <deque>
#include <memory>
#include <mutex>
#include <string>
#include <vector>

// CLI Libraries
#include "A_Render_Driver_Context_ASCII.hpp"
#include "A_Render_Manager_Base.hpp"
#include "A_Render_State.hpp"
#include "ascii/An_ASCII_Render_Window_Base.hpp"
#include "ascii/A_CLI_Command_Detailed_Help_Window.hpp"
#include "../cmd/A_Command_History.hpp"
#include "../utility/An_ASCII_Print_Table.hpp"


namespace CLI{
namespace RENDER{

/**
 * @class A_Render_Manager_ASCII
 */
class A_Render_Manager_ASCII : public A_Render_Manager_Base 
{

    public:


        /// Pointer Type
        typedef std::shared_ptr<A_Render_Manager_ASCII> ptr_t;


        /**
         * @brief Constructor
         *
         * @param[in] instance_id
         * @param[in] command_parser
         */
        A_Render_Manager_ASCII( const int&                    instance_id,
                                CMD::A_Command_Parser::ptr_t  command_parser,
                                CMD::A_Command_Queue::ptr_t   command_queue );

        /**
         * @brief Destructor
         */
         virtual ~A_Render_Manager_ASCII();


        /**
         * @brief Initialize
        */
        virtual void Initialize();


        /**
         * @brief Finalize
        */
        virtual void Finalize();


        /**
         * @brief Get the buffer.
         *
         * @return Console buffer.
         */
        std::vector<std::string> Get_Console_Buffer();


        /**
         * @brief Command the system to wait on the input command response.
         */
        virtual void Set_Waiting_Command_Response( const CMD::A_Command_Result::ptr_t response );


        /**
         * @brief Get the waiting status
         *
         * @return True if waiting on command result response.
         */
        virtual bool Check_Waiting_Command_Response();


        /**
         * @brief Set the Current Window
         */
        inline virtual void Set_Current_Window( const int& window_id )
        {
            m_current_window = window_id;
            m_help_window_mode = false;
        }


        /**
         * @brief Set the CLI Window Size
         *
         * @param[in] rows CLI Window Rows.
         * @param[in] cols CLI Window Cols.
         */
        virtual void Set_CLI_Window_Size( const int& rows,
                                          const int& cols );

        /**
         * @brief Set the window to the appropriate Detailed Help ID.
         *
         * @param[in] command_name
        */
        virtual bool Set_CLI_Detailed_Help_Window( const std::string& command_name );


        /**
         * @brief Add a Custom Render Window.
         *
         * @param[in] render_window Render window to add.
         *
         * @return ID of the window.
        */
        virtual int Register_Custom_Render_Window( An_ASCII_Render_Window_Base::ptr_t render_window );


        /**
         * @brief Find a Window-ID by Command
         */
        virtual int Find_Window_ID_By_Trigger_Command( const CMD::A_Command& command )const;


        /**
         * @brief Send Asynchronous Message to Rendering Windows.
         *
         * @param[in] topic_name
         * @param[in] message
        */
        virtual void Send_Asynchronous_Message( const std::string& topic_name,
                                                const std::string& message );

    protected:

        /**
         * @brief Check the Async Message Flag
        */
        bool Check_Async_Message_Sent();


        /**
         * @brief Refresh the Screen.
         */
        virtual void Refresh();



       /**
         * @brief Get the header status bar text.
         *
         * @return Header status bar text.
        */
        virtual std::string Get_Header_Status_Bar_Text()const;


        /**
         * @brief Get the header mode bar text.
         *
         * @return Header Mode bar text.
        */
        virtual std::string Get_Header_Mode_Bar_Text()const;
        

        /**
         * @brief Get the header async message bar text
        */
        virtual std::string Get_Header_Async_Bar_Text();

        /**
         * @brief Print the header
         *
         * @param[in] print_buffer Buffer to print header contents to.
        */
        virtual void Print_Header( std::vector<std::string>& print_buffer );


        /**
         * @brief Print CLI
         *
         * @param[in] print_buffer Buffer to post cli contents to.
         */
        virtual void Print_CLI( std::vector<std::string>& print_buffer );


    private:

        /**
         * @brief Process Async Message Calls.
         */
        void Listen_Async_Messages();


        /// Class Name
        std::string m_class_name;


        /// List of Render Windows
        std::vector<An_ASCII_Render_Window_Base::ptr_t> m_window_list;


        /// List of CLI Detailed Help Windows
        std::vector<A_Detailed_Help_Window::ptr_t> m_help_windows;

        /// Current Window Index
        int m_current_window;

        /// Flag if we need to show the help windows
        bool m_help_window_mode;

        /// Refresh Mutex
        std::mutex m_refresh_mutex;

        /// Start Timer
        bool m_async_message_sent;
        
        std::thread m_async_message_thread;
        bool m_async_message_thread_running;
        std::condition_variable m_async_message_cv;
        std::mutex m_async_message_mtx;

        std::chrono::milliseconds m_async_message_sleep_time;


}; // End of A_Render_Manager_ASCII Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
