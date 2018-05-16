/**
 * @file    CLI_Configuration_File_Parser_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef CLI_CPP_IO_CONFIGURATION_FILE_PARSER_UTILITIES_HPP
#define CLI_CPP_IO_CONFIGURATION_FILE_PARSER_UTILITIES_HPP

// CLI Libraries
#include "../cli/A_Connection_Manager_Base_Config.hpp"
#include "../core/ConnectionType.hpp"
#include "../event/Event_Manager_Config.hpp"
#include "../thirdparty/pugixml.hpp"
#include "../cli/A_CLI_Manager_Configuration.hpp"


namespace CLI{
namespace IO{
namespace CONFIG{
namespace XML{

/**
 * @brief PugiXML Config Parser
 */
class A_CLI_Config_Parser_PugiXML
{
    public:
        
        /**
         * @brief Constructor
         *
         * @param config_pathname
         */
        A_CLI_Config_Parser_PugiXML( const std::string& config_pathname );
        
        
        /**
         * @brief Get the Connection-Manager Configuration
         */
        A_CLI_Manager_Configuration  Get_CLI_Manager_Config()const{
            return m_cli_manager_config;
        }
        
        
        /**
         * @brief Validity Flag
         */
        inline bool Is_Valid()const{
            return m_is_valid;
        }
        
    private:
        
        
        /**
         * @brief Parse Configuration
         */
        void Parse();
        
        
        /**
         * @brief Parse Log-Configuration
         */
        void Parse_Log_Node( pugi::xml_node& root_node );
        
        
        /**
         * @brief Parse Event-Manager Configuration
         *
         * @param root_node
         * @return
         */
        EVT::Event_Manager_Config  Parse_Event_Manager_Node( pugi::xml_node& root_node );
        
        
        /// Class Name
        std::string m_class_name;
        
        /// Configuration
        std::string m_config_pathname;
        
        /// CLI-Manager Config
        A_CLI_Manager_Configuration m_cli_manager_config;
        
        /// Valid Flag
        bool m_is_valid;
};


} // End of XML    Namespace
} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

#endif
