/**
 * @file    A_Command_Queue_Config.hpp
 * @author  Marvin Smith
 * @date    7/11/2015
*/
#ifndef __CLI_CPP_CMD_A_COMMAND_QUEUE_CONFIG_HPP__
#define __CLI_CPP_CMD_A_COMMAND_QUEUE_CONFIG_HPP__

// C++ Standard Libraries
#include <string>


namespace CLI{
namespace CMD{

/**
 * @class A_Command_Queue_Config
*/
class A_Command_Queue_Config
{

    public:
        
        /**
         * @brief Constructor
         *
         * @param[in] max_queue_size Max size of the command queue.
        */
        A_Command_Queue_Config( const int& max_queue_size = 10 );


        /**
         * @brief Get the Max Command Queue Size.
         *
         * @return Max Queue Size.
        */
        inline int Get_Max_Queue_Size()const{
            return m_max_queue_size;
        }


        /**
         * @brief PRint to Log String
        */
        std::string To_Log_String( int offset = 0 )const;

    private:
        
        /// Class Name
        std::string m_class_name;


        /// Max Queue Size
        int m_max_queue_size;


}; // End of A_Command_Queue_Config Class



} // End of CMD Namespace
} // End of CLI Namespace

#endif
