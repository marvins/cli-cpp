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
namespace CORE{

/**
 * @enum CLI_Event_Type
*/
enum class CLI_Event_Type : int32_t{
    CLI_LOG              = -6,
    CLI_HELP             = -5,
    CLI_BACK             = -4,
    CLI_SHUTDOWN         = -3,
    UNKNOWN              = -1,
    KEYBOARD_ENTER       = 13,
    KEYBOARD_A           = 'A',
    KEYBOARD_B           = 'B',
    KEYBOARD_C           = 'C',
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
    KEYBOARD_BACKSPACE   = 127,
    KEYBOARD_DELETE_KEY  = 500,
    KEYBOARD_LEFT_ARROW  = 501,
    KEYBOARD_RIGHT_ARROW = 502,
    KEYBOARD_UP_ARROW    = 503,
    KEYBOARD_DOWN_ARROW  = 504,
}; // End of event type enum

} // End of CORE Namespace
} // End of CLI  Namespace

#endif
