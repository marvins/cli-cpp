/**
 * @file    A_Session_Event_Handler_Base.hpp
 * @author  Marvin Smith
 * @date    10/30/2016
 */
#ifndef __CLI_CPP_HANDLERS_A_SESSION_EVENT_HANDLER_BASE_HPP__
#define __CLI_CPP_HANDLERS_A_SESSION_EVENT_HANDLER_BASE_HPP__

// C++ Libraries
#include <memory>
#include <string>

// CLI Libraries
#include "../core/A_Session.hpp"


namespace CLI{


/**
 * @class A_Session_Event_Handler_Base
 */
class A_Session_Event_Handler_Base 
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Session_Event_Handler_Base> ptr_t;

        /**
         * @brief Constructor
         */
        A_Session_Event_Handler_Base();


        /**
         * @brief Destructor
         */
        virtual ~A_Session_Event_Handler_Base();

        
        /**
         * @brief Process the Session Info
         */
        virtual void Process_Event( const CORE::Session_Event& session ) = 0;

    private:
        
        /// Class Name
        std::string m_class_name;

}; // End of A_Session_Event_Handler_Base Class


} // End of CLI     Namespace


#endif
