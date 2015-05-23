/**
 * @file    A_Command_History.hpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#ifndef __CLI_CPP_CMD_A_COMMAND_HISTORY_HPP__
#define __CLI_CPP_CMD_A_COMMAND_HISTORY_HPP__

// C++ Standard Libraries
#include <deque>

// CLI Libraries
#include "A_Command_History_Entry.hpp" 

namespace CLI{
namespace CMD{


/**
 * @brief A_Command_History
 */
class A_Command_History{

    public:

        /// Pointer TYpe
        typedef std::shared_ptr<A_Command_History> ptr_t;


        /**
         * @brief Add Entry
         */
        void Add_Entry( const A_Command_History_Entry& entry );

        
        /**
         * @brief Get entry
         */
        inline A_Command_History_Entry Get_Entry( const int& entry )const{
            return m_command_history[entry];
        }

        
        /**
         * @brief Get back entry.
         */
         inline A_Command_History_Entry Get_Back()const{
             return m_command_history.back();
         }

        
        /**
         * @brief Get the size.
         */
        inline int Size()const{
            return m_command_history.size();
        }

        

    private:
        
        /// History
        std::deque<A_Command_History_Entry> m_command_history;


}; // End A_Command_History Class


} // End of CMD Namespace
} // End of CLI Namespace

#endif
