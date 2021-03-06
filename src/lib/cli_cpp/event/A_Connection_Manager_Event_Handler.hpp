/**
 * @file    A_Connection_Manager_Event_Handler.hpp  
 * @author  Marvin Smith
 * @date    5/31/2015
*/
#ifndef CLI_CPP_LIB_CORE_A_CONNECTION_MANAGER_EVENT_HANDLER_HPP
#define CLI_CPP_LIB_CORE_A_CONNECTION_MANAGER_EVENT_HANDLER_HPP

// CLI Libraries
#include "../cli/A_Connection_Manager_Base.hpp"
#include "../core/CLI_Event_Type.hpp"
#include "A_CLI_Event_Handler_Base.hpp"

namespace CLI{
namespace EVT{

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
        virtual void Process_Event( const int& instance,
                                    const int& event );


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Event Manager Pointer
        A_Connection_Manager_Base::ptr_t m_connection_manager;

}; // End of A_Connection_Manager_Event_Handler Class


} // End of EVT Namespace
} // End of CLI Namespace

#endif
