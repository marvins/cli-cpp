/**
 * @file    A_Socket_JSON_Instance.hpp
 * @author  Marvin Smith
 * @date    5/15/2018
*/
#ifndef CLI_CPP_LIB_CLI_A_SOCKET_JSON_INSTANCE_HPP
#define CLI_CPP_LIB_CLI_A_SOCKET_JSON_INSTANCE_HPP

// C++ Standard Libraries
#include <memory>
#include <mutex>
#include <string>

// CLI Libraries
#include "../core/A_Session.hpp"
#include "../render/A_Render_Manager_Base.hpp"
#include "A_Socket_Base_Instance.hpp"

namespace CLI{


class A_Socket_Instance_Config_JSON : public A_Socket_Instance_Config_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Socket_Instance_Config_JSON> ptr_t;
        
        /**
         * @brief Constructor
         */
        A_Socket_Instance_Config_JSON( std::chrono::microseconds  read_sleep_timeout );
        
        
        /**
         * @brief Get the session-type
         */
        CORE::SessionType Get_Session_Type()const override{
            return CORE::SessionType::JSON;
        }
        
        
        /**
         * @brief Print to Log String
         */
        virtual std::string To_Log_String( int indent )const;
    
    
    private:
        
        /// Class-Name
        std::string m_class_name;
    
};

/**
 * @class A_Socket_JSON_Instance
*/
class A_Socket_JSON_Instance : public A_Socket_Base_Instance
{
    
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Socket_JSON_Instance> ptr_t;
        
        
        /**
         * @brief Constructor
         *
         * @param[in] instance Instance ID of the client.
         * @param[in] client_fd Socket File Descriptor of Client.
         */
        A_Socket_JSON_Instance( A_Socket_Instance_Config_Base::ptr_t  config,
                                int                                   instance_id,
                                const CORE::Session&                  session,
                                int                                   client_fd );
        
        
        /**
         * @brief Destructor
        */
        virtual ~A_Socket_JSON_Instance();
        
        
        /**
         * @brief Run
        */
        void Run() override;
        
        
        /**
         * @brief Refresh the Screen
        */
        void Refresh_Screen() override;
    
    
    private:
        
        
        /// Class Name
        std::string m_class_name;
        
        /// Configuration
        A_Socket_Instance_Config_JSON::ptr_t m_config;
        
        bool m_first_command_received;
    
}; // End of A_Socket_JSON_Instance


} // End of CLI Namespace

#endif

