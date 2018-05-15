/**
 * @file    A_Socket_Base_Instance.hpp
 * @author  Marvin Smith
 * @date    7/7/2015
*/
#ifndef CLI_CPP_LIB_CLI_A_SOCKET_BASE_INSTANCE_HPP
#define CLI_CPP_LIB_CLI_A_SOCKET_BASE_INSTANCE_HPP

// C++ Standard Libraries
#include <memory>
#include <mutex>
#include <string>

// CLI Libraries
#include "../core/A_Session.hpp"
#include "../core/SessionType.hpp"
#include "../render/A_Render_Manager_Base.hpp"


namespace CLI{


class A_Socket_Instance_Config_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Socket_Instance_Config_Base> ptr_t;
        
        
        /**
         * @brief Constructor
         *
         * @param read_sleep_timeout
         */
        A_Socket_Instance_Config_Base( std::chrono::microseconds  read_sleep_timeout );
        
        
        /**
         * @brief Get the session-type
         */
        virtual CORE::SessionType Get_Session_Type()const = 0;
        
        
        /**
         * @brief Get the Read Sleep Timeout
         */
        inline std::chrono::microseconds Get_Read_Sleep_Timeout()const{
            return m_read_sleep_timeout;
        }
        
        
        /**
         * @brief Print to Log String
         */
        virtual std::string To_Log_String( int indent )const = 0;
        
    private:
        
        /// Class-Name
        std::string m_class_name;
        
        /// Read-Sleep Timeout
        std::chrono::microseconds m_read_sleep_timeout;
};

/**
 * @class A_Socket_Base_Instance
*/
class A_Socket_Base_Instance
{
    
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Socket_Base_Instance> ptr_t;
        
        
        /**
         * @brief Constructor
         *
         * @param[in] instance Instance ID of the client.
         * @param[in] client_fd Socket File Descriptor of Client.
         */
        A_Socket_Base_Instance( A_Socket_Instance_Config_Base::ptr_t  config,
                                int                                   instance_id,
                                const CORE::Session&                  session,
                                int                                   client_fd );
        
        
        
        
        /**
         * @brief Run
        */
        virtual void Run() = 0;
        
        
        /**
         * @brief Start Thread
         */
        void Start();
        
        
        /**
         * @brief Join the Thread.
        */
        void Join();
        
        
        /**
         * @brief Set the Connection Flag
        */
        void Set_Connection_Flag( const int& connect_flag ){
            m_is_connected = connect_flag;
        }
        
        /**
         * @brief Check if Running.
        */
        inline bool Is_Running()const{
            return m_is_running;
        }
        
        
        /**
         * @brief Refresh the Screen
        */
        virtual void Refresh_Screen() = 0;
        
        
        /**
         * @brief Get Session Info
         */
        inline CORE::Session Get_Session_Info()const{
            return m_session;
        }
    
    protected:
        
        /// Instance ID
        int m_instance_id;
        
        /// Session Info
        CORE::Session m_session;
        
        /// Client File Descriptor
        int m_client_fd;
        
        /// Internal Thread
        std::thread m_thread;
        
        /// Flag if running
        bool m_is_running;
        
        /// Flag if Connected
        bool m_is_connected;
        
    private:
        
        
        /// Class Name
        std::string m_class_name;
        
        // Configuration
        A_Socket_Instance_Config_Base::ptr_t m_config;
        
}; // End of A_Socket_Base_Instance Class


} // End of CLI Namespace

#endif
