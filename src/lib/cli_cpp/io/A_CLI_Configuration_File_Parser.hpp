/**
 * @file    A_CLI_Configuration_File_Parser.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef CLI_A_CLI_CONFIGURATION_FILE_PARSER_HPP
#define CLI_A_CLI_CONFIGURATION_FILE_PARSER_HPP

// C++ Standard Libraries
#include <string>
#include <vector>


// CLI Libraries
#include "../cli/A_CLI_Manager_Configuration.hpp"
#include "../cli/A_Connection_Manager_Base_Config.hpp"
#include "../cmd/A_Command_Queue_Config.hpp"
#include "../event/Event_Manager_Config.hpp"


namespace CLI{
namespace IO{
namespace CONFIG{

/**
 * @class A_CLI_Configuration_File_Parser
 */
class A_CLI_Configuration_File_Parser{

    public:
        
        /**
         * @brief Constructor
         *
         * @param[in] config_path Path to configuration file.
         */
        A_CLI_Configuration_File_Parser( const std::string& config_path );
    
        
        /**
         * @brief Get the CLI Manager Configuration.
         *
         * @return CLI Manager Configuration Object.
         */
        inline A_CLI_Manager_Configuration Get_CLI_Manager_Configuration()const{
            return m_current_configuration;
        }
        

        /**
         * @brief Valid Status
         *
         * @return valid status
         */
        inline bool Is_Valid()const{
            return m_is_valid;
        }


        /**
         * @brief Update the Configuration File
        */
        void Write();


    private:

        /**
         * @brief Parse the configuration file.
         */
        void Parse_Configuration_File();
        
    
        /// Class Name
        std::string m_class_name;

        
        /// Configuration File Path
        std::string m_config_pathname;

        
        /// Current Configuration
        A_CLI_Manager_Configuration m_current_configuration;


        /// Parsing Status
        bool m_is_valid;

}; // End of A_CLI_Configuration_File_Parser Class

} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

#endif
