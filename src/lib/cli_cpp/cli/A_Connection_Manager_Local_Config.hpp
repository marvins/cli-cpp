/**
 * @file    A_Connection_Manager_Local_Config.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
*/
#ifndef __CLI_CPP_CLI_A_CONNECTION_MANAGER_LOCAL_CONFIG_HPP__
#define __CLI_CPP_CLI_A_CONNECTION_MANAGER_LOCAL_CONFIG_HPP__

// C++ Standard Libraries
#include <memory>

// CLI Libraries
#include "A_Connection_Manager_Base_Config.hpp"


namespace CLI{

/**
 * @class A_Connection_Manager_Local_Config
*/
class A_Connection_Manager_Local_Config : public A_Connection_Manager_Base_Config
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Connection_Manager_Local_Config> ptr_t;

        /**
         * @brief Constructor
        */
        A_Connection_Manager_Local_Config();


        /**
         * @brief Destructor
        */
        ~A_Connection_Manager_Local_Config();


    private:
        
        /// Class Name
        std::string m_class_name;


}; // End of A_Connection_Manager_Local_Config Class

} // End of CLI Namespace

#endif
