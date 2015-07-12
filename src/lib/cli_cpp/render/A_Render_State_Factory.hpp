/**
 * @file    A_Render_State_Factory.hpp
 * @author  Marvin Smith
 * @date    7/11/2015
*/
#ifndef __CLI_CPP_RENDER_A_RENDER_STATE_FACTORY_HPP__
#define __CLI_CPP_RENDER_A_RENDER_STATE_FACTORY_HPP__

// CLI Libraries
#include "../cmd/A_Command_Parser.hpp"
#include "A_Render_State.hpp"


// C++ Libraries
#include <string>
#include <vector>


namespace CLI{
namespace RENDER{

/**
 * @class A_Render_State_Factory
*/
class A_Render_State_Factory
{

    public:
        
        /**
         * @brief Create a new Render State Instance.
         *
         * @param
         *
         * @return New render state instance.
        */
        static A_Render_State::ptr_t Instance_Of( const int& instance_id );


        /**
         * @brief Initialize the Render State Factory.
         *
         * @param[in] command_parser Command-Parser to tie to each instance.
        */
        static void Initialize( CMD::A_Command_Parser::ptr_t command_parser );
        

        /**
         * @brief Check if initialized
        */
        static bool Is_Initialized();


    private:
        
        /**
         * @brief Constructor
         */
        A_Render_State_Factory();
        

        /**
         * @brief Get a factory instance.
        */
        static A_Render_State_Factory& Get_Factory_Instance();


        /// Class Name
        std::string m_class_name;


        /// List of instances
        std::vector<A_Render_State::ptr_t> m_instances;


        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;
        

        /// Initialized Flag
        bool m_is_initialized;

}; // End of A_Render_State_Factory Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
