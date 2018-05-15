/**
 * @file    A_CLI_Manager_Configuration.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef CLI_A_CLI_MANAGER_CONFIGURATION_HPP
#define CLI_A_CLI_MANAGER_CONFIGURATION_HPP

// C++ Standard Libraries
#include <map>
#include <string>
#include <vector>

// CLI Libraries
#include "A_Connection_Manager_Base.hpp"
#include "A_Connection_Manager_Base_Config.hpp"
#include "../core/ConnectionType.hpp"
#include "../core/SessionType.hpp"
#include "../cmd/A_Command_Parser.hpp"
#include "../event/Event_Manager_Config.hpp"
#include "../render/A_Render_Driver_Context_Base.hpp"
#include "../render/A_Render_Manager_Base.hpp"


namespace CLI{


/**
 * @class A_CLI_Manager_Configuration
 *
 * @brief Configuration parameters required for the CLI-Manager.
 */
class A_CLI_Manager_Configuration
{
    public:
        
        
        /**
         * @brief Default Constructor
         *
         * Don't use unless as there are no setters in this method
         */
        A_CLI_Manager_Configuration();
        

        /**
         * @brief Constructor
         */
        A_CLI_Manager_Configuration( std::vector<A_Connection_Manager_Base_Config::ptr_t> connection_configs,
                                     std::map<CORE::SessionType,
                                              RENDER::Render_Driver_Config_Base::ptr_t>   render_driver_configs,
                                     CMD::A_Command_Parser::ptr_t                         command_parser,
                                     CMD::A_Command_Queue_Config                          command_queue_config,
                                     EVT::Event_Manager_Config                            event_manager_config );


        /**
         * @brief Get the Connection-Manager Configuration.
         *
         * @return Connection-Manager configuration object.
        */
        inline std::vector<A_Connection_Manager_Base_Config::ptr_t> Get_Connection_Manager_Config()const{
            return m_connection_manager_configurations;
        }
        
        
        /**
         * @brief Get the Render-Driver Configurations
         * @return
         */
        inline std::map<CORE::SessionType,RENDER::Render_Driver_Config_Base::ptr_t> Get_Render_Driver_Configs()const{
            return m_render_driver_configs;
        }


        /**
         * @brief Get the Command Parser
         * 
         * @return Command Parser.
         */
        inline CMD::A_Command_Parser::ptr_t Get_Command_Parser()const{
            return m_command_parser;
        }


        /**
         * @brief Get the CLI Command Queue Configuration.
         *
         * @return Command-Queue Configuration
         */
        inline CMD::A_Command_Queue_Config Get_Command_Queue_Config()const{
            return m_command_queue_config;
        }


        /**
         * @brief Get the Event-Manager Configuration
         *
         * @return Event Manager config
         */
        inline EVT::Event_Manager_Config Get_Event_Manager_Config()const{
            return m_event_manager_config;
        }


        /**
         * @brief Check if the configuration is valid.
         *
         * @return True if valid, false otherwise.
         */
        bool Is_Valid()const;


    private:

        /// Class Name
        std::string m_class_name;

        /// Connection Manager Configuration
        std::vector<A_Connection_Manager_Base_Config::ptr_t> m_connection_manager_configurations;
        
        /// Render Configurations
        std::map<CORE::SessionType,RENDER::Render_Driver_Config_Base::ptr_t> m_render_driver_configs;

        /// Command Parser
        CMD::A_Command_Parser::ptr_t m_command_parser;

        /// Event Manager Configuration
        EVT::Event_Manager_Config m_event_manager_config;

        /// Command Queue Configuration
        CMD::A_Command_Queue_Config m_command_queue_config;


}; // End of A_CLI_Manager_Configuration Class


} // End of CLI Namespace

#endif
