/**
 * @file    A_Command_Argument.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef __CLI_CMD_A_CLI_COMMAND_ARGUMENT_HPP__
#define __CLI_CMD_A_CLI_COMMAND_ARGUMENT_HPP__

// CLI Libraries
#include "CommandArgumentType.hpp"

// C++ Standard Libraries
#include <string>
#include <vector>


namespace CLI{
namespace CMD{

/**
 * @class A_Command_Argument
*/
class A_Command_Argument{

    public:
        
        /**
         * @brief Default Constructor
        */
        A_Command_Argument();


        /**
         * @brief Constructor
         * 
         * @param[in] arg_name Argument name.
         * @param[in] arg_type Argument type.
         * @param[in] arg_description Description of the argument's purpose or function.
         * @param[in] arg_required Flag if the argument is required on input.
         * @param[in] arg_default_value Default value if the argument is not provided.
        */
        A_Command_Argument( const std::string&          arg_name,
                            const CommandArgumentType&  arg_type,
                            const std::string&          arg_description,
                            const bool&                 arg_required = true,
                            const std::string&          arg_default_value = "" );
        
        
        /**
         * @brief Constructor
         * 
         * @param[in] arg_name Argument name.
         * @param[in] arg_type Argument type.
         * @param[in] arg_description Description of the argument's purpose or function.
         * @param[in] arg_required Flag if the argument is required on input.
         * @param[in] arg_default_value Default value if the argument is not provided.
         * @param[in] arg_autocomplete_path   Flag if we want to auto-complete path values (Only valid on PATH types).
         * @param[in] arg_autocomplete_terms  Argument autocomplete terms.
        */
        A_Command_Argument( const std::string&              arg_name,
                            const CommandArgumentType&      arg_type,
                            const std::string&              arg_description,
                            const bool&                     arg_required,
                            const std::string&              arg_default_value,
                            const bool&                     arg_autocomplete_path,
                            std::vector<std::string>const&  arg_autocomplete_terms );


        /**
         * @brief Get the argument name.
         *
         * @return Argument name.
         */
        inline std::string Get_Name()const{
            return m_name;
        }


        /**
         * @brief Get the Argument Type.
         *
         * @return Argument type (See \CommandArgumentType).
         */
        inline CommandArgumentType Get_Type()const{
            return m_type;
        }


        /**
         * @brief Get the argument description.
         *
         * @return Argument description.
        */
        inline std::string Get_Description()const{
            return m_description;
        }


        /**
         * @brief Get the default value.
         *
         * @return Default value.
         */
        inline std::string Get_Default_Value()const{
            return m_default_value;
        }
        
        /**
         * @brief Check if the input argument is a substring of an autocomplete element.
         *
         * @param[in] argument_name Argument to query.
         * @param[out] match_name Match if one exists.
         * 
         * @return True if found, false otherwise.
        */
        bool Is_Argument_Substring( const std::string& argument_name,
                                    std::string&       match_name )const;


        /**
         * @brief Check if the test string is a valid type for the argument.
         *
         * @param[in] test_str Test string to evaluate.
         *
         * @return True if valid, false otherwise.
         */
        bool Is_Valid_Type( const std::string& test_str )const;
        

        /**
         * @brief Check if the parameter is required.
         *
         * @return True if required, false otherwise.
         */
        inline bool Is_Required()const{
            return m_required;
        }

        /**
         * @brief Equivalent Operator.
         *
         * This method will check if two arguments are the same.  Note that this will not 
         * check the description as that does not affect the outcome of the argument input.
         *
         * @param[in] other Command argument to compare.
         *
         * @return True if equivalent, false otherwise.
         */
        bool operator == ( const A_Command_Argument& other )const;
        
        
        /**
         * @brief Not-Equivalent Operator.
         *
         * This method will check if two arguments are not the same.  Note that this will not 
         * check the description as that does not affect the outcome of the argument input.
         *
         * @param[in] other Command argument to compare.
         *
         * @return True if not-equivalent, false otherwise.
         */
        bool operator != ( const A_Command_Argument& other )const;


        /**
         * @brief Print as a debug string.
         *
         * @param[in] offset Amount to offset the output by.
         *
         * @return String with info about the argument.
        */
        std::string To_Debug_String( const int& offset = 0 )const;


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Argument Name
        std::string m_name;

        /// Type
        CommandArgumentType m_type;

        /// Description
        std::string m_description;

        /// Default Value
        std::string m_default_value;

        /// Required
        bool m_required;

        /// Flag if we want to auto-complete the path
        bool m_autocomplete_path;

        /// Argument Autocomplete Terms
        std::vector<std::string> m_autocomplete_terms;

}; // End of A_Command_Argument Class

} // End of CMD Namespace
} // End of CLI Namespace

#endif
