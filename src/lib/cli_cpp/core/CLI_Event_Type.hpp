/**
 * @file    CLI_Event_Type.hpp
 * @author  Marvin Smith
 * @date    6/1/2015
*/
#ifndef __CLI_CPP_CORE_CLI_EVENT_TYPE_HPP__
#define __CLI_CPP_CORE_CLI_EVENT_TYPE_HPP__

// C++ Standard Libraries
#include <cinttypes>

namespace CLI{

/**
 * @enum CLI_Event_Type
 *
 * @brief Enumerates different events that may be registered or triggered within CLI-CPP.
*/
enum class CLI_Event_Type : int32_t
{
    CLI_VARIABLE_SHOW    = -14 /**< Event for Print the Variable List.*/,
    CLI_VARIABLE_ADD     = -13 /**< Event for Adding a Variable to the Command-Parser.*/,
    CLI_VARIABLE_RM      = -12 /**< Event for Removing a Variable from the Command-Parser.*/,
    CLI_NULL             = -11 /**< Treat a null or no-op value.*/,
    CLI_PAUSE            = -10 /**< User requested to pause the CLI.*/,
    CLI_SLEEP            = -9  /**< User requested to sleep for a period of time.*/,
    CLI_REFRESH          = -8  /**< Event for refreshing the interface.*/,
    CLI_ALIAS_LIST       = -7  /**< Event for showing the alias list screen.*/,
    CLI_LOG              = -6  /**< Event for showing the log output screen.*/,
    CLI_HELP             = -5  /**< Event for showing the help windows.*/,
    CLI_BACK             = -4  /**< Event for returning to the main window.*/,
    CLI_SHUTDOWN         = -3  /**< Event for disconnecting the CLI.*/,
    UNKNOWN              = -1  /**< Unknown event.  Treat this as an error.*/,
    KEYBOARD_ENTER       = 13  /**< Enter Key. */,
    KEYBOARD_A           = 'A' /**< A Key.*/,
    KEYBOARD_B           = 'B' /**< B Key.*/,
    KEYBOARD_C           = 'C' /**< C Key.*/,
    KEYBOARD_D           = 'D',
    KEYBOARD_E           = 'E',
    KEYBOARD_F           = 'F',
    KEYBOARD_G           = 'G',
    KEYBOARD_H           = 'H',
    KEYBOARD_I           = 'I',
    KEYBOARD_J           = 'J',
    KEYBOARD_K           = 'K',
    KEYBOARD_L           = 'L',
    KEYBOARD_M           = 'M',
    KEYBOARD_N           = 'N',
    KEYBOARD_O           = 'O',
    KEYBOARD_P           = 'P',
    KEYBOARD_Q           = 'Q',
    KEYBOARD_R           = 'R',
    KEYBOARD_S           = 'S',
    KEYBOARD_T           = 'T',
    KEYBOARD_U           = 'U',
    KEYBOARD_V           = 'V',
    KEYBOARD_W           = 'W',
    KEYBOARD_X           = 'X',
    KEYBOARD_Y           = 'Y',
    KEYBOARD_Z           = 'Z',
    KEYBOARD_a           = 'a',
    KEYBOARD_b           = 'b',
    KEYBOARD_c           = 'c',
    KEYBOARD_d           = 'd',
    KEYBOARD_e           = 'e',
    KEYBOARD_f           = 'f',
    KEYBOARD_g           = 'g',
    KEYBOARD_h           = 'h',
    KEYBOARD_i           = 'i',
    KEYBOARD_j           = 'j',
    KEYBOARD_k           = 'k',
    KEYBOARD_l           = 'l',
    KEYBOARD_m           = 'm',
    KEYBOARD_n           = 'n',
    KEYBOARD_o           = 'o',
    KEYBOARD_p           = 'p',
    KEYBOARD_q           = 'q',
    KEYBOARD_r           = 'r',
    KEYBOARD_s           = 's',
    KEYBOARD_t           = 't',
    KEYBOARD_u           = 'u',
    KEYBOARD_v           = 'v',
    KEYBOARD_w           = 'w',
    KEYBOARD_x           = 'x',
    KEYBOARD_y           = 'y',
    KEYBOARD_z           = 'z',
    KEYBOARD_1           = '1',
    KEYBOARD_2           = '2',
    KEYBOARD_3           = '3',
    KEYBOARD_4           = '4',
    KEYBOARD_5           = '5',
    KEYBOARD_6           = '6',
    KEYBOARD_7           = '7',
    KEYBOARD_8           = '8',
    KEYBOARD_9           = '9',
    KEYBOARD_0           = '0',
    KEYBOARD_COLON       = ':',
    KEYBOARD_SEMICOLON   = ';',
    KEYBOARD_TAB_KEY     =   9,
    KEYBOARD_BACKSPACE   = 127,
    KEYBOARD_DELETE_KEY  = 500,
    KEYBOARD_LEFT_ARROW  = 501,
    KEYBOARD_RIGHT_ARROW = 502,
    KEYBOARD_UP_ARROW    = 503,
    KEYBOARD_DOWN_ARROW  = 504,
    KEYBOARD_F1          = 505,
    KEYBOARD_F2          = 506,
    KEYBOARD_F3          = 507,
    KEYBOARD_F4          = 508,
    KEYBOARD_F5          = 509,
    KEYBOARD_F6          = 510,
    KEYBOARD_F7          = 511,
    KEYBOARD_PG_DN       = 512,
    KEYBOARD_PG_UP       = 513,
    KEYBOARD_INSERT      = 514,
    KEYBOARD_HOME        = 515,
    KEYBOARD_END         = 516,
}; // End of event type enum

} // End of CLI  Namespace

#endif
