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
#include <netinet/in.h>
#include <netdb.h>

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

}; // End of A_Connection_Manager_Socket Class

} // End of CLI Namespace

#endif
