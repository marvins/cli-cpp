/**
 * @file    A_Render_State_Factory.cpp
 * @author  Marvin Smith
 * @date    7/11/2015
*/
#include "A_Render_State_Factory.hpp"

// C++ Libraries
#include <memory>

namespace CLI{
namespace RENDER{


/***************************************/
/*      Get the Factory Instance       */
/***************************************/
A_Render_State_Factory&  A_Render_State_Factory::Get_Factory_Instance()
{
    // Create instance
    static A_Render_State_Factory factory_instance;

    // Return
    return factory_instance;
}


/***************************************/
/*          Create Instance            */
/***************************************/
A_Render_State::ptr_t A_Render_State_Factory::Instance_Of( const int& instance )
{

    // Check that the factory is initialized
    if( Is_Initialized() == false ){
        return nullptr;
    }

    // Get the instance
    A_Render_State_Factory& factory = Get_Factory_Instance();


    // Otherwise, make sure the instance is not over the max
    if( instance >= factory.m_instances.size() ){
        factory.m_instances.resize( instance+1, nullptr );
    }


    // Check if the instance is null
    if( factory.m_instances[instance] == nullptr ){
        factory.m_instances[instance] = std::make_shared<A_Render_State>( instance,
                                                                          factory.m_command_parser );
    }

    // Otherwise, return instance
    return factory.m_instances[instance];

}

/**********************************/
/*          Constructor           */
/**********************************/
A_Render_State_Factory::A_Render_State_Factory()
  : m_class_name("A_Render_State_Factory"),
    m_command_parser(nullptr),
    m_is_initialized(false)
{
}

/**********************************/
/*          Initialize            */
/**********************************/
void A_Render_State_Factory::Initialize( CMD::A_Command_Parser::ptr_t command_parser )
{
    // Do not initialize if command parser is null
    if( command_parser == nullptr ){
        return;
    }

    // Create instance
    A_Render_State_Factory& factory = Get_Factory_Instance();
    
    // Set the command parser
    factory.m_command_parser = command_parser;

    // Set the init flag
    factory.m_is_initialized = true;
}


/*******************************/
/*          Finalize           */
/*******************************/
void A_Render_State_Factory::Finalize()
{
    // Get the instance
    A_Render_State_Factory& factory = Get_Factory_Instance();

    // Clear it
    factory = A_Render_State_Factory();

}

/*************************************/
/*       Check if Initialized        */
/*************************************/
bool A_Render_State_Factory::Is_Initialized()
{
    return Get_Factory_Instance().m_is_initialized;
}


} // End of RENDER Namespace
} // End of CLI    Namespace

