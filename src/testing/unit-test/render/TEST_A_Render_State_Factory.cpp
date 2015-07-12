/**
 * @file    TEST_A_Render_State_Factory.cpp
 * @author  Marvin Smith
 * @date    7/12/2015
*/
#include <gtest/gtest.h>

// CLI Libraries
#include <cli_cpp/render/A_Render_State_Factory.hpp>

using namespace CLI;

/*****************************************/
/*      Test the Initialize Method       */
/*****************************************/
TEST( A_Render_State_Factory, Initialization )
{
    // Make sure it is not initialized
    if( RENDER::A_Render_State_Factory::Is_Initialized() == true ){
        RENDER::A_Render_State_Factory::Finalize();
    }

    // Check init status
    ASSERT_FALSE( RENDER::A_Render_State_Factory::Is_Initialized() );

    // Check instances
    for( int i=-2; i<5; i++ ){
        ASSERT_EQ( RENDER::A_Render_State_Factory::Instance_Of( i ), nullptr );
    }

    // Initialize with no command parser
    RENDER::A_Render_State_Factory::Initialize( nullptr );

    // Make sure it is not initialized
    ASSERT_FALSE( RENDER::A_Render_State_Factory::Is_Initialized() );
    
    // Check instances
    for( int i=-2; i<5; i++ ){
        ASSERT_EQ( RENDER::A_Render_State_Factory::Instance_Of( i ), nullptr );
    }

}

