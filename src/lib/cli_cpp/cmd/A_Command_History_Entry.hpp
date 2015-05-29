/**
 * @file    A_Command_History_Entry.hpp
 * @author  Marvin Smith
 * @date    5/20/2015
 */
#ifndef __CLI_CPP_CMD_A_COMMAND_HISTORY_ENTRY_HPP__
#define __CLI_CPP_CMD_A_COMMAND_HISTORY_ENTRY_HPP__

// C++ Standard Libraries
#include <string>

// CLI Libraries
#include "A_Command_Result.hpp"


namespace CLI{
namespace CMD{


/**
 * @class A_Command_History_Entry
 *
 * @brief Stores the command which was processed along with the actual text entered.
 */
class A_Command_History_Entry{

    public:
        
    
        /**
         * @brief Constructor.
         *
         * @param[in] command_count Entry number corresponding to when the command was entered in order.
         * @param[in] command_string Actual user text entered.
         * @param[in] command_result Command result.
         */
        A_Command_History_Entry( const int&                    command_count,
                                 const std::string&            command_string,
                                 CMD::A_Command_Result::ptr_t  command_result );
   
        
        /**
         * @brief Get the Command ID.
         *
         * @return Command ID.
         */
        inline int Get_Command_ID()const{
            return m_command_id;
        }

        
        /**
         * @brief Get the Command String.
         *
         * @return Command string text.
         */
        inline std::string Get_Command_String()const{
            return m_command_string;
        }


        /**
         * @brief Get the command result
         */
        inline CMD::A_Command_Result Get_Command_Result(){
            return (*m_command_result);
        }


    private:
        
        /// Command Counter
        int m_command_id;


        /// Command String
        std::string m_command_string;


        /// Command Result
        CMD::A_Command_Result::ptr_t m_command_result;

}; // End of A_Command_History_Entry Class


} // End of CMD Namespace
} // End of CLI Namespace

#endif
