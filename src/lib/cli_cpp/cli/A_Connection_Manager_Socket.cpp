/**
 * @file    A_Connection_Manager_Socket.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Connection_Manager_Socket.hpp"

// CLI Libraries
#include "A_Connection_Manager_Socket_Config.hpp"
#include "../render/A_Render_Manager_ASCII.hpp"
#include "../thirdparty/ncurses/NCurses_Utilities.hpp"


// C++ Standard Libraries
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <sstream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>


// Keyboard Delete Key Value
const std::string KEYBOARD_DELETE_KEY = "\033\133\063\176";
const std::string KEYBOARD_LEFT_KEY   = "\033\133\104";
const std::string KEYBOARD_RIGHT_KEY  = "\033\133\103";
const std::string KEYBOARD_UP_KEY     = "\033\133\101";
const std::string KEYBOARD_DOWN_KEY   = "\033\133\102";

namespace CLI{


/*************************/
/*      Constructor      */
/*************************/
A_Connection_Manager_Socket::A_Connection_Manager_Socket( A_Connection_Manager_Base_Config::ptr_t configuration )
  : A_Connection_Manager_Base(),
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

    // Misc Variables
    int key;

    // Read the socket
    char buffer[256];
    int n;
    std::string input;
    
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

        // Write back
        write( m_client_fd,"\377\375\042\377\373\001",6);
        write( m_client_fd,"Welcome\n\0", 9);

        // Setup Render Manager
        if( this->m_render_manager != nullptr ){
            this->m_render_manager->Initialize();
            this->m_render_state = this->m_render_manager->Get_Render_State();
        }
        

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
                    usleep(1000);
                }

            }

            // Check the buffer
            input = std::string(buffer).substr(0,n);
        
            // Process the text
            if( input.size() > 1 ){
                this->m_render_state->Process_Input( this->Process_Special_Key( input ));    
            }
            else{
            
                // cast the key
                key = input[0];

                // Check if enter
                if( key == 27 || key == 13 || key == 10 ){
                    this->Process_Command();
                }
            
                // Otherwise, add the key
                else{
                    this->m_render_state->Process_Input( key );
                }
            }

        
            // Render the screen
            this->m_render_manager->Refresh();

            // Get the buffer string
            std::vector<std::string>& buffer_data = std::dynamic_pointer_cast<RENDER::A_Render_Manager_ASCII>(m_render_manager)->Get_Console_Buffer();
       
            // Write each line to the socket
            for( size_t i=0; i<buffer_data.size(); i++ ){
                write( m_client_fd, buffer_data[i].c_str(), buffer_data[i].size() );
            }

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

}


/**************************************/
/*        Process Special Keys        */
/**************************************/
int A_Connection_Manager_Socket::Process_Special_Key( const std::string& input_str )const
{
    // Check Delete Key
    if( input_str == KEYBOARD_DELETE_KEY ){
        return KEY_DC;
    }

    // Check Left Key
    else if( input_str == KEYBOARD_LEFT_KEY ){
        return KEY_LEFT;
    }

    // Check Right Key
    else if( input_str == KEYBOARD_RIGHT_KEY ){
        return KEY_RIGHT;    
    }

    // Check Up Key
    else if( input_str == KEYBOARD_UP_KEY ){
        return KEY_UP;
    }

    // Check Down Key
    else if( input_str == KEYBOARD_DOWN_KEY ){
        return KEY_DOWN;
    }

    // Otherwise, there was an error
    else{
        std::cerr << "Warning, data is larger than expected. Size: " << input_str.size() << std::endl;
        for( size_t i=0; i<input_str.size(); i++ ){
            std::cout << i << " : " << (int)input_str[i] << std::endl;
        }
    }


    // otherwise, return failure
    return -1;
}


} // End of CLI Namespacee

