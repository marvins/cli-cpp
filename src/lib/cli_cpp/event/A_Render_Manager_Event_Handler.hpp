/**
 * @file    A_Render_Manager_Event_Handler.hpp  
 * @author  Marvin Smith
 * @date    5/31/2015
*/
#ifndef __CLI_CPP_LIB_CORE_A_RENDER_MANAGER_EVENT_HANDLER_HPP__
#define __CLI_CPP_LIB_CORE_A_RENDER_MANAGER_EVENT_HANDLER_HPP__

// CLI Libraries
#include "A_CLI_Event_Handler_Base.hpp"
#include "../render/A_Render_Manager_Base.hpp"

namespace CLI{
namespace EVT{

/**
 * @class A_Render_Manager_Event_Handler Class
*/
class A_Render_Manager_Event_Handler : public A_CLI_Event_Handler_Base
{
    public:
        
        /**
         * @brief Constructor
        */
        A_Render_Manager_Event_Handler();
        
        
        /**
         * @brief Check if Event is Valid.
         *
         * @param[in] event Event value to evaluate.
         *
         * @return True if valid, false otherwise,
        */
        virtual bool Is_Supported_Event( const int& event )const;


        /**
         * @brief Process Event.
         *
         * @param[in] instance_id ID of the client issuing the event.
         * @param[in] event Event value.
         */
        virtual void Process_Event( const int& instance_id,
                                    const int& event );


    private:
        
        /// Class Name
        std::string m_class_name;

}; // End of A_Render_Manager_Event_Handler Class


} // End of EVT Namespace
} // End of CLI Namespace

#endif
