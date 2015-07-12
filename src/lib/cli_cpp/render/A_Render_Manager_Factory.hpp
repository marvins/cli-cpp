/**
 * @file    A_Render_Manager_Factory.hpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#ifndef __CLI_CPP__RENDER_A_RENDER_MANAGER_FACTORY_HPP__
#define __CLI_CPP__RENDER_A_RENDER_MANAGER_FACTORY_HPP__

// CLI Libraries
#include "../core/ConnectionType.hpp"
#include "A_Render_Driver_Context_Base.hpp"
#include "A_Render_Manager_Base.hpp"

// C++ Standard Libraries
#include <string>
#include <vector>

namespace CLI{
namespace RENDER{


/**
 * @class A_Render_Manager_Factory
*/
class A_Render_Manager_Factory
{
    public:
        
        /**
         * Initialize the Render-Manager Factory.
         *
         * @param[in] conn_type Connection Type used for rendering.
         * @param[in] cli_title CLI Title to post to render-managers.
         * @param[in] command_parser Command-Parser to process command information.
        */
        static void Initialize( CORE::ConnectionType const&   conn_type,
                                const std::string&            cli_title,
                                CMD::A_Command_Parser::ptr_t  command_parser );
        

        /**
         * @brief Get a Render-Manager Instance.
         *
         * @param[in] instance_id Instance of the render manager.
        */
        static A_Render_Manager_Base::ptr_t Instance_Of( const int& instance_id );
        
        
        /**
         * @brief Register a Custom Render Window
         *
         * @param[in] render_window Render window to add to the system.
         */
        static int Register_Custom_Render_Window( An_ASCII_Render_Window_Base::ptr_t render_window );
        

        /**
         * @brief Check if Initialized.
         * 
         * @return True if initialized, false otherwise.
        */
        static bool Is_Initialized();

    private:

        /**
         * @brief Default Constructor
        */
        A_Render_Manager_Factory();


        /**
         * @brief Constructor
         *
         * @param[in] conn_type Connection-Type used to decide which driver to use.
         * @param[in] cli_title Title for the CLI Main Window.
         * @param[in] command_parser Command-Parser for processing command results.
        */
        A_Render_Manager_Factory( CORE::ConnectionType const&  conn_type,
                                  const std::string&           cli_title,
                                  CMD::A_Command_Parser::ptr_t command_parser );

        
        /**
         * @brief Copy Constructor
         *
         * @note This method has been deleted as it should never be used.
        */
        A_Render_Manager_Factory( A_Render_Manager_Factory const& other ) = delete;
        

        /**
         * @brief Create a new instance.
         *
         * @param[in] instance_id ID to load into the render-manager.  Used for grabbing the driver and state.
         */
        A_Render_Manager_Base::ptr_t Create_Manager_Instance( const int& instance_id )const;
   
        
        /**
         * @brief Get Factory
        */
        static A_Render_Manager_Factory& Get_Factory_Instance();

        
        /// Class Name
        std::string m_class_name;

        /// Render Manager List
        std::vector<A_Render_Manager_Base::ptr_t> m_render_managers;

        /// Configuration Items
        CORE::ConnectionType m_conn_type;

        /// CLI Title
        const std::string m_cli_title;

        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;

        /// Custom Window
        std::vector<An_ASCII_Render_Window_Base::ptr_t> m_custom_render_windows;
        
        /// Initialized Flag
        bool m_is_initialized;

}; // End of A_Render_Manager_Factory

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
