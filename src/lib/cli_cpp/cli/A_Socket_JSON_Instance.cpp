/**
 * @file    A_Socket_JSON_Instance.cpp
 * @author  Marvin Smith
 * @date    5/15/2018
*/
#include "A_Socket_JSON_Instance.hpp"

// CLI Libraries
#include "../event/Event_Manager.hpp"
#include "../utility/Log_Utilities.hpp"
#include "../utility/String_Utilities.hpp"


namespace CLI{


/*********************************/
/*          Constructor          */
/*********************************/
A_Socket_Instance_Config_JSON::A_Socket_Instance_Config_JSON( std::chrono::microseconds  read_sleep_timeout )
    : A_Socket_Instance_Config_Base(read_sleep_timeout),
      m_class_name("A_Socket_Instance_Config_JSON")
{
}


/*****************************************/
/*          Print to Log String          */
/*****************************************/
std::string A_Socket_Instance_Config_JSON::To_Log_String( int offset )const
{
    std::string gap(offset, ' ');
    
    std::stringstream sin;
    sin << gap << " - " << m_class_name << "\n";
    sin << gap << "    - Read-Sleep-Timeout: " << Get_Read_Sleep_Timeout().count() << " ms\n";
    return sin.str();
}


/************************************/
/*           Constructor            */
/************************************/
A_Socket_JSON_Instance::A_Socket_JSON_Instance( A_Socket_Instance_Config_Base::ptr_t  config,
                                                int                                   instance_id,
                                                const CORE::Session&                  session,
                                                int                                   client_fd )
    : A_Socket_Base_Instance( config,
                              instance_id,
                              session,
                              client_fd ),
      m_class_name("A_Socket_JSON_Instance"),
      m_first_command_received(false)
{
    // Cast the config
    m_config = std::dynamic_pointer_cast<A_Socket_Instance_Config_JSON>(config);
}


/********************************/
/*         Destructor           */
/********************************/
A_Socket_JSON_Instance::~A_Socket_JSON_Instance()
{
    // Join
    Join();
}

/************************************/
/*          Run Instance            */
/************************************/
void A_Socket_JSON_Instance::Run()
{
    // Misc flags
    int n;
    std::string input;
    char buffer[256];
    
    // Set the running flag
    m_is_running = true;
    
    // Set the connected flag
    m_is_connected = true;
    
    // run until time to quit
    while( m_is_connected == true &&
           m_is_running   == true )
    {
        
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
        
        LOG_TRACE("INPUT: " + input);
        /*
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
        */
        
        // Process the command
        //LOG_TRACE("BOOST_LOG_TRIVIAL(trace) << "Calling Event_Manager::Process_Event with Key = " << key;
        //BOOST_LOG_TRIVIAL(trace) << "Event_Manager::Process_Event returned.";
        
        // Check if time to exit
        if( m_is_running == false ||
            m_is_connected == false )
        {
            break;
        }
        
        // Set the first command as received
        m_first_command_received = true;
        
    }
    
    // Close the current session
    close( m_client_fd );
    
    // exit
    m_is_running = false;
    
}


/*********************************/
/*       Refresh the screen      */
/*********************************/
void A_Socket_JSON_Instance::Refresh_Screen()
{
    CLI_LOG_CLASS_ENTRY();
}


} // End of CLI Namespace

