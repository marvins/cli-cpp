/**
 * @file    A_Command_Parser_Factory.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef __CLI_CMD_CMD_A_COMMAND_PARSER_FACTORY_HPP__
#define __CLI_CMD_CMD_A_COMMAND_PARSER_FACTORY_HPP__

// C++ Standard Libraries
#include <string>

// CLI Libraries
#include "A_Command_Parser.hpp"

namespace CLI{
namespace CMD{

/**
 * @class A_Command_Parser_Factory
*/
class A_Command_Parser_Factory{

    public:
        
        /**
         * @brief Create
         */
        static A_Command_Parser::ptr_t  Initialize( const std::string& configuration_path );


}; // End of A_Command_Parser_Factory Class

} // End of CMD Namespace
} // End of CLI Namespace

#endif
