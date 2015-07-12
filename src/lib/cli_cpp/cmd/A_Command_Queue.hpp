/**
 * @file    A_Command_Queue.hpp
 * @author  Marvin Smith
 * @date    5/19/2015
*/
#ifndef __CLI_CPP_CMD_A_COMMAND_QUEUE_HPP__
#define __CLI_CPP_CMD_A_COMMAND_QUEUE_HPP__

// C++ Standard Libraries
#include <atomic>
#include <memory>
#include <mutex>
#include <semaphore.h>

// CLI Libraries
#include "A_Command_Queue_Config.hpp"
#include "A_Command_Result.hpp"

namespace CLI{
namespace CMD{

/**
 * @class A_Command_Queue
*/
class A_Command_Queue{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Command_Queue> ptr_t;


        /**
         * @brief Constructor
         *
         * @param[in] max_queue_size Max number of elements in the queue before blocking.
        */
        A_Command_Queue( const A_Command_Queue_Config& configuration );
        

        /**
         * @brief Destructor
        */
        ~A_Command_Queue();

        
        /**
         * @brief Add Command
         *
         * @param[in] command Command to push onto the queue.
         */
        void Push_Command( A_Command_Result::ptr_t const& command );


        /**
         * @brief Pop Command
         *
         * @return Next command on the queue.  If queue is empty, it will block.
         */
        A_Command_Result::ptr_t Pop_Command();


        /**
         * @brief Clear the Semaphore
        */
        void Clear();


    private:

        /// Class Name
        std::string m_class_name;


        /// Configuration 
        A_Command_Queue_Config m_configuration;

        
        /// Command Queue
        A_Command_Result::ptr_t* m_command_queue;
   

        /// Main Mutex
        std::mutex m_mtx;

        /// Counters
        sem_t* m_push_semaphore;
        sem_t* m_pop_semaphore;

        /// Head and Tail Cursors
        int m_head;
        int m_tail;
        
        /// Close Flag
        std::atomic<bool> m_close_flag;

}; // End of A_Command_Queue Class

} // End of CMD Namespace
} // End of CLI Namespace

#endif
