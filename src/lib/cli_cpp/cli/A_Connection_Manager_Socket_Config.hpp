/**
 * @file    A_Connection_Manager_Socket_Config.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef __CLI_CPP_CLI_A_CONNECTION_MANAGER_SOCKET_CONFIG_HPP__
#define __CLI_CPP_CLI_A_CONNECTION_MANAGER_SOCKET_CONFIG_HPP__

// C++ Standard Libraries
#include <memory>

// CLI Libraries
#include "A_Connection_Manager_Base_Config.hpp"

namespace CLI{

/**
 * @class A_Connection_Manager_Socket_Config
*/
class A_Connection_Manager_Socket_Config : public A_Connection_Manager_Base_Config
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Connection_Manager_Socket_Config> ptr_t;

        /**
         * @brief Constructor
         *
         * @param[in] port Port number to configure the Connection-Manager's socket with.
         * @param[in] read_timeout_sleep_time_usec 
         * @param[in] max_connections
        */
        A_Connection_Manager_Socket_Config( const int& port,
                                            const int64_t& read_timeout_sleep_time_usec,
                                            const int&   max_connections );


        /**
         * @brief Destructor
        */
        ~A_Connection_Manager_Socket_Config();

        
        /**
         * @brief Get the port number.
         *
         * @return Port number.
         */
        inline int Get_Port()const
        {
            return m_port;
        }
       

        /**
         * @brief Get the Connection Type.
         *
         * @return ConnectionType.
        */
        inline virtual CORE::ConnectionType Get_ConnectionType()const{
            return CORE::ConnectionType::SOCKET;
        }


        /**
         * @brief Get the Read Timeout Sleep Time in Microseconds.
         *
         * @return Sleep time.
        */
        inline int64_t Get_Read_Timeout_Sleep_Microseconds()const{
            return m_read_timeout_sleep_usec;
        }


        /**
         * @brief Get the max number of connections.
         *
         * @return Max number of connections.
        */
        inline int Get_Max_Connections()const{
            return m_max_connections;
        }


    private:
        
        /// Class Name
        std::string m_class_name;

        
        /// Port Number
        int m_port;


        /// Read Timeout Sleep Time
        int64_t m_read_timeout_sleep_usec;


        /// Max Connections
        int m_max_connections;

        
}; // End of A_Connection_Manager_Socket_Config Class

} // End of CLI Namespace

#endif
