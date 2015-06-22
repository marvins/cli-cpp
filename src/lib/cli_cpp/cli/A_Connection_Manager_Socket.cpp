/**
 * @file    A_Connection_Manager_Socket.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Connection_Manager_Socket.hpp"

// CLI Libraries
#include "A_Connection_Manager_Socket_Config.hpp"
#include "../core/Event_Manager.hpp"
#include "../render/A_Render_Manager_ASCII.hpp"
#include "../utility/Log_Utilities.hpp"


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
const std::string KEYBOARD_F1_KEY     = "\033\117\120";
const std::string KEYBOARD_F2_KEY     = "\033\117\121";
const std::string KEYBOARD_F3_KEY     = "\033\117\122";
const std::string KEYBOARD_F4_KEY     = "\033\117\123";
const std::string KEYBOARD_F5_KEY     = "\033\117\124";

namespace CLI{


/*************************/
/*      Constructor      */
/*************************/
A_Connection_Manager_Socket::A_Connection_Manager_Socket( A_Connection_Manager_Base_Config::ptr_t configuration,
                                                          RENDER::A_Render_Manager_Base::ptr_t    render_manager )
  : A_Connection_Manager_Base(render_manager),
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
    
    // Misc Variables
    int key;

    // Read the socket
    char buffer[256];
    int n;
    std::string input;

    // Get the sleep time and refresh counter
    int read_sleep_time_usec = m_configuration->Get_Socket_Read_Sleep_Time_USec();
    int refresh_counter_max  = m_configuration->Get_Socket_Max_Wait_Refresh_Count();
    int refresh_counter = 0;

    // Get the length
    socklen_t clilen;
    struct sockaddr_in cli_addr;
    clilen = sizeof(cli_addr);
    
    //  Iteratively load connections
    while( m_is_running == true )
    {

        // Wait until a valid connection
        while( true ){
        
            // Accept the socket
            m_client_fd = accept( m_sock_fd, 
                                  (struct sockaddr*)&cli_addr,
                                  &clilen);
            
            // Check if we need to keep waiting
            if( m_client_fd < 0 && m_is_running == true )
            {
                usleep(1000);
                continue;
            }

            // Check the status
            if( m_is_running != true || 
                m_client_fd != EAGAIN )
            {
                break;
            }
        }

        // Check if we need to exit
        if( m_is_running != true ){
            close(m_client_fd);
            break;
        }

        // Make the socket non-blocking
        fcntl( m_client_fd, F_SETFL, O_NONBLOCK );
        
        // Log
        char host[NI_MAXHOST];
        getnameinfo((struct sockaddr *)&cli_addr, sizeof(cli_addr), host, sizeof(host), NULL, 0, NI_NUMERICHOST);
        BOOST_LOG_TRIVIAL(debug) << "Connection has been made by " << host;


        // Write back
        write( m_client_fd,"\377\375\042\377\373\001",6);
        write( m_client_fd,"Welcome\n\0", 9);

        // Set the connected flag
        m_is_connected = true;
    
        // run until time to quit
        while( m_is_connected == true &&
               m_is_running   == true )
        {
            // Check the manager
            if( this->m_render_manager == nullptr ){
                break;
            }

        
            // Check keyboard value
            while( true ){
                
                // Read from socket
                n = read( m_client_fd, buffer, 255 );
                
                // Check if the socket has closed
                if( n == 0 ){
                    break;
                }

                // Check time to quit
                else if ( m_is_running   == false || 
                          m_is_connected == false )
                {
                    break;
                }

                // Check if valid data
                else if( n != EAGAIN && n > 0 ){
                    break;
                }
                else{

                    // If we have hit the max count, then refresh the screen anyhow
                    if( refresh_counter >= refresh_counter_max ){
                        refresh_counter = 0;
                        Refresh_Screen();
                    }
                    // Since not valid, sleep
                    usleep(read_sleep_time_usec);

                    // Increment the refresh counter
                    refresh_counter++;
                }

            }

            // Check the buffer
            input = std::string(buffer).substr(0,n);
        
            // Process the text
            if( input.size() > 1 ){
                
                // Check if the input has a special key
                key = this->Process_Special_Key( input );
                
                if( key != (int)CORE::CLI_Event_Type::UNKNOWN ){
                    
                    CORE::Event_Manager::Process_Event( key );
                }
                else{
                
                    // If no special key, just process it in chunks
                    for( size_t ch=0; ch<input.size(); ch++ ){
                    
                        // Since we are just parsing straight input,
                        // make sure we avoid negative numbers from the 
                        // telnet client (HACK).  For some reason, telnet sends
                        // a bunch of 250+ digits which causes the char to return
                        // negative numbers.  -3 tells me right now to shut down.
                        if( input[ch] > 0 ){    
                            CORE::Event_Manager::Process_Event( input[ch] );
                        }
                    }
                }

            } else {
            
                // Process the single key
                CORE::Event_Manager::Process_Event( input[0] );
            
            }

            // Process the command
            BOOST_LOG_TRIVIAL(trace) << "Calling Event_Manager::Process_Event with Key = " << key;
            BOOST_LOG_TRIVIAL(trace) << "Event_Manager::Process_Event returned.";
        
            // Refresh
            Refresh_Screen();

            // Check if time to exit
            if( m_is_running == false || 
                m_is_connected == false )
            {
                break;
            }

        }
    
        // Close the current session
        close( m_client_fd );
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
void A_Connection_Manager_Socket::Refresh_Screen()
{
    
    // Refresh the window manager
    this->m_render_manager->Refresh();
    
    // Get the buffer string
    std::vector<std::string>& buffer_data = std::dynamic_pointer_cast<RENDER::A_Render_Manager_ASCII>(m_render_manager)->Get_Console_Buffer();
    
    // Write each line to the socket
    for( size_t i=0; i<buffer_data.size(); i++ ){
        write( m_client_fd, buffer_data[i].c_str(), buffer_data[i].size() );   
    }
}

/********************************************/
/*      Configure the Special Key Map       */
/********************************************/
void A_Connection_Manager_Socket::Configure_Special_Key_List()
{
    // Add each keyboard to event mapping here
    m_special_key_list.push_back( std::make_tuple( TELNET_JUNK,          (int)CORE::CLI_Event_Type::CLI_NULL             ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_DELETE_KEY,  (int)CORE::CLI_Event_Type::KEYBOARD_DELETE_KEY  ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_LEFT_KEY,    (int)CORE::CLI_Event_Type::KEYBOARD_LEFT_ARROW  ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_RIGHT_KEY,   (int)CORE::CLI_Event_Type::KEYBOARD_RIGHT_ARROW ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_UP_KEY,      (int)CORE::CLI_Event_Type::KEYBOARD_UP_ARROW    ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_DOWN_KEY,    (int)CORE::CLI_Event_Type::KEYBOARD_DOWN_ARROW  ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F1_KEY,      (int)CORE::CLI_Event_Type::KEYBOARD_F1          ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F2_KEY,      (int)CORE::CLI_Event_Type::KEYBOARD_F2          ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F3_KEY,      (int)CORE::CLI_Event_Type::KEYBOARD_F3          ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F4_KEY,      (int)CORE::CLI_Event_Type::KEYBOARD_F4          ));
    m_special_key_list.push_back( std::make_tuple( KEYBOARD_F5_KEY,      (int)CORE::CLI_Event_Type::KEYBOARD_F5          ));

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
    return (int)CORE::CLI_Event_Type::UNKNOWN;
}


} // End of CLI Namespacee

