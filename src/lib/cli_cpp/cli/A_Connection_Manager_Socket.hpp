/**
 * @file    A_Connection_Manager_Socket.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef __CLI_A_CLI_CONNECTION_HANDLER_SOCKET_HPP__
#define __CLI_A_CLI_CONNECTION_HANDLER_SOCKET_HPP__

// CLI Libraries
#include "A_Connection_Manager_Base.hpp"
#include "A_Connection_Manager_Base_Config.hpp"
#include "A_Connection_Manager_Socket_Config.hpp"

// C++ Standard Libraries
#include <memory>
#include <sys/socket.h>
#include <mutex>
#include <netinet/in.h>
#include <netdb.h>
#include <tuple>
#include <unistd.h>


namespace CLI{

/**
 * @class A_Connection_Manager_Socket
 */
class A_Connection_Manager_Socket : public A_Connection_Manager_Base
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Connection_Manager_Socket> ptr_t;

        
        /**
         * @brief Constructor
        */
        A_Connection_Manager_Socket( A_Connection_Manager_Base_Config::ptr_t configuration,
                                     RENDER::A_Render_Manager_Base::ptr_t    render_manager );


        /**
         * @brief Destructor
         */
        ~A_Connection_Manager_Socket();
        

        /**
         * @brief Refresh the Screen.
         */
        virtual void Refresh_Screen();
        
        
        /**
         * @brief Set the Is Connection Flag
        */
        inline virtual void Set_Is_Connected_Flag( const bool& is_connected ){
            m_is_connected = is_connected;
        }

    
    protected:
        
        /**
         * @brief Run the message handler
         */
        virtual void Run_Handler();


    private:

        /**
         * @brief Setup the socket.
         */
        void Setup_Socket();


        /**
         * @brief Close the socket.
         */
        void Close_Socket();
        

        /**
         * @brief Configure the Special Key List.
        */
        void Configure_Special_Key_List();


        /**
         * @brief Check for special keys.
         *
         * @param[in]  key_str String of digits from system.
         *
         * @return Key value.  -1 if no key present.
        */
        int Process_Special_Key( std::string const& key_str ) const;
       

        /// Class Name
        std::string m_class_name;


        /// Configuration
        A_Connection_Manager_Socket_Config::ptr_t m_configuration;


        /// Socket File Descriptor
        int m_sock_fd;


        /// Client File Description
        int m_client_fd;


        /// Keyboard Special Key Map
        std::vector<std::tuple<std::string,int>> m_special_key_list;


        /// Refresh Lock
        std::mutex m_refresh_lock;

}; // End of A_Connection_Manager_Socket Class

} // End of CLI Namespace

#endif
