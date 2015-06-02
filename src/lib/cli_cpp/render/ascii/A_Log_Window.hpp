/** 
 * @file    A_Log_Window.hpp
 * @author  Marvin Smith
 * @date    5/30/2015
*/
#ifndef __CLI_CPP_LIB_RENDER_ASCII_A_LOG_WINDOW_HPP__
#define __CLI_CPP_LIB_RENDER_ASCII_A_LOG_WINDOW_HPP__

// CLI Libraries
#include "An_ASCII_Render_Window_Base.hpp"

// C++ Standard Libraries
#include <memory>
#include <string>
#include <vector>

namespace CLI{
namespace RENDER{

 
/**
 * @class A_Log_Window
*/
class A_Log_Window : public An_ASCII_Render_Window_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Log_Window> ptr_t;


        /**
         * @brief Constructor
        */
        A_Log_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver );
    
    private:
        
        /// Class Name
        std::string m_class_name;

}; // End of A_Log_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
