/**
 * @file    A_Render_Driver_Context_Base.hpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#ifndef __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_BASE_HPP__
#define __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_BASE_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>

namespace CLI{
namespace RENDER{

/**
 * @class A_Render_Driver_Context_Base
*/
class A_Render_Driver_Context_Base{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Render_Driver_Context_Base> ptr_t;

        /**
         * @brief Constructor
        */
        A_Render_Driver_Context_Base();
        

        /**
         * @brief Destructor
        */
        virtual ~A_Render_Driver_Context_Base();


    private:

        /// Class Name
        std::string m_class_name;

}; // End of A_Render_Driver_Context_Base Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
