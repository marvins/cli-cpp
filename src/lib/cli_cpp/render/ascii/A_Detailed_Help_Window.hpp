/**
 * @file    A_Detailed_Help_Window.hpp
 * @author  Marvin Smith
 * @date    7/3/2015
*/
#ifndef __CLI_CPP_RENDER_ASCII_A_DETAILED_HELP_WINDOW_HPP__
#define __CLI_CPP_RENDER_ASCII_A_DETAILED_HELP_WINDOW_HPP__

// CLI Libraries
#include "An_ASCII_Render_Window_Base.hpp"
#include "../A_Render_Driver_Context_ASCII.hpp"


// C++ Libraries
#include <memory>
#include <string>


namespace CLI{
namespace RENDER{

/**
 * @class A_Detailed_Help_Window
*/
class A_Detailed_Help_Window : public An_ASCII_Render_Window_Base
{
    public:

        /// Pointer Type
        typedef std::shared_ptr<A_Detailed_Help_Window> ptr_t;

        
        /**
         * @brief Constructor
         *
         * @param[in] render_driver Driver containing rendering parameters.
         */
        A_Detailed_Help_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver );
        

        /**
         * @brief Update the buffer data.
         */
        virtual void Update_Buffer_Data();


        /**
         * @brief Check if there is a matching name.
         *
         * @return True if so, false otherwise.
        */
        virtual bool Is_Matching_Name( const std::string& test_name )const;
    
    protected:
        
        /// List of matching names
        std::vector<std::string> m_valid_command_names;

    private:


        /**
         * @brief Update Buffer Lines
        */
        void Update_Buffer_Lines();


        /// Class Name
        std::string m_class_name;




}; // End of A_Detailed_Help_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
