/**
 * @file    Init_Utilities.hpp
 * @author  Marvin Smith
 * @date    7/4/2015
*/
#ifndef __CLI_CPP_APP_UTILS_INIT_UTILITIES_HPP__
#define __CLI_CPP_APP_UTILS_INIT_UTILITIES_HPP__

// App Libraries
#include "../core/State_Manager.hpp"

// CLI Libraries
#include <cli_cpp/cli/A_CLI_Manager.hpp>


/**
 * @brief Register Command Response Handlers
 *
 * @param[in/out] cli_manager
 * @param[in]     state_manager 
*/
void Register_Command_Response_Handlers( CLI::A_CLI_Manager::ptr_t  cli_manager,
                                         State_Manager&             state_manager  );

        

/**
 * @brief Register Rendering Windows.
 *
 * @param[in/out] cli_manager   CLI Manager
 * @param[in]     state_manager State Manager.
*/
bool Register_Render_Windows( CLI::A_CLI_Manager::ptr_t  cli_manager,
                              State_Manager&             state_manager );


#endif
