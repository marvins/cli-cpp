/**
 * @file    CLI_Event_Type.cpp
 * @author  Marvin Smith
 * @date    11/12/2015
*/
#include "CLI_Event_Type.hpp"


namespace CLI{


/******************************************************/
/*          Convert CLI Event Type to String          */
/******************************************************/
std::string CLI_Event_Type_To_String( const int& event_id )
{
    
    switch(event_id)
    {
        // CLI Shutdown
        case (int)CLI_Event_Type::CLI_SHUTDOWN:
            return "CLI_SHUTDOWN";

        // CLI Refresh
        case (int)CLI_Event_Type::CLI_REFRESH:
            return "CLI_REFRESH";

        // Char
        case (int)CLI_Event_Type::CLI_VARIABLE_SHOW:
            return "CLI_VARIABLE_SHOW";

        // NULL
        case (int)CLI_Event_Type::CLI_NULL:
            return "CLI_NULL";

    }

    // return unknown
    return "UNKNOWN";
}


} // End of CLI Namespace

