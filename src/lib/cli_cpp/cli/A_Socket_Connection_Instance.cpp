/**
 * @file    A_Socket_Connection_Instance.cpp
 * @author  Marvin Smith
 * @date    7/9/2015
*/
#include "A_Socket_Connection_Instance.hpp"

// CLI Libraries
#include "../event/Event_Manager.hpp"
#include "../render/A_Render_Manager_ASCII.hpp"
#include "../render/A_Render_Manager_Factory.hpp"
#include "../utility/ANSI_Utilities.hpp"
#include "../utility/Log_Utilities.hpp"


namespace CLI{


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


/************************************/
/*           Constructor            */
/************************************/
A_Socket_Connection_Instance::A_Socket_Connection_Instance( const int& instance, 
                                                            const int& client_fd,
                                                            const int& read_sleep_timeout_usec)
  : m_class_name("A_Socket_Connection_Instance"),
    m_instance_id(instance),
    m_client_fd(client_fd),
    m_read_sleep_timeout_usec(read_sleep_timeout_usec),
    m_is_running(false)
{

    // Configure Special Key List
    Configure_Special_Key_List();

}


/************************************/
/*          Run Instance            */
/************************************/
void A_Socket_Connection_Instance::Run()
{
    // Get the render manager
    m_render_manager = RENDER::A_Render_Manager_Factory::Instance_Of( m_instance_id );

    // Make sure the instance is valid
    if( m_render_manager == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render-Manager instance returned was null.";
        m_is_running = false;
        return;
    }

    // Misc flags
    int n;
    std::string input;
    int key;
    char buffer[256];

    // Set the running flag
    m_is_running = true;

    // Write to the client
    write( m_client_fd,"\377\375\042\377\373\001",6);


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


        // While connected
        while( m_is_connected == true &&
               m_is_running   == true )
        {

            // Read from socket
            n = read( m_client_fd, buffer, 255 );

            // Check if the socket has closed
            if( n == 0 ){
                m_is_connected = false;
                break;
            }

            // Check time to quit
            else if ( m_is_running   == false || 
                      m_is_connected == false )
            {
                break;
            }

            // Otherwise, check if valid
            if( n > 0 ){
                break;
            }

            // Finally sleep
            usleep(m_read_sleep_timeout_usec);
        }

        // Check if we are still running
        if( m_is_connected == false || 
            m_is_running   == false )
        {
            break;
        }

        // Check the buffer
        input = std::string(buffer).substr(0,n);


        // Process the text
        if( input.size() > 1 ){

            // Check if the input has a special key
            key = this->Process_Special_Key( input );

            if( key != (int)CLI_Event_Type::UNKNOWN ){

                EVT::Event_Manager::Process_Event( m_instance_id,
                        key );
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
                        EVT::Event_Manager::Process_Event( m_instance_id,
                                input[ch] );
                    }
                }
            }

        } else {

            // Process the single key
            EVT::Event_Manager::Process_Event( m_instance_id,
                    input[0] );

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

    // Before we close the socket, write out the vis string to
    // remove the effects of hiding the cursor
    std::string close_socket_str = UTILS::ANSI_CLEARSCREEN +  UTILS::ANSI_CURSORVIS;
    write( m_client_fd, 
           close_socket_str.c_str(), 
           close_socket_str.size() );


    // Close the current session
    close( m_client_fd );

    // exit
    m_is_running = false;

}


/*********************************/
/*       Refresh the screen      */
/*********************************/
void A_Socket_Connection_Instance::Refresh_Screen()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;


    // Get the buffer string
    std::vector<std::string> buffer_data = std::dynamic_pointer_cast<RENDER::A_Render_Manager_ASCII>(m_render_manager)->Get_Console_Buffer();


    // Write each line to the socket
    for( size_t i=0; i<buffer_data.size(); i++ ){
        write( m_client_fd, buffer_data[i].c_str(), buffer_data[i].size() );   
    }

    // Unlock the mutex
    m_refresh_lock.unlock();


    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/*******************************/
/*            Start            */
/*******************************/
void A_Socket_Connection_Instance::Start()
{
    m_thread = std::thread( &A_Socket_Connection_Instance::Run,
                            this );
}

/*********************************/
/*          Join Thread          */
/*********************************/
void A_Socket_Connection_Instance::Join()
{
    // Set flag
    m_is_running = false;

    // Wait to finish
    if( m_thread.joinable() ){
        m_thread.join();
    }
}


/**************************************/
/*        Process Special Keys        */
/**************************************/
int A_Socket_Connection_Instance::Process_Special_Key( const std::string& input_str )const
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

/********************************************/
/*      Configure the Special Key Map       */
/********************************************/
void A_Socket_Connection_Instance::Configure_Special_Key_List()
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


} // End of CLI Namespace

