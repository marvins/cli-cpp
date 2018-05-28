/**
 * @file    A_Command_Parser_Factory.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef CLI_CMD_CMD_A_COMMAND_PARSER_FACTORY_HPP
#define CLI_CMD_CMD_A_COMMAND_PARSER_FACTORY_HPP

// C++ Standard Libraries
#include <string>

// CLI Libraries
#include "A_Command_Parser.hpp"

namespace CLI{
namespace CMD{

/**
 * @class A_Command_Parser_Factory
 *
 * @brief Builds the command parser given a configuration file.
*/
class A_Command_Parser_Factory
{
    public:
        
        /**
         * @brief Create the Command-Parser.
         *
         * @param[in] configuration_path Path to the command configuration XML file.
         * @param[in] alias_support Flag if we want to allow alias shortcuts.
         * @param[in] alias_path Path to alias list.
         * @param[in] variable_support  Flag if we want to allow variables.
         * @param[in] variable_path     Path to the variable list file.
         *
         * @return Command parser pointer.  Null if there was an issue.
         */
        static A_Command_Parser::ptr_t  Initialize( const std::string&  configuration_path,
                                                    bool                alias_support,
                                                    const std::string&  alias_path,
                                                    bool                variable_support,
                                                    const std::string&  variable_path );
    
}; // End of A_Command_Parser_Factory Class

} // End of CMD Namespace
} // End of CLI Namespace

#endif
