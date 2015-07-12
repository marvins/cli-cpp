/**
 * @file    A_Socket_Connection_Instance.cpp
 * @author  Marvin Smith
 * @date    7/9/2015
*/
#include "A_Socket_Connection_Instance.hpp"


namespace CLI{


/************************************/
/*           Constructor            */
/************************************/
A_Socket_Connection_Instance::A_Socket_Connection_Instance( const int& instance, 
                                                            const int& client_fd )
  : m_class_name("A_Socket_Connection_Instance"),
    m_instance_id(instance),
    m_client_fd(client_fd),
    m_is_running(false)
{


}


/************************************/
/*          Run Instance            */
/************************************/
void A_Socket_Connection_Instance::Run()
{
    // Get the render manager
    m_render_manager = RENDER::A_Render_Manager_Factory::Instance_Of( m_instance_id );

    // Make sure the instance is valid
    if( render_manager == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render-Manager instance returned was null.";
        m_is_running = false;
        return;
    }

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
            while( m_is_connected[instance_id] == true &&
                   m_is_running   == true )
            {
            
                // Read from socket
                n = read( m_client_fd[instance_id], buffer, 255 );
               
                // Check if the socket has closed
                if( n == 0 ){
                    m_is_connected[instance_id] = false;
                    break;
                }

                // Check time to quit
                else if ( m_is_running   == false || 
                          m_is_connected[instance_id] == false )
                {
                    break;
                }

                // Otherwise, check if valid
                if( n > 0 ){
                    break;
                }

                // Finally sleep
                usleep(m_configuration->Get_Read_Timeout_Sleep_Microseconds());
            }

            // Check if we are still running
            if( m_is_connected[instance_id] == false || 
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
                m_is_connected[instance_id] == false )
            {
                break;
            }

        }

        // Before we close the socket, write out the vis string to
        // remove the effects of hiding the cursor
        std::string close_socket_str = UTILS::ANSI_CLEARSCREEN +  UTILS::ANSI_CURSORVIS;
        write( m_client_fd[instance_id], close_socket_str.c_str(), close_socket_str.size() );
    
        
        // Close the current session
        close( m_client_fd[instance_id] );
    }






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
    std::vector<std::string> buffer_data = std::dynamic_pointer_cast<RENDER::A_Render_Manager_ASCII>(m_render_manager)->Get_Console_Buffer( instance_id );
    
    
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


} // End of CLI Namespace

