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


// Keyboard Delete Key Value
const std::string TELNET_JUNK   = { (char)-1, (char)-3, (char)3, (char)-1, (char)-5, (char)34, (char)-1, (char)-6, (char)34, (char)3, (char)1, (char)3 };
const std::string KEYBOARD_DELETE_KEY = "\033\133\063\176";
const std::string KEYBOARD_LEFT_KEY   = "\033\133\104";
const std::string KEYBOARD_RIGHT_KEY  = "\033\133\103";
const std::string KEYBOARD_UP_KEY     = "\033\133\101";
const std::string KEYBOARD_DOWN_KEY   = "\033\133\102";
const std::string KEYBOARD_PG_UP_KEY  = "\033\133\065\176";
const std::string KEYBOARD_PG_DN_KEY  = "\033\133\066\176";
const std::string KEYBOARD_HOME_KEY   = "\033\133\110";
const std::string KEYBOARD_END_KEY    = "\033\133\106";
const std::string KEYBOARD_INSERT_KEY = "\033\133\062";
const std::string KEYBOARD_F1_KEY     = "\033\117\120";
const std::string KEYBOARD_F2_KEY     = "\033\117\121";
const std::string KEYBOARD_F3_KEY     = "\033\117\122";
const std::string KEYBOARD_F4_KEY     = "\033\117\123";
const std::string KEYBOARD_F5_KEY     = "\033\117\124";

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

    // Configure Special Key List
    Configure_Special_Key_List();

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
    //fcntl( m_sock_fd, F_SETFL, O_NONBLOCK );


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
        BOOST_LOG_TRIVIAL(debug) << "Waiting for connection";
        client_fd = accept( m_sock_fd, 
                            (struct sockaddr*)&cli_addr,
                            &clilen);
            
        // Check if we need to exit
        if( m_is_running != true ){
            close(client_fd);
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
        BOOST_LOG_TRIVIAL(debug) << "Connection has been made by " << host;



        // Call the process method
        int next_position = Get_Next_Client_Slot();
        m_connection_list[next_position] = std::make_shared<A_Socket_Connection_Instance>( next_position,
                                                                                           client_fd ); 
                                                                                           
    } 

    // Set the running flag
    m_is_running = false;

    // Close Socket
    Close_Socket();

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/*********************************/
/*       Refresh the screen      */
/*********************************/
void A_Connection_Manager_Socket::Refresh_Screen( const int& instance_id )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    if( m_connection_list[instance_id] != nullptr && 
        m_connection_list[instance_id]->Is_Running() ){
        m_connection_list[instance_id]->Refresh_Screen(); 
    }
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}

/********************************************/
/*      Configure the Special Key Map       */
/********************************************/
void A_Connection_Manager_Socket::Configure_Special_Key_List()
{
    // Add each keyboard to event mapping here
    m_special_key_list.push_back( std::make_tuple( TELNET_JUNK,          (int)CLI_Event_Type::CLI_NULL             ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_DELETE_KEY,  (int)CLI_Event_Type::KEYBOARD_DELETE_KEY  ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_LEFT_KEY,    (int)CLI_Event_Type::KEYBOARD_LEFT_ARROW  ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_RIGHT_KEY,   (int)CLI_Event_Type::KEYBOARD_RIGHT_ARROW ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_UP_KEY,      (int)CLI_Event_Type::KEYBOARD_UP_ARROW    ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_DOWN_KEY,    (int)CLI_Event_Type::KEYBOARD_DOWN_ARROW  ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_PG_UP_KEY,   (int)CLI_Event_Type::KEYBOARD_PG_UP       ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_PG_DN_KEY,   (int)CLI_Event_Type::KEYBOARD_PG_DN       ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_HOME_KEY,    (int)CLI_Event_Type::KEYBOARD_HOME        ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_END_KEY,     (int)CLI_Event_Type::KEYBOARD_END         ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_INSERT_KEY,  (int)CLI_Event_Type::KEYBOARD_INSERT      ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F1_KEY,      (int)CLI_Event_Type::KEYBOARD_F1          ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F2_KEY,      (int)CLI_Event_Type::KEYBOARD_F2          ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F3_KEY,      (int)CLI_Event_Type::KEYBOARD_F3          ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F4_KEY,      (int)CLI_Event_Type::KEYBOARD_F4          ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F5_KEY,      (int)CLI_Event_Type::KEYBOARD_F5          ));

}

/**************************************/
/*        Process Special Keys        */
/**************************************/
int A_Connection_Manager_Socket::Process_Special_Key( const std::string& input_str )const
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
    
    // Iterate over list
    for( size_t i=0; i<m_special_key_list.size(); i++ ){
        if( input_str == std::get<0>(m_special_key_list[i]) ){
            return std::get<1>(m_special_key_list[i]);
        }
    }

    // Otherwise, there was an error
    std::stringstream sin;
    sin  << "Warning, data is larger than expected. Size: " << input_str.size() << std::endl;
    for( size_t i=0; i<input_str.size(); i++ ){
        sin << i << " : " << (int)input_str[i] << std::endl;
    }
    BOOST_LOG_TRIVIAL(warning) << sin.str();

    // otherwise, return failure
    return (int)CLI_Event_Type::UNKNOWN;
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

    // If we get here, push another open spot
    m_connection_list.push_back(nullptr);
    return (m_connection_list.size()-1);
}

} // End of CLI Namespacee

