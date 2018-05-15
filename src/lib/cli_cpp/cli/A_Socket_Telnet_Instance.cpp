/**
 * @file    A_Socket_Connection_Instance.cpp
 * @author  Marvin Smith
 * @date    7/9/2015
*/
#include "A_Socket_Telnet_Instance.hpp"

// CLI Libraries
#include "../event/Event_Manager.hpp"
#include "../render/A_Render_Manager_ASCII.hpp"
#include "../render/A_Render_Manager_Factory.hpp"
#include "../utility/ANSI_Utilities.hpp"
#include "../utility/Log_Utilities.hpp"
#include "../utility/String_Utilities.hpp"


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
const std::string KEYBOARD_F5_KEY     = "\033\133\061\065\176";


/************************************/
/*           Constructor            */
/************************************/
A_Socket_Telnet_Instance::A_Socket_Telnet_Instance( A_Socket_Instance_Config_Base::ptr_t  config,
                                                    int                                   instance_id,
                                                    const CORE::Session&                  session,
                                                    int                                   client_fd )
  : A_Socket_Base_Instance( config,
                            instance_id,
                            session,
                            client_fd ),
    m_class_name("A_Socket_Telnet_Instance"),
    m_skip_render(false),
    m_first_command_received(false)
{
    // Cast the config
    m_config = std::dynamic_pointer_cast<A_Socket_Instance_Config_Telnet>(config);
    
    // Configure Special Key List
    Configure_Special_Key_List();

}


/********************************/
/*         Destructor           */
/********************************/
A_Socket_Telnet_Instance::~A_Socket_Telnet_Instance()
{
    // Join
    Join();
}

/************************************/
/*          Run Instance            */
/************************************/
void A_Socket_Telnet_Instance::Run()
{
    // Get the render manager
    m_render_manager = RENDER::A_Render_Manager_Factory::Instance_Of( m_instance_id,
                                                                      m_config->Get_Session_Type() );

    // Make sure the instance is valid
    if( m_render_manager == nullptr )
    {
        LOG_ERROR("Render-Manager instance returned was null.");
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
    // IAC DO linemode IAC WILL eacho
    int res = write( m_client_fd,"\377\375\042\377\373\001",6);
    if( res < 0 ){
        m_is_running = false;
        return;
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
            std::this_thread::sleep_for( m_config->Get_Read_Sleep_Timeout() );
        }

        // Check if we are still running
        if( m_is_connected == false || 
            m_is_running   == false )
        {
            break;
        }

        // Check the buffer
        input = std::string(buffer).substr(0,n);
        
        // Check if CLI Command Input
        if( m_first_command_received == false    &&
            UTILS::String_Trim(input).size() > 3 &&
            UTILS::String_Trim(input.substr(0,3)) == "cli" )
        {
            // Split the string
            std::vector<std::string> comps = UTILS::String_Split( input );
            
            if( comps.size() <= 1 ){
                BOOST_LOG_TRIVIAL(warning) << "Input is invalid (" << input << ")";
            }
            else{

                // Get all but the first arg
                input = comps[1];
                for( size_t i=2; i<comps.size(); i++ ){ 
                    input += " " + comps[i];
                }
                BOOST_LOG_TRIVIAL(debug) << "Received command over socket directly (" << input << ")";
                
                // Process the input
                for( size_t i=0; i<input.size(); i++ ){
                    std::cout << "Processing Key (" << input[i] << ")" << std::endl;
                    EVT::Event_Manager::Process_Event( m_instance_id,
                                                       input[i] );
                }

                // Add the Enter Key
                std::cout << "Processing Enter Key" << std::endl;
                EVT::Event_Manager::Process_Event( m_instance_id,
                                                   (int)CLI_Event_Type::KEYBOARD_ENTER );

                EVT::Event_Manager::Process_Event( m_instance_id,
                                                   (int)CLI_Event_Type::CLI_SHUTDOWN );

            }
        }
        // Process the text
        else if( input.size() > 1 ){

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
        if( m_skip_render == true ){
            Refresh_Screen();
        }


        // Check if time to exit
        if( m_is_running == false || 
                m_is_connected == false )
        {
            break;
        }

        // Set the first command as received
        m_first_command_received = true;

    }

    // Before we close the socket, write out the vis string to
    // remove the effects of hiding the cursor
    if( m_skip_render != true )
    {
        std::string close_socket_str = UTILS::ANSI_CLEARSCREEN +  UTILS::ANSI_CURSORVIS;
        res = write( m_client_fd, 
                     close_socket_str.c_str(), 
                     close_socket_str.size() );

        if( res < 0 ){
            BOOST_LOG_TRIVIAL(error) << "Unable to write. File: " << __FILE__ << ", Line: " << __LINE__;
        }
    }

    // Close the current session
    close( m_client_fd );

    // exit
    m_is_running = false;

}


/*********************************/
/*       Refresh the screen      */
/*********************************/
void A_Socket_Telnet_Instance::Refresh_Screen()
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;

    // Check if we are skipping the refresh
    if( m_skip_render == true ){
        BOOST_LOG_TRIVIAL(debug) << "Skipping Rendering in Connection-Manager.";
        return;
    }

    // Lock the mutex
    m_refresh_lock.lock();

    // Get the buffer string
    std::vector<std::string> buffer_data = std::dynamic_pointer_cast<RENDER::A_Render_Manager_ASCII>(m_render_manager)->Get_Console_Buffer();

    // Write each line to the socket
    for( size_t i=0; i<buffer_data.size(); i++ ){
        int res = write( m_client_fd, buffer_data[i].c_str(), buffer_data[i].size() );   
        if( res < 0 ){
            BOOST_LOG_TRIVIAL(error) << "Unable to write to socket.";
        }
    }

    // Unlock the mutex
    m_refresh_lock.unlock();


    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/**************************************/
/*        Process Special Keys        */
/**************************************/
int A_Socket_Telnet_Instance::Process_Special_Key( const std::string& input_str )const
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
    BOOST_LOG_TRIVIAL(debug) << sin.str();

    // otherwise, return failure
    return (int)CLI_Event_Type::UNKNOWN;
}

/********************************************/
/*      Configure the Special Key Map       */
/********************************************/
void A_Socket_Telnet_Instance::Configure_Special_Key_List()
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

