/**
 * @file    A_CLI_Command.hpp
 * @author  Marvin Smith
 * @date    5/19/2015
 */
#ifndef __CLI_CPP_CMD_A_CLI_COMMAND_HPP__
#define __CLI_CPP_CMD_A_CLI_COMMAND_HPP__


// C++ Standard Libraries
#include <string>
#include <vector>

// CLI Libraries
#include "A_Command.hpp"
#include "A_Command_Argument.hpp"
#include "CommandParseStatus.hpp"

namespace CLI{
namespace CMD{


/**
 * @class A_CLI_Command
 *
 * @brief CLI-specific command.
 */
class A_CLI_Command{

    public:
        
        /**
         * @brief Constructor
         *
         * @param[in] mode Parsing mode type (Back, Help, Quit, etc).
         */
        A_CLI_Command( const CommandParseStatus& mode );
        

        /**
         * @brief Constructor
         *
         * @param[in] mode Command parse status mode.
         * @param[in] names Supported command names.
         * @param[in] formal_name Formal name of the command.
         * @param[in] description Description of the function's purpose.
         */
        A_CLI_Command( const CommandParseStatus&        mode,
                       const std::vector<std::string>&  names,
                       const std::string&               formal_name,
                       const std::string&               description );

        
        /**
         * @brief Get the mode type.
         *
         * @return Parsing command mode.
         */
        inline CommandParseStatus Get_Mode()const{
            return m_mode;
        }


        /**
         * @brief Add command name to list.
         *
         * @param[in] name Name to address command by.
         */
        void Add_Name( const std::string& name );
        

        /** 
         * @brief Add a Command Argument to the list.
         *
         * @param[in] arg Argument to add to the list.
        */
        void Add_Argument( const A_Command_Argument& arg );


        /**
         * @brief Check for Match between command and registered name.
         *
         * @param[in] name Name to compare against.
         */
        bool Is_Name_Match( const std::string& name )const;
        

        /**
         * @brief Check if name matches the substring
         */
        bool Is_Name_Substring( const std::string&  input_string,
                                std::string&        match_result )const;
        

        /**
         * @brief Check if the argument is a subset or matches the autocomplete set.
         *
         * @param[in] argument_index Specific argument to query.
         * @param[in] argument_name  Argument name to test.
         * @param[in] match_name     Matching name if one exists.
         *
         * @return True if subset, false otherwise.
        */
        bool Is_Argument_Substring( const int&         argument_index,
                                    const std::string& argument_name,
                                    std::string&       match_name ) const;

        
        /**
         * @brief Set the Formal Name
         *
         * @param[in] formal_name Name to print for user output.
         */
        void Set_Formal_Name( const std::string& formal_name );


        /**
         * @brief Get the formal name
         *
         * @return Formal name string.
         */
        inline std::string Get_Formal_Name()const{
            return m_formal_name;
        }


        /**
         * @brief Get the Description.
         *
         * @return Description string.
         */
        inline std::string Get_Description()const{
            return m_description;
        }


        /**
         * @brief Set the description.
         *
         * @param[in] description Description to set.
         */
        inline void Set_Description( const std::string& description ){
            m_description = description;
        }


        /**
         * @brief Get the name list.
         * 
         * @return list of command names.
         */
        inline std::vector<std::string> Get_Command_Name_List()const{
            return m_names;
        }


        /**
         * @brief Get the argument list.
         *
         * @return Argument list
        */
        inline std::vector<A_Command_Argument> Get_Argument_List()const{
            return m_command_argument_list;
        }
        
        
        /**
         * @brief Check if response expected.
         *
         * @return True if expected, false otherwise.
        */
        inline bool Response_Expected()const{
            return m_response_expected;
        }


        /**
         * @brief Set the Response Expected Flag.
         *
         * @param[in] response_expected value of the flag.
         */
        inline void Set_Response_Expected( const bool& response_expected ){
            m_response_expected = response_expected;
        }


        /**
         * @brief Get the requested argument.
         *
         * @param[in] index Position to fetch.
         *
         * @return Desired command.
         */
        inline A_Command_Argument Get_Command_Argument( const int& index )const{
            return m_command_argument_list[index];
        }

        
        /**
         * @brief Check an argument against the list to see if it is a valid type.
         *
         * @param[in] argument_id Index of argument to fetch.
         * @param[in] test_argument_value Value of argument to check type against.
         *
         * @return True if the test value has a valid type (i.e. Int, Float, Str, etc). False otherwise.
         */
        bool Check_Argument_Type( const int& argument_idx,
                                  const std::string& test_argument_value )const;

        
        /**
         * @brief Equivalent Operator
         *
         * @param[in] other CLI Command to compare.
         *
         * @return True if equal, false otherwise.
        */
        bool operator == ( A_CLI_Command const& other )const;
        

        /**
         * @brief Write out as command.
         *
         * @return Command structure
        */
        A_Command To_Command()const;


        /**
         * @brief Print as debug string.
         *
         * @return Debugging data about the cli command.
         */
        std::string To_Debug_String()const;

    
    private:
        
        /// Class Name
        std::string m_class_name;

        /// Mode
        CommandParseStatus m_mode;

        /// Names
        std::vector<std::string> m_names;

        /// Formal Name
        std::string m_formal_name;

        /// Description
        std::string m_description;

        /// List of arguments
        std::vector<A_Command_Argument> m_command_argument_list;
        
        /// Response Expected Flag
        bool m_response_expected;

}; // End of A_CLI_Command Class


} // End of CMD Namespace
} // End of CLI Namespace

#endif
