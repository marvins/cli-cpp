/**
 * @file    An_ASCII_Render_Window.hpp
 * @author  Marvin Smith
 * @date    5/30/2015
*/
#ifndef __CLI_CPP_LIB_RENDER_AN_ASCII_RENDER_WINDOW_HPP__
#define __CLI_CPP_LIB_RENDER_AN_ASCII_RENDER_WINDOW_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>
#include <vector>

// CLI Libraries
#include "../A_Render_Driver_Context_ASCII.hpp"

namespace CLI{
namespace RENDER{

/**
 * @brief An_ASCII_Render_Window_Base
*/
class An_ASCII_Render_Window_Base
{
    public:
    
        /// Pointer Type
        typedef std::shared_ptr<An_ASCII_Render_Window_Base> ptr_t;
        

        /**
         * @brief Default Constructor
         *
         * This method should only be used for custom windows.  Until the render driver
         * has been attached, this will fail.
         */
        An_ASCII_Render_Window_Base( );


        /**
         * @brief Constructor
         *
         * @param[in] render_driver Rendering driver used to set window size and other parameters.
        */
        An_ASCII_Render_Window_Base( A_Render_Driver_Context_ASCII::ptr_t render_driver );


        /**
         * @brief Retrieve the buffer data
         *
         * @return Buffer data list.
        */
        inline virtual std::vector<std::string>& Get_Buffer_Data(){
            return m_buffer_data;
        }

        
        /**
         * @brief Update the current buffer data.
         *
         * @brief Note that this will do nothing unless implemented.
         */
        virtual void Update_Buffer_Data();
        

        /**
         * @brief Set the driver context.
         *
         * @param[in] driver_context Driver context.
        */
        virtual void Set_Render_Driver_Context( A_Render_Driver_Context_ASCII::ptr_t render_driver );

        
        /**
         * @brief Get the Window Title
         *
         * @return Window Title String
        */
        inline virtual std::string  Get_Window_Title()const{
            return m_class_name;
        }


        /**
         * @brief Check if Event is Mapped to this method. 
         *
         * @param[in] event_id ID of the event.
         * 
         * @return False unless implemented by child class.
         */
        inline virtual bool Event_Registered( const int32_t& event_id ){
            return false;
        }
        

        /**
         * @brief Check if a Command is supported for enabling window.
         */
        inline virtual bool Is_Trigger_Command( const CMD::A_Command& command )const
        {
            return false;
        }
    
    protected:

        /// Buffer Data
        std::vector<std::string> m_buffer_data;

        /// Render Driver
        A_Render_Driver_Context_ASCII::ptr_t m_render_driver;

    private:
        
        /// Class Name
        std::string m_class_name;


}; // End of An_ASCII_Render_Window_Base Class

} // End of RENDER Namespace
} // End of CLI     Namespace

#endif
