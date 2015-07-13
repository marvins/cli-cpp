/**
 * @file    A_Command_Alias.hpp
 * @author  Marvin Smith
 * @date    6/19/2015
 */
#ifndef __CLI_CMD_A_COMMAND_ALIAS_HPP__
#define __CLI_CMD_A_COMMAND_ALIAS_HPP__


// C++ Standard Libraries
#include <string>
#include <vector>


namespace CLI{
namespace CMD{

/**
 * @class A_Command_Alias
 */
class A_Command_Alias
{

    public:
        

        /**
         * @brief Constructor
         */
        A_Command_Alias();


        /**
         * @brief  Constructor
         *
         * @param[in] alias_name    Name or text the alias will use.
         * @param[in] command_text  Command text to map to alias.
         */
        A_Command_Alias( std::string const& alias_name,
                         std::string const& command_text );
        

        /**
         * @brief Get the Alias Name
         *
         * @return Alias name.
         */
        inline std::string Get_Alias_Name()const{
            return m_alias_name;
        }


        /**
         * @brief Get the Command Text.
         *
         * @return Command text.
         */
        inline std::string Get_Command_Text()const{
            return m_command_text;
        }


        /**
         * @brief Check if alias name matches the input string.
         *
         * @param[in] test_input  Input to evaluate.
         * @param[in] match_whole Flag if we want to match the entire input or just the beginning.  Allowing the beginning will enable passing args to the alias.
         * @param[out] formatted output  If a match is found, this is the formatted output.  If match_whole is false, then the left-overs will be appended.
         *
         * @return True if a match exists, false otherwise.
         */
        bool Is_Alias_Name_Match( const std::string& test_input,
                                  const bool&        match_whole,
                                  std::string&       formatted_output )const;
        
        /**
         * @brief Check if the input is a substring of the alias.
         *
         * @param[in] command_name Text to check.
         * 
         * @return True if a match, false otherwise.
         */
        bool Is_Alias_Name_Substring( const std::string& command_name )const;

        
        /**
         * @brief Generate Command Alias from CLI Input String.
         *
         * @param[in] input Text to evaluate.
         * @param[out] valid True if the command is valid, false otherwise.
         *
         * @return Command-Alias.
        */
        static A_Command_Alias From_CLI_Input( const std::string& input,
                                               bool& valid );
        
        
        /**
         * @brief Load an Alias Configuration File
         *
         * @param[in] pathname Path to load from.
         *
         * @return List of aliases.
         */
        static std::vector<A_Command_Alias> Load_Alias_Configuration_File( const std::string& pathname );
        

        /**
         * @brief Write an Alias Configuration File.
         *
         * @param[in] pathname Path to write to.
         * @param[in] alias_list List of aliases to write.
         * 
         * @return Status. True if successful, false otherwise.
        */
        static bool Write_Alias_Configuration_File( const std::string& pathname,
                                                    const std::vector<A_Command_Alias>& alias_list );
        

        /**
         * @brief Print the Command Alias as a debug string.
         *
         * @return formatted string.
        */
        std::string To_Debug_String()const;


    private:

        /// Class Name
        std::string m_class_name;

        /// Alias Text
        std::string m_alias_name;

        /// Alias Command Text
        std::string m_command_text;

}; // End of A_Command_Alias Class


} // End of CMD Namespace
} // End of CLI Namespace


#endif
