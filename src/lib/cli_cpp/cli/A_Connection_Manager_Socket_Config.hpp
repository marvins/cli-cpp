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
#include "A_Socket_Base_Instance.hpp"

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
        A_Connection_Manager_Socket_Config( int                                   port,
                                            int                                   max_connections,
                                            A_Socket_Instance_Config_Base::ptr_t instance_config );

        
        /**
         * @brief Get the port number.
         *
         * @return Port number.
         */
        inline int Get_Port()const{
            return m_port;
        }
       

        /**
         * @brief Get the Connection Type.
         *
         * @return ConnectionType.
        */
        inline CORE::ConnectionType Get_ConnectionType()const override{
            return CORE::ConnectionType::SOCKET;
        }


        /**
         * @brief Get the Session-Type
         * @return
         */
        inline CORE::SessionType Get_Session_Type()const override{
            if( m_instance_config == nullptr ){
                return CORE::SessionType::UNKNOWN;
            }
            return m_instance_config->Get_Session_Type();
        }


        /**
         * @brief Get the max number of connections.
         *
         * @return Max number of connections.
        */
        inline int Get_Max_Connections()const{
            return m_max_connections;
        }
        
        
        /**
         * @brief Get the Instance Config
         * @return
         */
        inline  A_Socket_Instance_Config_Base::ptr_t  Get_Instance_Config()const{
            return m_instance_config;
        }
        
        
        /**
         * @brief Print to Log String
         */
        std::string To_Log_String( int offset = 0 )const override;


    private:
        
        /// Class Name
        std::string m_class_name;
        
        /// Port Number
        int m_port;

        /// Max Connections
        int m_max_connections;
        
        A_Socket_Instance_Config_Base::ptr_t m_instance_config;

        
}; // End of A_Connection_Manager_Socket_Config Class

} // End of CLI Namespace

#endif
