/**
 * @file    An_ASCII_History_Window.hpp
 * @author  Marvin Smith
 * @date    5/25/2015
*/
#ifndef __AN_ASCII_HISTORY_WINDOW_HPP__
#define __AN_ASCII_HISTORY_WINDOW_HPP__

// C++ Standard Libraries
#include <memory>
#include <vector>


// CLI Libraries
#include "../../cmd/A_Command_History.hpp"
#include "../../utility/String_Utilities.hpp"


namespace CLI{
namespace RENDER{

/**
 * @class An_ASCII_History_Window
*/
class An_ASCII_History_Window
{

    public:

        /// Pointer Type
        typedef std::shared_ptr<An_ASCII_History_Window> ptr_t;
        
        /**
         * @brief Constructor
         *
         * @param[in] command_history Command history reference.
        */
        An_ASCII_History_Window( CMD::A_Command_History::ptr_t command_history );


        /**
         * @brief Print table.
         *
         * @param[in] buffer_data Buffer data to print to.
         *
         * @return Status of the operation.
         */
         bool Print_Table( std::vector<std::string>& buffer_data,
                           const int&                min_row,
                           const int&                max_row,
                           const int&                min_col,
                           const int&                max_col) const;

    private:
        
        /// Class Name
        std::string m_class_name;

        /// Command History
        CMD::A_Command_History::ptr_t m_command_history;

        /// Table Headers
        std::vector<std::string> m_table_headers;
 
        /// Table Alignments
        std::vector<UTILS::StringAlignment> m_table_alignments;


}; // End of An_ASCII_History_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace


#endif
