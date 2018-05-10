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
#include "../render/A_Render_Manager_Base.hpp"


namespace CLI{


class A_Socket_Instance_Config_Base
{
    public:
        
        /**
         * @brief Constructor
         *
         * @param instance
         * @param session
         * @param client_fd
         * @param read_sleep_timeout
         */
        A_Socket_Instance_Config_Base( std::chrono::microseconds  read_sleep_timeout );
        
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
        A_Socket_Base_Instance( const A_Socket_Instance_Config_Base& instance_config,
                                int                        instance,
                                const CORE::Session&       session,
                                int                        client_fd );
        
        
        /**
         * @brief Destructor
        */
        virtual ~A_Socket_Telnet_Instance();
        
        
        /**
         * @brief Run
        */
        void Run();
        
        
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
        void Refresh_Screen();
        
        
        /**
         * @brief Get Session Info
         */
        inline CORE::Session Get_Session_Info()const{
            return m_session;
        }
    
    
    private:
        
        /**
         * @brief Check for special keys.
         *
         * @param[in]  key_str String of digits from system.
         *
         * @return Key value.  -1 if no key present.
        */
        int Process_Special_Key( std::string const& key_str ) const;
        
        
        /**
         * @brief Configure the Special Key List.
        */
        void Configure_Special_Key_List();
        
        
        /// Class Name
        std::string m_class_name;
        
        /// Internal Thread
        std::thread m_thread;
        
        /// Instance ID
        int m_instance_id;
        
        /// Session Info
        CORE::Session m_session;
        
        /// Client File Descriptor
        int m_client_fd;
        
        /// Read Sleep Timeout Microseconds
        int m_read_sleep_timeout_usec;
        
        /// Flag if running
        bool m_is_running;
        
        /// Flag if Connected
        bool m_is_connected;
        
        /// Local Render Manager Instance
        RENDER::A_Render_Manager_Base::ptr_t m_render_manager;
        
        /// Keyboard Special Key Map
        std::vector<std::tuple<std::string,int>> m_special_key_list;
        
        /// Refresh Screen Mutex Lock
        std::mutex m_refresh_lock;
        
        /// Skip the Rendering
        bool m_skip_render;
        
        bool m_first_command_received;
    
}; // End of A_Socket_Base_Instance Class


} // End of CLI Namespace

#endif