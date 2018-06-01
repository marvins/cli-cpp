/**
 * @file    A_Connection_Manager_Socket.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Connection_Manager_Socket.hpp"

// CLI Libraries
#include "A_Connection_Manager_Socket_Config.hpp"
#include "A_Socket_JSON_Instance.hpp"
#include "A_Socket_Telnet_Instance.hpp"
#include "../event/Event_Manager.hpp"
#include "../render/A_Render_Manager_ASCII.hpp"
#include "../utility/ANSI_Utilities.hpp"
#include "../utility/Log_Utilities.hpp"
#include "../utility/Telnet_Utilities.hpp"


// C++ Standard Libraries
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


namespace CLI{


/*************************/
/*      Constructor      */
/*************************/
A_Connection_Manager_Socket::A_Connection_Manager_Socket( A_Connection_Manager_Base_Config::ptr_t configuration )
  : A_Connection_Manager_Base(configuration),
    m_class_name("A_Connection_Manager_Socket")
{
    // Cast the configuration
    m_configuration = std::dynamic_pointer_cast<A_Connection_Manager_Socket_Config>(configuration);

    // Configure the socket
    Setup_Socket();

}


/*****************************/
/*       Destructor          */
/*****************************/
A_Connection_Manager_Socket::~A_Connection_Manager_Socket()
{
}


/********************************************/
/*          Configure the SOcket            */
/********************************************/
void A_Connection_Manager_Socket::Setup_Socket()
{

    // Setup the socket
    m_sock_fd = socket( AF_INET, SOCK_STREAM, 0 );
    if( m_sock_fd < 0 ){
        std::cerr << "error opening socket" << std::endl;
        return;
    }

    // Configure the socket
    int optionFlag = 1;
    if( setsockopt( m_sock_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&optionFlag, sizeof(int)) < 0 ){
        std::cerr << "error setting SO_REUSEADDR" << std::endl;
        return;
    }


    // Make the socket non-blocking
    fcntl( m_sock_fd, F_SETFL, O_NONBLOCK );


    // configure the endpoint
    struct sockaddr_in serv_addr;
    bzero((char *) &serv_addr, sizeof(serv_addr));
    
    // Get the port number
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(m_configuration->Get_Port());

    // Bind the socket
    if( bind( m_sock_fd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0 ){
        std::cerr << "error binding socket" << std::endl;
        return;
    }

    // Listen
    if( listen( m_sock_fd, 5 ) < 0 ){
        std::cerr << "error listening on socket." << std::endl;
        return;
    }

}


/********************************/
/*       Close the socket       */
/********************************/
void A_Connection_Manager_Socket::Close_Socket()
{
    close( m_sock_fd );
}


/****************************************/
/*          Print to Log String         */
/****************************************/
std::string A_Connection_Manager_Socket::To_Log_String(int offset) const
{
    std::string gap(offset, ' ');

    std::stringstream sin;

    sin << gap << " - " << m_class_name << std::endl;
    sin << gap << "     - Session-Type: " << CORE::SessionTypeToString(m_configuration->Get_Session_Type()) << "\n";
    sin << gap << "     - Connection-Type: " << CORE::ConnectionTypeToString(m_configuration->Get_ConnectionType()) << "\n";
    sin << gap << "     - Is-Running: " << std::boolalpha << m_is_running << std::endl;
    sin << gap << "     - Connection List (Size: " + std::to_string(m_connection_list.size()) + ")\n";
    for( auto conn : m_connection_list )
    {
    }

    return sin.str();
}


/***********************************************/
/*          Run the message handler            */
/***********************************************/
void A_Connection_Manager_Socket::Run_Handler()
{

    // Log Entry
    CLI_LOG_CLASS_ENTRY();

    // Get the length
    const std::string log_tag = "SessionType: " + CORE::SessionTypeToString(m_configuration->Get_Session_Type());
    socklen_t clilen;
    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    
    //  Iteratively load connections
    while( m_is_running )
    {
        // Spawn a new instance
        int client_fd;

        // Accept the socket
        LOG_TRACE( log_tag + ", Waiting for connection.  (Socket FD: " + std::to_string(m_sock_fd) + ")");
        client_fd = accept( m_sock_fd, 
                            (struct sockaddr*)&cli_addr,
                            &clilen);
            
        // Check if we need to exit
        if( m_is_running != true ){
            close(client_fd);
            continue;
        }

        // Check if the operation failed
        if( client_fd < 0 ){
            sleep(1);
            continue;
        }

        // Make the socket non-blocking
        fcntl( client_fd, F_SETFL, O_NONBLOCK );
    
        
        // Log
        char host[NI_MAXHOST];
        getnameinfo( (struct sockaddr *)&cli_addr, 
                     sizeof(cli_addr), 
                     host, 
                     sizeof(host), 
                     NULL, 
                     0, 
                     NI_NUMERICHOST);

        // Log Connection
        LOG_DEBUG(log_tag + ", Connection has been made by " + std::string(host));


        // Call the process method
        int next_position = Get_Next_Client_Slot();
        
        // Make sure we are not past the max number
        if( next_position < 0 ){
            LOG_DEBUG( log_tag + ", Connection is rejected as max number of connections reached.");
            continue;
        }

        
        // Log the Creation
        LOG_DEBUG( log_tag + ", Starting the Socket Connection for ID " + std::to_string(next_position) + ".");
        
        // Add new Connection Instance
        CORE::Session session( next_position, 
                               CORE::ConnectionType::SOCKET );
        session.Add_Connection_Data_Entry("IP_ADDRESS", std::string(host));

        A_Socket_Base_Instance::ptr_t new_connection = nullptr;

        switch(m_configuration->Get_Session_Type())
        {
            case CORE::SessionType::JSON:
                new_connection = std::make_shared<A_Socket_JSON_Instance>( m_configuration->Get_Instance_Config(),
                                                                           next_position,
                                                                           session,
                                                                           client_fd );
                break;

            case CORE::SessionType::TELNET:
                new_connection = std::make_shared<A_Socket_Telnet_Instance>( m_configuration->Get_Instance_Config(),
                                                                             next_position,
                                                                             session,
                                                                             client_fd );
                break;

            default:
                LOG_FATAL("Unsuported Session-Type: " + CORE::SessionTypeToString(m_configuration->Get_Session_Type()));
        }

        
        // Process Event
        //CORE::SessionEvent new_session_event( session,
        //                                      CORE::SessionEventType::CONNECT );
        //EVT::Event_Manager::Process_Event( 
        
        
        // Start
        new_connection->Start();
        m_connection_list[next_position] = new_connection;
                                                                                           
    } 

    // Set the running flag
    m_is_running = false;

    // Stop each connection
    for( auto conn : m_connection_list )
    {
        conn.second->Set_Connection_Flag(false);
        conn.second->Join();
    }

    // Close Socket
    Close_Socket();

    // Log Exit
    CLI_LOG_CLASS_EXIT();
}


/************************************/
/*       Refresh all Screens        */
/************************************/
void A_Connection_Manager_Socket::Refresh_Screens()
{
    // Iterate over each instance
    for( size_t i=0; i<m_connection_list.size(); i++ )
    {
        if( m_connection_list[i] != nullptr &&
            m_connection_list[i]->Is_Running() )
        {
            Refresh_Screen( i );
        }
    }

}


/*********************************/
/*       Refresh the screen      */
/*********************************/
void A_Connection_Manager_Socket::Refresh_Screen( int instance_id )
{
    // Log Entry
    LOG_TRACE("Start of Method. Instance-ID: " + std::to_string(instance_id));

    // If Instance-ID is -1, then iterate
    if( instance_id < 0 )
    {
        for( auto connection : m_connection_list )
        {
            if( connection.second != nullptr &&
                connection.second->Is_Running() )
            {
                connection.second->Refresh_Screen();
            }
            else {
                LOG_ERROR("Why are we hare?");
            }
        }
    }

    // Otherwise, 
    else if( m_connection_list.find(instance_id) != m_connection_list.end() )
    {
        if( m_connection_list[instance_id] == nullptr ||
            !m_connection_list[instance_id]->Is_Running() )
        {
            m_connection_list.erase(instance_id);
        }else {
            m_connection_list[instance_id]->Refresh_Screen();
        }
    }
    else
    {
        LOG_TRACE("Connection-Manager does not have Instance-ID: " + std::to_string(instance_id) + ".");
    }
    
    // Log Exit
    LOG_TRACE("End of Method. Instance-ID: " + std::to_string(instance_id));
}


/*************************************************/
/*          Get list of active sessions          */
/*************************************************/
std::vector<CORE::Session> A_Connection_Manager_Socket::Get_Active_Session_List()const
{
    // Create output list
    std::vector<CORE::Session> output;

    for( auto conn : m_connection_list )
    {
        // Check if null
        if( conn.second == nullptr )
        {

        }

        // Otherwise, continue
        else
        {
            output.push_back(conn.second->Get_Session_Info());
        }
    }

    // Return session info
    return output;
}


/********************************************/
/*          Set the connection flag         */
/********************************************/
void A_Connection_Manager_Socket::Set_Is_Connected_Flag( int  instance,
                                                         bool is_connected)
{
    // Check if instance is in this manager
    if( m_connection_list.find(instance) == m_connection_list.end() ){
        LOG_TRACE("Skipping as Connection-Manager does not contain instance.");
    } else {
        m_connection_list[instance]->Set_Connection_Flag(is_connected);
    }
    // If it is false, we should take down
}


/*****************************************************/
/*          Get the Next Open Client Slot            */
/*****************************************************/
int A_Connection_Manager_Socket::Get_Next_Client_Slot()
{
    // Make sure we are not past the max number of connections
    if( (int)m_connection_list.size() > m_configuration->Get_Max_Connections() ){
        return -1;
    }

    return EVT::Event_Manager::Request_Instance_ID();
}

} // End of CLI Namespacee

