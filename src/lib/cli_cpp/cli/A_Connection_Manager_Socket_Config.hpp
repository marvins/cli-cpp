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
        */
        A_Connection_Manager_Socket_Config( const int& port,
                                            const int& socket_read_sleep_time_usec,
                                            const int& socket_read_max_wait_refresh_count) ;


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
          * @brief Get the socket read sleep time.
          *
          * @return Socket wait time in microseconds.
         */
         inline int Get_Socket_Read_Sleep_Time_USec()const{
             return m_socket_read_sleep_time_usec;
         }
    
    
        /**
         * @brief Get the socket read max wait refresh counter.
        */
        inline int Get_Socket_Max_Wait_Refresh_Count() const{
            return m_socket_read_max_wait_refresh_count;
        }

        
        /**
         * @brief Get the Connection Type.
         *
         * @return ConnectionType.
        */
        inline virtual CORE::ConnectionType Get_ConnectionType()const{
            return CORE::ConnectionType::SOCKET;
        }

    private:
        
        /// Class Name
        std::string m_class_name;
        
        /// Port Number
        int m_port;
        
        /// Socket Window Refresh Sleep Time in Microseconds
        int m_socket_read_sleep_time_usec;

        /// Socket Read Max Wait Refresh Count
        int m_socket_read_max_wait_refresh_count;

}; // End of A_Connection_Manager_Socket_Config Class

} // End of CLI Namespace

#endif
