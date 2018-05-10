/**
 * @file    A_Connection_Manager_Factory.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Connection_Manager_Factory.hpp"

// CLI Libraries
#include "A_Connection_Manager_Socket.hpp"
#include "A_Connection_Manager_Socket_JSON.hpp"

namespace CLI{


/********************************************/
/*      Initialize Connection Manager       */
/********************************************/
A_Connection_Manager_Base::ptr_t A_Connection_Manager_Factory::Initialize( A_Connection_Manager_Base_Config::ptr_t configuration )
{
    // Check the type
    if( configuration == nullptr ){
        return nullptr;
    }

    // Check if socket
    if( configuration->Get_ConnectionType() == CORE::ConnectionType::SOCKET ){
        
        // Cast the configuration
        A_Connection_Manager_Socket_Config::ptr_t socket_config = std::dynamic_pointer_cast<A_Connection_Manager_Socket_Config>( configuration );

        // Return socket
        return std::make_shared<A_Connection_Manager_Socket>( socket_config  );
    } else if( configuration->Get_ConnectionType() == CORE::ConnectionType::SOCKET_JSON ){
        
        A_Connection_Manager_Socket_JSON_Config::ptr_t socket_config == std::dynamic_pointer_cast<A_Connection_Manager_Socket_JSON_Config>(configuration);
        
        return std::make_shared<A_Connection_Manager_Socket_JSON>(socket_config);
    }
    
    // return manager
    return nullptr;
}

} // End of CLI Namespace

