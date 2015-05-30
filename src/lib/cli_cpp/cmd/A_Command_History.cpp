/**
 * @file    A_Command_History.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Command_History.hpp"

namespace CLI{
namespace CMD{


/*******************************/
/*         Add Entry           */
/*******************************/
void A_Command_History::Add_Entry( A_Command_History_Entry const& entry )
{
    m_command_history.push_back(entry);
}


/************************************/
/*          Clear History           */
/************************************/
void A_Command_History::Clear()
{
    m_command_history.clear();
}

} // End of CMD Namespace
} // End of CLI Namespace

