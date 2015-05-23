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
#include "../thirdparty/ncurses/NCurses_Utilities.hpp"

namespace CLI{


/**
 * @class A_CLI_Manager_Configuration
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
         * @brief Get the Connection Manager Configuration
         *
         * @return Connection Manager Configuration.
         */
        A_Connection_Manager_Base::ptr_t  Get_Connection_Manager()const;

        
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
         * @brief Get the CLI Command Queue Max Size
        */
        inline int Get_Command_Queue_Max_Size()const{
            return m_command_queue_max_size;
        }


        /**
         * @brief Set the Command Queue Max Size
        */
        inline void Set_Command_Queue_Max_Size( const int& command_queue_max_size )
        {
            m_command_queue_max_size = command_queue_max_size;
        }


        /**
         * @brief Create NCurses Context.
         *
         * @return NCurses Context.
         */
         NCURSES::An_NCurses_Context::ptr_t Create_NCurses_Context()const;
         
        
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


    private:
        
        /// Class Name
        std::string m_class_name;

        /// CLI Communication Type
        CORE::ConnectionType m_conn_type;

        /// Connection Manager Configuration
        A_Connection_Manager_Base_Config::ptr_t m_connection_manager_configuration;

        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;
        
        /// Command-Line Title
        std::string m_cli_title;
            
        /// Command Queue Max Size
        int m_command_queue_max_size;

        /// Socket window rows
        int m_socket_window_rows;


        /// Socket window cols
        int m_socket_window_cols;


}; // End of A_CLI_Manager_Configuration Class


} // End of CLI Namespace

#endif
