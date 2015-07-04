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
         * @brief Constructor
        */
        An_ASCII_Render_Window_Base( A_Render_Driver_Context_ASCII::ptr_t render_driver );


        /**
         * @brief Retrieve the buffer data
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
         * @brief Get the Window Title
        */
        inline virtual std::string  Get_Window_Title()const{
            return m_class_name;
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
