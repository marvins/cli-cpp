/**
 * @file    A_Connection_Manager_Socket.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Connection_Manager_Socket.hpp"

// CLI Libraries
#include "A_Connection_Manager_Socket_Config.hpp"
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


/***********************************************/
/*          Run the message handler            */
/***********************************************/
void A_Connection_Manager_Socket::Run_Handler()
{

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Get the length
    socklen_t clilen;
    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    
    //  Iteratively load connections
    while( m_is_running == true )
    {
        // Spawn a new instance
        int client_fd;

        // Accept the socket
        BOOST_LOG_TRIVIAL(trace) << "Waiting for connection.  (Socket FD: " << m_sock_fd << ")";
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
        CLI_LOG_CLASS( debug,
                       "Connection has been made by " + std::string(host));


        // Call the process method
        int next_position = Get_Next_Client_Slot();
        
        // Make sure we are not past the max number
        if( next_position < 0 )
        {
            CLI_LOG_CLASS( debug,
                           "Connection is rejected as max number of connections reached.");
            continue;
        }

        
        // Log the Creation
        BOOST_LOG_TRIVIAL(debug) << "Starting the Socket Connection for ID " << next_position << ".";
        
        // Add new Connection Instance
        CORE::Session session( next_position, 
                               CORE::ConnectionType::SOCKET );
        session.Add_Connection_Data_Entry("IP_ADDRESS", std::string(host));

        m_connection_list[next_position] = std::make_shared<A_Socket_Connection_Instance>( next_position,
                                                                                           session,
                                                                                           client_fd,
                                                                                           m_configuration->Get_Read_Timeout_Sleep_Microseconds()); 

        
        // Process Event
        //CORE::SessionEvent new_session_event( session,
        //                                      CORE::SessionEventType::CONNECT );
        //EVT::Event_Manager::Process_Event( 
        
        
        // Start
        m_connection_list[next_position]->Start();
                                                                                           
    } 

    // Set the running flag
    m_is_running = false;

    // Stop each connection
    for( size_t i=0; i<m_connection_list.size(); i++ )
    {
        m_connection_list[i]->Set_Connection_Flag(false);
        m_connection_list[i]->Join();
    }

    // Close Socket
    Close_Socket();

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
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
void A_Connection_Manager_Socket::Refresh_Screen( const int& instance_id )
{
    // Log Entry
    CLI_LOG_CLASS( trace,
                   "Start of Method. Instance-ID: " + std::to_string(instance_id));
    
    // If Instance-ID is -1, then iterate
    if( instance_id < 0 )
    {
        for( auto connection : m_connection_list )
        {
            if( connection != nullptr &&
                connection->Is_Running() )
            {
                connection->Refresh_Screen();
            }
        }
    }

    // Otherwise, 
    else
    {
        if( m_connection_list[instance_id] != nullptr && 
            m_connection_list[instance_id]->Is_Running() )
        {
            m_connection_list[instance_id]->Refresh_Screen(); 
        }
    }
    
    // Log Exit
    CLI_LOG_CLASS( trace,
                   "End of Method. Instance-ID: " + std::to_string(instance_id));
}


/*************************************************/
/*          Get list of active sessions          */
/*************************************************/
std::vector<CORE::Session> A_Connection_Manager_Socket::Get_Active_Session_List()const
{
    // Create output list
    std::vector<CORE::Session> output;
    
    for( size_t i=0; i<m_connection_list.size(); i++ ){
        
        // Check if null
        if( m_connection_list[i] == nullptr )
        {

        }

        // Otherwise, continue
        else
        {
            output.push_back(m_connection_list[i]->Get_Session_Info());
        }
    }

    // Return session info
    return output;
}


/*****************************************************/
/*          Get the Next Open Client Slot            */
/*****************************************************/
int A_Connection_Manager_Socket::Get_Next_Client_Slot()
{

    // Iterate over existing items
    for( size_t i=0; i<m_connection_list.size(); i++ ){

        // Look for dead thread
        if( m_connection_list[i] == nullptr ){
            return i;
        }
        else if( m_connection_list[i]->Is_Running() == false ){
            return i;
        }
    }
    
    // Make sure we are not past the max number of connections
    if( (int)m_connection_list.size() > m_configuration->Get_Max_Connections() ){
        return -1;
    }

    // If we get here, push another open spot
    m_connection_list.push_back(nullptr);
    return (m_connection_list.size()-1);
}

} // End of CLI Namespacee

