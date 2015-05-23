/**
 * @file    A_Connection_Manager_Local.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef __CLI_CPP_CLI_A_CONNECTION_MANAGER_LOCAL_HPP__
#define __CLI_CPP_CLI_A_CONNECTION_MANAGER_LOCAL_HPP__

// CLI Libraries
#include "A_Connection_Manager_Base.hpp"
#include "A_Connection_Manager_Local_Config.hpp"

// C++ Standard Libraries
#include <memory>

namespace CLI{

/**
 * @class A_Connection_Manager_Local
 */
class A_Connection_Manager_Local : public A_Connection_Manager_Base
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Connection_Manager_Local> ptr_t;

        
        /**
         * @brief Constructor
        */
        A_Connection_Manager_Local( A_Connection_Manager_Base_Config::ptr_t configuration );


        /**
         * @brief Destructor
         */
        ~A_Connection_Manager_Local();
    

    protected:
        
        /**
         * @brief Run the message handler
         */
        virtual void Run_Handler();



    private:
        
        /// Class Name
        std::string m_class_name;

        /// Configuration
        A_Connection_Manager_Local_Config::ptr_t  m_configuration;

}; // End of A_Connection_Manager_Local Class

} // End of CLI Namespace

#endif
