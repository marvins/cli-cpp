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

/// Instance
std::shared_ptr<A_Render_State_Factory>  factory;

/***************************************/
/*          Create Instance            */
/***************************************/
A_Render_State::ptr_t A_Render_State_Factory::Instance_Of( const int& instance )
{

    // Check that the factory is initialized
    if( factory == nullptr ){
        return nullptr;
    }

    // Otherwise, make sure the instance is not over the max
    if( instance >= factory.m_instances.size() ){
        m_instances.resize( instance+1, std::make_shared<A_Render_State>( factory->m_command_parser ));
    }

    // Check if the instance is null
    if( m_instances[instance] == nullptr ){
        m_instances[instance] = std::make_shared<A_Render_State>( factory->m_command_parser );
    }

    // Otherwise, return instance
    return m_instances[instance];

}

/**********************************/
/*          Constructor           */
/**********************************/
A_Render_State_Factory::A_Render_State_Factory( CMD::A_Command_Parser::ptr_t command_parser )
  : m_class_name("A_Render_State_Factory"),
    m_command_parser(command_parser)
{
}

/**********************************/
/*          Initialize            */
/**********************************/
void A_Render_State_Factory::Initialize( CMD::A_Command_Parser::ptr_t command_parser )
{
    // Create instance
    factory = std::make_shared<A_Render_State_Factory>( command_parser );
}

} // End of RENDER Namespace
} // End of CLI    Namespace

