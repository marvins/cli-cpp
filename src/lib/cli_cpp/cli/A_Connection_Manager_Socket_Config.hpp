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
        A_Connection_Manager_Socket_Config( const int& port );


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

    private:
        
        /// Class Name
        std::string m_class_name;

        
        /// Port Number
        int m_port;

}; // End of A_Connection_Manager_Socket_Config Class

} // End of CLI Namespace

#endif
