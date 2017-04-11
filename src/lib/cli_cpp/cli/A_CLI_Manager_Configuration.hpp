/**
 * @file    A_CLI_Manager_Configuration.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __CLI_A_CLI_MANAGER_CONFIGURATION_HPP__
#define __CLI_A_CLI_MANAGER_CONFIGURATION_HPP__

// C++ Standard Libraries
#include <string>

// CLI Libraries
#include "A_Connection_Manager_Base.hpp"
#include "A_Connection_Manager_Base_Config.hpp"
#include "../core/ConnectionType.hpp"
#include "../cmd/A_Command_Parser.hpp"
#include "../event/Event_Manager_Config.hpp"
#include "../render/A_Render_Driver_Context_Base.hpp"
#include "../render/A_Render_Manager_Base.hpp"


namespace CLI{


/**
 * @class A_CLI_Manager_Configuration
 *
 * @brief Configuration parameters required for the CLI-Manager.
 */
class A_CLI_Manager_Configuration{

    public:

        /**
         * @brief Constructor
         *
         * @param[in] conn_type Connection type.
         */
        A_CLI_Manager_Configuration( CORE::ConnectionType const& conn_type );


        /**
         * @brief Get the Communication Type
         *
         * @return Connection Type
         */
        inline CORE::ConnectionType Get_Connection_Type()const{
            return m_conn_type;
        }


        /**
         * @brief Set the Connection Type.
         *
         * @param[in] conn_type Connection Type.
         */
        inline void Set_Connection_Type( CORE::ConnectionType const& conn_type )
        {
            m_conn_type = conn_type;
        }


        /**
         * @brief Set the Connection Manager Configuration
         *
         * @param[in] configuration Configuration object to set.
         */
        inline void Set_Connection_Manager_Config( A_Connection_Manager_Base_Config::ptr_t configuration )
        {
            m_connection_manager_configuration = configuration;
        }

        /**
         * @brief Get the Connection-Manager Configuration.
         *
         * @return Connection-Manager configuration object.
        */
        inline A_Connection_Manager_Base_Config::ptr_t Get_Connection_Manager_Config()const{
            return m_connection_manager_configuration;
        }


        /**
         * @brief Get the Command Parser
         * 
         * @return Command Parser.
         */
        inline CMD::A_Command_Parser::ptr_t Get_Command_Parser()const{
            return m_command_parser;
        }


        /**
         * @brief Set the Command Parser
         */
        inline void Set_Command_Parser( CMD::A_Command_Parser::ptr_t command_parser ){
            m_command_parser = command_parser;
        }


        /**
         * @brief Set the CLI Title.
         *
         * @return CLI Title
         */
        inline std::string Get_CLI_Title()const{
            return m_cli_title;
        }


        /**
         * @brief Set the CLI Title
         *
         * @param[in] cli_title
         */
        inline void Set_CLI_Title( const std::string& cli_title ){
            m_cli_title = cli_title;
        }


        /**
         * @brief Get the CLI Command Queue Configuration.
         *
         * @return Command-Queue Configuration
         */
        inline CMD::A_Command_Queue_Config Get_Command_Queue_Config()const{
            return m_command_queue_config;
        }


        /**
         * @brief Set the Command Queue Configuration
         */
        inline void Set_Command_Queue_Config( const CMD::A_Command_Queue_Config& command_queue_config )
        {
            m_command_queue_config = command_queue_config;
        }


        /**
         * @brief Set the Event-Manager Configuration
         *
         * @param[in] event_manager_config
         */
        inline void Set_Event_Manager_Config( EVT::Event_Manager_Config const& event_manager_config ){
            m_event_manager_config = event_manager_config;
        }


        /**
         * @brief Get the Event-Manager Configuration
         *
         * @return Event Manager config
         */
        inline EVT::Event_Manager_Config Get_Event_Manager_Config()const{
            return m_event_manager_config;
        }


        /**
         * @brief Get the socket terminal window size
         */
        inline int Get_Socket_Window_Rows()const{
            return m_socket_window_rows;
        }


        /**
         * @brief Set the socket terminal window rows
         */
        inline void Set_Socket_Window_Rows( const int& socket_window_rows )
        {
            m_socket_window_rows = socket_window_rows;
        }


        /**
         * @brief Get the socket terminal window columns
         */
        inline int Get_Socket_Window_Cols()const{
            return m_socket_window_cols;
        }


        /**
         * @brief Set the socket terminal window columns
         */
        inline void Set_Socket_Window_Cols( const int& socket_window_cols )
        {
            m_socket_window_cols = socket_window_cols;
        }


        /**
         * @brief Check if the configuration is valid.
         *
         * @return True if valid, false otherwise.
         */
        bool Is_Valid()const;


        /**
         * @brief Set the Log Window Redirect Flags.
         *
         * @param[in] redirect_stdout Flag if we want to redirect stdout.
         * @param[in] redirect_stderr Flag if we want to redirect stderr.
         */
        inline void Set_Log_Window_Redirect_Flags( const bool& redirect_stdout,
                                                   const bool& redirect_stderr )
        {
            m_redirect_stdout = redirect_stdout;
            m_redirect_stderr = redirect_stderr;
        }

        /**
         * @brief Get the Redirect STDOUT Flag
        */
        inline bool Get_Redirect_stdout()const{
            return m_redirect_stdout;
        }


        /**
         * @brief Get the Redirect stderr flag
        */
        inline bool Get_Redirect_stderr()const{
            return m_redirect_stderr;
        }
        

        /**
         * @brief Set the CLI Async Message Refresh Time
         */
        inline void Set_Async_Message_Refresh_Time( const std::chrono::milliseconds& async_message_refresh_time ){
            m_async_message_refresh_time = async_message_refresh_time;
        }


        /**
         * @brief Get the CLI Async Message Refresh Time
         */
        inline std::chrono::milliseconds Get_Async_Message_Refresh_Time()const{
            return m_async_message_refresh_time;
        }


    private:

        /// Class Name
        std::string m_class_name;

        /// CLI Communication Type
        CORE::ConnectionType m_conn_type;

        /// Connection Manager Configuration
        A_Connection_Manager_Base_Config::ptr_t m_connection_manager_configuration;


        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;


        /// Event Manager Configuration
        EVT::Event_Manager_Config m_event_manager_config;


        /// Command-Line Title
        std::string m_cli_title;

        /// Command Queue Configuration
        CMD::A_Command_Queue_Config m_command_queue_config;

        /// Socket window rows
        int m_socket_window_rows;

        /// Socket window cols
        int m_socket_window_cols;

        /// Redirect stdout
        bool m_redirect_stdout;

        /// Redirect stderr
        bool m_redirect_stderr;
            
        /// Async Message Refresh Time
        std::chrono::milliseconds m_async_message_refresh_time;


}; // End of A_CLI_Manager_Configuration Class


} // End of CLI Namespace

#endif
