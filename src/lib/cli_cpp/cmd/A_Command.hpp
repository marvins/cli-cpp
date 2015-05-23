/**
 * @file    A_Command.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef __CLI_CMD_A_COMMAND_HPP__
#define __CLI_CMD_A_COMMAND_HPP__

// C++ Standard Libraries
#include <string>
#include <vector>

// CLI Arguments
#include "A_Command_Argument.hpp"


namespace CLI{
namespace CMD{

/**
 * @class A_Command
 *
 * @brief Stores Command attributes such as the name, description, arguments, and if a response is required.
*/
class A_Command{

    public:
        
        /**
         * @brief Default Constructor
        */
        A_Command();


        /**
         * @brief Constructor
         *
         * @param[in] command_name          Name of the command.
         * @param[in] command_description   Description of the command.
         * @param[in] command_expect_response  Flag if the command should return a response.
        */
        A_Command( const std::string&    command_name,
                   const std::string&    command_description,
                   const bool&           command_expect_response );

        /**
         * @brief Constructor
         *
         * @param[in] command_name             Name of the command.
         * @param[in] command_description      Description of the command.
         * @param[in] command_expect_response  Flag if the command should return a response.
         * @param[in] command_arguments        Command arguments.
         */
        A_Command( const std::string&                         command_name,
                   const std::string&                         command_description,
                   const bool&                                command_expect_response,
                   const std::vector<A_Command_Argument>& command_arguments );


        /**
         * @brief Get the Command Name.
         * 
         * @return Command name.
         */
        inline std::string Get_Name()const{
            return m_command_name;
        }


        /**
         * @brief Get the command description.
         */
        inline std::string Get_Description()const{
            return m_command_description;
        }


        /**
         * @brief Check if a response is required.
         */
        inline bool Response_Expected()const{
            return m_expect_response;
        }


        /**
         * @brief Get the argument list.
         *
         * @return Argument list.
         */
        inline std::vector<A_Command_Argument> Get_Argument_List()const
        {
            return m_command_argument_list;
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
         * @brief Check if the input command names matches this command.
         *
         * @param[in] command_name Command name to test.
         *
         * @return True if there is a match, false otherwise.
         */
        bool Is_Name_Match( const std::string& command_name )const;
        

        /**
         * @brief Print as a debug string.
         */
        std::string To_Debug_String()const;


    private:
        /// Class Name
        std::string m_class_name;

        /// Command Name
        std::string m_command_name;

        /// Command Description
        std::string m_command_description;

        /// Command Argument List
        std::vector<A_Command_Argument> m_command_argument_list;
        
        /// Expect Response Flag
        bool m_expect_response;

}; // End of A_Command 

} // End of CMD Namespace
} // End of CLI Namespace

#endif
