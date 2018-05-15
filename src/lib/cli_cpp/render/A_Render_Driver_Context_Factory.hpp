/**
 * @file    A_Render_Driver_Context_Driver_Factory.hpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#ifndef CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_FACTORY_HPP
#define CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_FACTORY_HPP

// C++ Standard Libraries
#include <map>
#include <string>

// CLI Libraries
#include "../core/ConnectionType.hpp"
#include "../core/SessionType.hpp"
#include "A_Render_Driver_Context_Base.hpp"

namespace CLI{
namespace RENDER{

/**
 * @class A_Render_Driver_Context_Factory
 *
 * @brief Constructs the proper Render Driver Context object.
 */
class A_Render_Driver_Context_Factory
{
    public:
        
        /**
         * @brief Initialize the context driver.
        */
        static void Initialize( std::map<CORE::SessionType,RENDER::Render_Driver_Config_Base::ptr_t> render_configs );
        
        
        /**
         * @brief Finalize the Factory.
        */
        static void Finalize();

        
        /**
         * @brief Create a driver context instance.
        */
        static A_Render_Driver_Context_Base::ptr_t Create_Instance( CORE::SessionType session_type );
        

        /**
         * @brief Check if Initialized.
         *
         * @return True if initialized, false otherwise.
        */
        static bool Is_Initialized();


    private:

        /**
         * @brief Get the Factory Instance.
         *
         * @return Render-Driver Context Factory instance.
        */
        static A_Render_Driver_Context_Factory& Get_Factory_Instance();
        
        /**
         * @brief Constructor
        */
        A_Render_Driver_Context_Factory();

        /// Class Name
        std::string m_class_name;
        
        /// Render-COnfig
        std::map<CORE::SessionType,RENDER::Render_Driver_Config_Base::ptr_t> m_render_configs;
        
        /// Initialized Flag
        bool m_is_initialized;

}; // End of A_Render_Driver_Context_Factory Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
