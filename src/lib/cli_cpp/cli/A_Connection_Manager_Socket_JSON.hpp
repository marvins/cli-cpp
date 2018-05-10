/**
 * @file    A_Connection_Manager_Socket_JSON.hpp
 * @author  Marvin Smith
 * @date    5/9/2018
*/
#ifndef __CLI_A_CLI_CONNECTION_MANAGER_SOCKET_JSON_HPP__
#define __CLI_A_CLI_CONNECTION_MANAGER_SOCKET_JSON_HPP__

// CLI Libraries
#include "A_Connection_Manager_Base.hpp"
#include "A_Connection_Manager_Base_Config.hpp"
#include "A_Connection_Manager_Socket_JSON_Config.hpp"

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
 * @class A_Connection_Manager_Socket_JSON
 */
class A_Connection_Manager_Socket_JSON : public A_Connection_Manager_Base
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Connection_Manager_Socket_JSON> ptr_t;

        
        /**
         * @brief Constructor
         *
         * @param[in] configuration Connection manager configuration.
        */
        A_Connection_Manager_Socket_JSON( A_Connection_Manager_Base_Config::ptr_t configuration );


        /**
         * @brief Destructor
         */
        virtual ~A_Connection_Manager_Socket_JSON();
        

        /**
         * @brief Refresh the Screen.
         *
         * @param[in] instance Client instance to refresh.
         */
        virtual void Refresh_Screen( const int& instance );
        
        
        /**
         * @brief Refresh all Instances
        */
        virtual void Refresh_Screens();

        
        /**
         * @brief Set the Is Connection Flag
        */
        inline virtual void Set_Is_Connected_Flag( int const& instance,
                                                   const bool& is_connected )
        {
        }

        
        /**
         * @brief Get a list of active connections.
         *
         * @return session list.
         */
        virtual std::vector<CORE::Session> Get_Active_Session_List()const;
    

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
         * @brief Get next open client slot.
         */
        int Get_Next_Client_Slot();
        

        
        /// Class Name
        std::string m_class_name;


        /// Configuration
        A_Connection_Manager_Socket_JSON_Config::ptr_t m_configuration;


        /// Socket File Descriptor
        int m_sock_fd;

}; // End of A_Connection_Manager_Socket_JSON Class

} // End of CLI Namespace

#endif