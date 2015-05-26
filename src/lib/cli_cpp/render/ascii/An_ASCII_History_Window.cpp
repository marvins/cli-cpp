/**
 * @file    An_ASCII_History_Window.cpp
 * @author  Marvin Smith
 * @date    5/25/2015
*/
#include "An_ASCII_History_Window.hpp"


namespace CLI{
namespace RENDER{
namespace ASCII{


/**************************************/
/*            Constructor             */
/**************************************/
An_ASCII_History_Window::An_ASCII_History_Window( CMD::A_Command_History::ptr_t command_history )
  : m_class_name("An_ASCII_History_Window"),
    m_command_history(command_history)
{
}


/*****************************************/
/*        Print Table Information        */
/*****************************************/
bool An_ASCII_History_Window::Print_Table( std::vector<std::string>& buffer_data,
                                           int const&                min_row,
                                           int const&                max_row,
                                           int const&                min_col )const
{
    // Iterate over the table


    // Return successful operation
    return true;
}


} // End of ASCII  Namespace
} // End of RENDER Namespace
} // End of CLI    Namespace




