/**
 * @file    A_Connection_Manager_Socket.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef CLI_A_CLI_CONNECTION_MANAGER_SOCKET_HPP
#define CLI_A_CLI_CONNECTION_MANAGER_SOCKET_HPP

// CLI Libraries
#include "A_Connection_Manager_Base.hpp"
#include "A_Connection_Manager_Base_Config.hpp"
#include "A_Connection_Manager_Socket_Config.hpp"
#include "A_Socket_Telnet_Instance.hpp"

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
         *
         * @param[in] configuration Connection manager configuration.
        */
        A_Connection_Manager_Socket( A_Connection_Manager_Base_Config::ptr_t configuration );


        /**
         * @brief Destructor
         */
        virtual ~A_Connection_Manager_Socket();
        

        /**
         * @brief Refresh the Screen.
         *
         * @param[in] instance Client instance to refresh.
         */
        void Refresh_Screen( int instance ) override;
        
        
        /**
         * @brief Refresh all Instances
        */
        void Refresh_Screens() override;

        
        /**
         * @brief Set the Is Connection Flag
        */
        inline void Set_Is_Connected_Flag( int  instance,
                                           bool is_connected ) override
        {
            m_connection_list[instance]->Set_Connection_Flag( is_connected );

            // If it is false, we should take down
        }

        
        /**
         * @brief Get a list of active connections.
         *
         * @return session list.
         */
        virtual std::vector<CORE::Session> Get_Active_Session_List()const;


        /**
         * @brief Print Current STate
         */
        std::string To_Log_String( int offset ) const override;
    

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
        A_Connection_Manager_Socket_Config::ptr_t m_configuration;


        /// Socket File Descriptor
        int m_sock_fd;
       
        
        /// Socket Instance List (Key is the Instance-ID)
        std::map<int,A_Socket_Base_Instance::ptr_t> m_connection_list;

}; // End of A_Connection_Manager_Socket Class

} // End of CLI Namespace

#endif
