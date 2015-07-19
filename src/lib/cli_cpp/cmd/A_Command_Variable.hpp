/**
 * @file    A_Command_Variable.hpp
 * @author  Marvin Smith
 * @date    7/19/2015
*/
#ifndef __CLI_CPP_CMD_A_COMMAND_VARIABLE_HPP__
#define __CLI_CPP_CMD_A_COMMAND_VARIABLE_HPP__


// C++ Libraries
#include <string>
#include <vector>


namespace CLI{
namespace CMD{

/**
 * @class A_Command_Variable
 *
 * @brief Contains information about CLI Command Variables.
*/
class A_Command_Variable
{

    public:
        
        /**
         * @brief Constructor
        */
        A_Command_Variable( std::string const&  name,
                            std::string const&  value );
        

        /**
         * @brief Get the Variable Name
        */
        inline std::string Get_Name()const{
            return m_name;
        }

        
        /**
         * @brief Get the Variable Value.
        */
        inline std::string Get_Value()const{
            return m_value;
        }


        /**
         * @brief Process Variable List
         *
         * @param[in] variable_list List of variables to check for.
         * @param[in/out] components    List of candidates to check.
        */
        static void Process_Variables( std::vector<A_Command_Variable> const& variables,
                                       std::vector<std::string>&              components );


        /**
         * @brief Check if variable is a valid candidate
        */
        static bool Is_Valid_Candidate( const std::string& candidate );

    private:
        
        /// Class Name
        std::string m_class_name;

        /// Variable Name
        std::string m_name;

        /// Variable Value
        std::string m_value;

}; // End of A_Command_Variable Class

} // End of CMD Namespace
} // End of CLI Namespace

#endif
