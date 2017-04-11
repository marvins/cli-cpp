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
        // CLI Show Variable
        case (int)CLI_Event_Type::CLI_VARIABLE_SHOW:
            return "CLI_VARIABLE_SHOW";

        // CLI Add Variable
        case (int)CLI_Event_Type::CLI_VARIABLE_ADD:
            return "CLI_VARIABLE_ADD";

        // CLI RM Variable
        case (int)CLI_Event_Type::CLI_VARIABLE_RM:
            return "CLI_VARIABLE_RM";

        // CLI Shutdown
        case (int)CLI_Event_Type::CLI_SHUTDOWN:
            return "CLI_SHUTDOWN";

        // CLI Refresh
        case (int)CLI_Event_Type::CLI_REFRESH:
            return "CLI_REFRESH";

        // NULL
        case (int)CLI_Event_Type::CLI_NULL:
            return "CLI_NULL";

        // SESSION_EVENT
        case (int)CLI_Event_Type::CLI_SESSION_EVENT:
            return "CLI_SESSION_EVENT";
    }

    // return unknown
    return "UNKNOWN";
}


} // End of CLI Namespace

