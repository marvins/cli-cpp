/**
 * @file    A_Connection_Manager_Event_Handler.hpp  
 * @author  Marvin Smith
 * @date    5/31/2015
*/
#ifndef __CLI_CPP_LIB_CORE_A_CONNECTION_MANAGER_EVENT_HANDLER_HPP__
#define __CLI_CPP_LIB_CORE_A_CONNECTION_MANAGER_EVENT_HANDLER_HPP__

// CLI Libraries
#include "A_CLI_Event_Handler_Base.hpp"
#include "CLI_Event_Type.hpp"
#include "../cli/A_Connection_Manager_Base.hpp"

namespace CLI{
namespace CORE{

/**
 * @class A_Connection_Manager_Event_Handler Class
*/
class A_Connection_Manager_Event_Handler : public A_CLI_Event_Handler_Base
{
    public:
        
        /**
         * @brief Constructor
         *
         * @param[in] connection_manager Connection manager to send responses to.
        */
        A_Connection_Manager_Event_Handler( A_Connection_Manager_Base::ptr_t connection_manager );
        

        /**
         * @brief Process Event.
         *
         * @param[in] event Event to process.  Cast the CLI_Event_Type for input to make things easier.
         */
        virtual void Process_Event( const int& event );


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Event Manager Pointer
        A_Connection_Manager_Base::ptr_t m_connection_manager;

}; // End of A_Connection_Manager_Event_Handler Class


} // End of CORE Namespace
} // End of CLI  Namespace

#endif
