/**
 * @file    Network_Scanner.cpp
 * @author  Marvin Smith
 * @date    7/5/2015
*/
#include "Network_Scanner.hpp"

// C++ Standard Libraries
#include <unistd.h>

// Demo Libraries
#include "System_Utilities.hpp"


/***************************/
/*      Network Asset      */
/***************************/
Network_Asset::Network_Asset( const std::string&  asset_name,
                              const std::string&  address,
                              const int&          max_ping_attempts )
 : m_class_name("Network_Asset"),
   m_name(asset_name),
   m_address(address),
   m_ping_max_attempts(max_ping_attempts),
   m_status(-1)
{
}


/*******************************************/
/*      Get the Last Scan Time String      */
/*******************************************/
std::string Network_Asset::Get_Last_Scan_Time_String()const
{
    return "Not scanned";
}


/*******************************************/
/*          Get the Status String          */
/*******************************************/
std::string Network_Asset::Get_Status_String()const
{
    // If never scanned, 
    if( m_status == -1 ){
        return "Never scanned";
    }

    // If responsive
    if( m_status == 1 ){
        return "Responsive";
    }

    // If in progress
    if( m_status == 2 ){
        return "In-Progress";
    }

    // If non-responsive
    return "Non-Responsive";
}


/****************************/
/*      Perform A Scan      */
/****************************/
void Network_Asset::Scan_Asset()
{
    // Set to in progress
    m_status = 2;

    // Set the timestamp
    m_last_scan_time = std::chrono::system_clock::now();

    // Do Ping
    std::string details;
    bool result = Ping( m_address, 
                        m_ping_max_attempts, 
                        details );

    if( result == true ){
        m_status = 1;
    }
    else{
        m_status = 0;
    }

}

/***********************/
/*      Constructor    */
/***********************/
Network_Scanner::Network_Scanner()
  : m_class_name("Network_Scanner"),
    m_is_running(false)
{


}


/***********************************/
/*       Add a Network Asset       */
/***********************************/
void Network_Scanner::Add_Network_Asset( const std::string& name,
                                         const std::string& address,
                                         const int&         max_ping_attempts )
{
    // Add to the list
    m_network_assets.push_back( Network_Asset( name,
                                               address,
                                               max_ping_attempts ));

}


/*******************************/
/*      Start the Scanner      */
/*******************************/
void Network_Scanner::Start_Scanner()
{
    // Set the run flag
    m_is_running = true;

    // Start the thread
    m_scan_thread = std::thread( &Network_Scanner::Scan_Runner,
                                 this );


}


/*******************************/
/*      Stop the Scanner       */
/*******************************/
void Network_Scanner::Stop_Scanner()
{

    // Set the flag
    m_is_running = false;

    // Join
    if( m_scan_thread.joinable() ){
        m_scan_thread.join();
    }

}


/************************************/
/*      Scanning Thread Runner      */
/************************************/
void Network_Scanner::Scan_Runner()
{

    // Scan while the flag is valid
    while( m_is_running == true )
    {

        //  Iterate over assets
        for( size_t i=0; i<m_network_assets.size(); i++ ){
            m_network_assets[i].Scan_Asset();
        }
        
        // Sleep
        sleep(2);
    }
}


