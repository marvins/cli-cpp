/**
 * @file    A_Connection_Manager_Base_Config.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __CLI_A_CLI_CONNECTION_HANDLER_BASE_CONFIG_HPP__
#define __CLI_A_CLI_CONNECTION_HANDLER_BASE_CONFIG_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>

// CLI Libraries
#include "../core/ConnectionType.hpp"
#include "../core/SessionType.hpp"

namespace CLI{

/**
 * @class A_Connection_Manager_Base_Config
 */
class A_Connection_Manager_Base_Config{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Connection_Manager_Base_Config> ptr_t;

        /**
         * @brief Constructor
         */
        A_Connection_Manager_Base_Config();


        /**
         * @brief Destructor
         */
        virtual ~A_Connection_Manager_Base_Config();

        
        /**
         * @brief Get the Connection Type.
         *
         * @return ConnectionType.
        */
        inline virtual CORE::ConnectionType Get_ConnectionType()const{
            return CORE::ConnectionType::BASE;
        }


        /**
         * @brief Get the Session-Type
         * @return
         */
        virtual CORE::SessionType Get_Session_Type()const = 0;
        
        /**
         * @brief Print to Log String
         */
        virtual std::string To_Log_String( int offset )const = 0;


    private:
        
        /// Class Name
        std::string m_class_name;

}; // End of A_Connection_Manager_Base_Config Class


} // End of CLI Namespace

#endif
