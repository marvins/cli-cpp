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
std::string CLI_Event_Type_To_String( int event_id )
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

        // CLI Async Show
        case (int)CLI_Event_Type::CLI_ASYNC_SHOW:
            return "CLI_ASYNC_SHOW";

        // Numberic Values
        case (int)CLI_Event_Type::KEYBOARD_0: return "KEYBOARD_0";
        case (int)CLI_Event_Type::KEYBOARD_1: return "KEYBOARD_1";
        case (int)CLI_Event_Type::KEYBOARD_2: return "KEYBOARD_2";
        case (int)CLI_Event_Type::KEYBOARD_3: return "KEYBOARD_3";
        case (int)CLI_Event_Type::KEYBOARD_4: return "KEYBOARD_4";
        case (int)CLI_Event_Type::KEYBOARD_5: return "KEYBOARD_5";
        case (int)CLI_Event_Type::KEYBOARD_6: return "KEYBOARD_6";
        case (int)CLI_Event_Type::KEYBOARD_7: return "KEYBOARD_7";
        case (int)CLI_Event_Type::KEYBOARD_8: return "KEYBOARD_8";
        case (int)CLI_Event_Type::KEYBOARD_9: return "KEYBOARD_9";
    }


    // return unknown
    return "UNKNOWN";
}


} // End of CLI Namespace

