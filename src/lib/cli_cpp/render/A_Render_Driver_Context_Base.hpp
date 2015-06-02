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

// CLI Libraries
#include "../cmd/A_Command_Result.hpp"


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
        A_Render_Driver_Context_Base( const std::string& cli_title );
        

        /**
         * @brief Destructor
        */
        virtual ~A_Render_Driver_Context_Base();

        
        /**
         * @brief Get the CLI Title
        */
        inline std::string Get_CLI_Title()const{
            return m_cli_title;
        }
        
        
        /**
         * @brief Command the system to wait on the input command response.
         */
        void Set_Waiting_Command_Response( const CMD::A_Command_Result::ptr_t response );


        /**
         * @brief Get the waiting status
         *
         * @return True if waiting on command result response.
         */
        bool Check_Waiting_Command_Response();

    protected:
        
        /// CLI Title
        std::string m_cli_title;

    private:

        /// Class Name
        std::string m_class_name;
        
        /// Waiting Response
        bool m_waiting_command_response;
        
        /// Waiting command
        CMD::A_Command_Result::ptr_t m_waiting_command_response_value;

}; // End of A_Render_Driver_Context_Base Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
