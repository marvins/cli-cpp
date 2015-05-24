/**
 * @file    A_Render_Driver_Context_Base.hpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#ifndef __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_NCURSES_HPP__
#define __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_NCURSES_HPP__

// CLI Libraries
#include "A_Render_Driver_Context_Base.hpp"

// C++ Standard Libraries
#include <memory>
#include <string>


namespace CLI{
namespace RENDER{

/**
 * @class A_Render_Driver_Context_NCurses
 *
 * @brief NCurses render driver context.
*/
class A_Render_Driver_Context_NCurses : public A_Render_Driver_Context_Base 
{

    public:

        /// Pointer Type
        typedef std::shared_ptr<A_Render_Driver_Context_NCurses> ptr_t;

        
        /**
         * @brief Constructor
        */
        A_Render_Driver_Context_NCurses();


    private:
        
        /// Class Name 
        std::string m_class_name;


}; // End of A_Render_Driver_Context_NCurses

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif

