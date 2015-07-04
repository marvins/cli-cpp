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
#include "A_Command_Alias.hpp"
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
        A_Command_Parser( const std::string&                   regex_split_pattern,
                          const std::vector<A_CLI_Command>&    parser_command_list,
                          const std::vector<A_Command>&        command_list,
                          const std::vector<A_Command_Alias>&  alias_list,
                          const std::string&                   alias_pathname,
                          const bool&                          alias_list_write_access );

        
        /**
         * @brief Evaluate Command
         *
         * @param[in] test_str      String to evaluate.
         * @param[in] ignore_alias  Skip processing the alias list.
         *
         * This method will process the input test string and check if it is a valid command.
         * Note that the ignore_alias flag is used so that if the input matches an alias, the method 
         * can be called again to process the alias command text.
         *
         * @return Command result.
         */
        A_Command_Result Evaluate_Command( const std::string&  test_str,
                                           const bool&         ignore_alias = false ) const;
        

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
         * @brief Get the CLI command list.
         *
         * @return CLI command list
         */
        inline std::vector<A_CLI_Command> Get_CLI_Command_List()const{
            return m_cli_command_list;
        }


        /**
         * @brief Get the Command Alias List.
         *
         * @return Alias list.
        */
        inline std::vector<A_Command_Alias> Get_Alias_List()const{
            return m_alias_list;
        }
        

        /**
         * @brief Query Autocomplete
         *
         * @param[in] input_string Input string to check.
         * @param[in] Nearest match.
         */
        void Update_Autocomplete_String( const std::string&  input_string,
                                         std::string&        match_list )const;
        

        /**
         * @brief Add a Command to the Parser.
         *
         * @param[in] command Command to add.
        */
        void Add_Command( const A_Command& command );


        /**
         * @brief Add command alias.
         *
         * @param[in] new_alias
         */
        void Add_Command_Alias( const A_Command_Alias& new_alias );


        /**
         * @brief Remove Command Alias.
         *
         * @brief old_alias
         */
        void Remove_Command_Alias( const A_Command_Alias& old_alias );

    
    private:
    
        /// Class Name
        std::string m_class_name;

        /// Command List
        std::vector<A_Command> m_command_list;

        /// CLI Command List
        std::vector<A_CLI_Command> m_cli_command_list;

        /// Alias List
        std::vector<A_Command_Alias> m_alias_list;
        
        /// Alias Pathname
        std::string m_alias_pathname;

        /// Alias List Write Access
        bool m_alias_list_write_access;

        /// Regex Split Pattern
        std::string m_regex_split_pattern;

}; // End of A_Command_Parser Class

} // End of CMD Namespace
} // End of CLI Namespace

#endif
