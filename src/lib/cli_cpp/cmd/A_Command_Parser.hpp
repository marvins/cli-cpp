/**
 * @file    A_Command_Parser.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef __CLI_CPP_CMD_A_COMMAND_PARSER_HPP__
#define __CLI_CPP_CMD_A_COMMAND_PARSER_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>
#include <vector>

// CLI Libraries
#include "A_CLI_Command.hpp"
#include "A_Command.hpp"
#include "A_Command_Result.hpp"


namespace CLI{
namespace CMD{

/**
 * @class A_Command_Parser
*/
class A_Command_Parser {

    public:

        /// Pointer Type
        typedef std::shared_ptr<A_Command_Parser> ptr_t;

        
        /**
         * @brief Constructor.
         * 
         * @param[in] regex_split_pattern Pattern to split the input commands for separating args from the name.
         * @param[in] cli_command_list List of CLI Commands.
         * @param[in] command_list List of regular, user-provided commands.
        */
        A_Command_Parser( const std::string&                 regex_split_pattern,
                          const std::vector<A_CLI_Command>&  parser_command_list,
                          const std::vector<A_Command>&      command_list );

        
        /**
         * @brief Evaluate Command
         *
         * @param[in] test_str String to evaluate.
         *
         * @return Command result.
         */
        A_Command_Result Evaluate_Command( const std::string& test_str ) const;
        

        /**
         * @brief Get the current command list.
         *
         * @return Command list.
         */
        inline std::vector<A_Command> Get_Command_List()const
        {
            return m_command_list;
        }


        /**
         * @brief Get the parser command list.
         *
         * @return Parser command list
         */
        inline std::vector<A_CLI_Command> Get_Parser_Command_List()const{
            return m_parser_command_list;
        }

    
    private:
    
        /**
         * @brief Parse the string.
         */
        std::vector<std::string> Parse_String( const std::string& test_str )const;


        /// Class Name
        std::string m_class_name;

        /// Command List
        std::vector<A_Command> m_command_list;

        /// CLI Command List
        std::vector<A_CLI_Command> m_parser_command_list;

        /// Regex Split Pattern
        std::string m_regex_split_pattern;

}; // End of A_Command_Parser Class

} // End of CMD Namespace
} // End of CLI Namespace

#endif
