/**
 * @file    A_Socket_Connection_Instance.hpp
 * @author  Marvin Smith
 * @date    7/7/2015
*/
#ifndef __CLI_CPP_LIB_CLI_A_SOCKET_CONNECTION_INSTANCE_HPP__
#define __CLI_CPP_LIB_CLI_A_SOCKET_CONNECTION_INSTANCE_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>

// CLI Libraries
#include "../render/A_Render_Manager_Base.hpp"


namespace CLI{

/**
 * @class A_Socket_Connection_Instance
*/
class A_Socket_Connection_Instance
{

    public:

        /// Pointer Type
        typedef std::shared_ptr<A_Socket_Connection_Instance> ptr_t;


        /**
         * @brief Constructor
         * 
         * @param[in] instance Instance ID of the client.
         * @param[in] client_fd Socket File Descriptor of Client.
         */
        A_Socket_Connection_Instance( const int& instance,
                                      const int& client_fd );

        
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


    private:

        /// Class Name
        std::string m_class_name;
        
        /// Internal Thread
        std::thread m_thread;

        /// Instance ID
        int m_instance_id;

        /// Client File Descriptor
        int m_client_fd;
        
        /// Flag if running
        bool m_is_running;

        /// Flag if Connected
        bool m_is_connected;
    
        /// Local Render Manager Instance
        RENDER::A_Render_Manager_Base::ptr_t m_render_manager; 

}; // End of A_Socket_Connection_Instance_Class


} // End of CLI Namespace

#endif

