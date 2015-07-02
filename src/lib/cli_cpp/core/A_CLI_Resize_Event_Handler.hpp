/**
 * @file    A_CLI_Resize_Event_Handler.hpp
 * @author  Marvin Smith
 * @date    6/2/2015
*/
#ifndef __CLI_CPP_LIB_CORE_A_CLI_RESIZE_EVENT_HANDLER_HPP__
#define __CLI_CPP_LIB_CORE_A_CLI_RESIZE_EVENT_HANDLER_HPP__

// CLI Libraries
#include "A_CLI_Event_Handler_Base.hpp"
#include "CLI_Event_Type.hpp"
#include "../render/A_Render_State.hpp"

namespace CLI{
namespace CORE{

/**
 * @class A_CLI_Resize_Event_Handler Class
*/
class A_CLI_Resize_Event_Handler : public A_CLI_Event_Handler_Base
{
    public:
        
        /**
         * @brief Constructor
         *
         * @param[in] render_state Render state manager which contains the CLI Size.
        */
        A_CLI_Resize_Event_Handler( RENDER::A_Render_State::ptr_t render_state );
      
      
        /**
         * @brief Check if Event is Valid.
         *
         * @param[in] event Event value to evaluate.
         *
         * @return True if event == CLI_Event_Type::CLI_RESIZE.
        */
        inline virtual bool Is_Supported_Event( const int& event )const{
            return (event == (int)CLI_Event_Type::CLI_RESIZE);
        }
  

        /**
         * @brief Process Event.
         *
         * @param[in] event Event to process.  Cast the CLI_Event_Type for input to make things easier.
         */
        virtual void Process_Event( const int& event );


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Render State Pointer
        RENDER::A_Render_State::ptr_t m_render_state;

}; // End of A_CLI_Resize_Event_Handler


} // End of CORE Namespace
} // End of CLI  Namespace

#endif
