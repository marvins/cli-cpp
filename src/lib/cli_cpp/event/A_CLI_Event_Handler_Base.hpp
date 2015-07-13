/**
 * @file    A_CLI_Event_Handler_Base.hpp
 * @author  Marvin Smith
 * @date    5/31/2015
*/
#ifndef __CLI_CPP_LIB_CORE_A_CLI_EVENT_HANDLER_BASE_HPP__
#define __CLI_CPP_LIB_CORE_A_CLI_EVENT_HANDLER_BASE_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>


namespace CLI{
namespace EVT{


/**
 * @class A_CLI_Event_Handler_Base
*/
class A_CLI_Event_Handler_Base
{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_CLI_Event_Handler_Base> ptr_t;

        /**
         * @brief Constructor
        */
        A_CLI_Event_Handler_Base();
    

        /**
         * @brief Check if Event is Valid.
         *
         * Default behavior, unless implemented is to always return true.
         *
         * @param[in] event Event value to evaluate.
         *
         * @return True if valid, false otherwise,
        */
        inline virtual bool Is_Supported_Event( const int& event )const{
            return true;
        }


        /**
         * @brief Process Event
        */
        virtual void Process_Event( const int& instance,
                                    const int& event ) = 0;


        /**
         * @brief Return the Handler Name.
         *
         * @return Class Name
        */
        inline virtual std::string Get_Handler_Name()const{
            return m_class_name;
        }


    private:
        
        /// Class Name
        std::string m_class_name;

}; // End of A_CLI_Event_Handler_Base Class

} // End of EVT Namespace
} // End of CLI Namespace

#endif
