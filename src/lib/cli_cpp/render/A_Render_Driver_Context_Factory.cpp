/**
 * @file    A_Render_Driver_Context_Factory.cpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#include "A_Render_Driver_Context_Factory.hpp"

// CLI Libraries
#include "A_Render_Driver_Context_ASCII.hpp"
#include "../utility/Log_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>
#include <memory>



namespace CLI{
namespace RENDER{


/**************************************/
/*       Get Factory Instance         */
/**************************************/
A_Render_Driver_Context_Factory& A_Render_Driver_Context_Factory::Get_Factory_Instance()
{
    // Create Instance
    static A_Render_Driver_Context_Factory factory_instance;

    // return instance
    return factory_instance;
}


/**************************************/
/*        Check if Initialized        */
/**************************************/
bool A_Render_Driver_Context_Factory::Is_Initialized()
{
    return Get_Factory_Instance().m_is_initialized;
}


/*************************/
/*      Initialize       */
/*************************/
void A_Render_Driver_Context_Factory::Initialize( std::map<CORE::SessionType,RENDER::Render_Driver_Config_Base::ptr_t> render_configs )
{
    // Log Entry
    const std::string m_class_name = "A_Render_Driver_Context_Factory";
    CLI_LOG_CLASS_ENTRY();

    // Get the instance
    A_Render_Driver_Context_Factory& context_factory = Get_Factory_Instance();

    // Call the constructor
    context_factory.m_render_configs = render_configs;
    context_factory.m_is_initialized  = true;
    
    // Log Exit
    CLI_LOG_CLASS_EXIT();
}


/*******************************/
/*          Finalize           */
/*******************************/
void A_Render_Driver_Context_Factory::Finalize()
{
    
    // Log Entry
    const std::string m_class_name = "A_Render_Driver_Context_Factory";
    CLI_LOG_CLASS_ENTRY();

    // Get the instance
    A_Render_Driver_Context_Factory& context_factory = Get_Factory_Instance();

    // Reset
    context_factory = A_Render_Driver_Context_Factory();
    
    // Log Exit
    CLI_LOG_CLASS_EXIT();
}


/******************************************/
/*          Create an Instance            */
/******************************************/
A_Render_Driver_Context_Base::ptr_t A_Render_Driver_Context_Factory::Create_Instance( CORE::SessionType session_type )
{
    
    const std::string m_class_name = "A_Render_Driver_Context_Factory";
    CLI_LOG_CLASS_ENTRY();
    
    // Make sure the factory exists
    if( Is_Initialized() == false )
    {
        BOOST_LOG_TRIVIAL(error) << "Render-Driver Context Factory is null.";
        return nullptr;
    }

    // Get the context factory
    A_Render_Driver_Context_Factory& context_factory = Get_Factory_Instance();
    

    // Return new instance
    switch(session_type)
    {
        case CORE::SessionType::TELNET:
            return std::make_shared<A_Render_Driver_Context_ASCII>( context_factory.m_render_configs[session_type] );
            
        case CORE::SessionType::JSON:
        default:
            CLI_LOG_CLASS( error,
                           "Unsupported Session-Type: " + CORE::SessionTypeToString(session_type));
            return nullptr;
    }

    return nullptr;
}


/**********************************/
/*          Constructor           */
/**********************************/
A_Render_Driver_Context_Factory::A_Render_Driver_Context_Factory()
  : m_class_name("A_Render_Driver_Context_Factory"),
    m_is_initialized(false)
{
}


} // End of RENDER Namespace
} // End of CLI    Namespace

