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


// Global Instance
//std::shared_ptr<
A_Render_Driver_Context_Factory* context_factory;

/*************************/
/*      Initialize       */
/*************************/
void A_Render_Driver_Context_Factory::Initialize( const CORE::ConnectionType& conn_type,
                                                  const std::string&          cli_title,
                                                  const int&                  window_rows,
                                                  const int&                  window_cols,
                                                  const bool&                 redirect_stdout,
                                                  const bool&                 redirect_stderr )
{
    // Call the constructor 
    context_factory = new A_Render_Driver_Context_Factory( conn_type,
                                                           cli_title,
                                                           window_rows,
                                                           window_cols,
                                                           redirect_stdout,
                                                           redirect_stderr );
}


/******************************************/
/*          Create an Instance            */
/******************************************/
A_Render_Driver_Context_Base::ptr_t A_Render_Driver_Context_Factory::Create_Instance()
{
    // Make sure the factory exists
    if( context_factory == nullptr ){
        BOOST_LOG_TRIVIAL(error) << "Render-Driver Context Factory is null.";
        return nullptr;
    }
    
    // Set the min content row
    int min_content_row = 2;
    int min_content_col = 1;

    // Return new instance
    if( context_factory->m_conn_type == CORE::ConnectionType::SOCKET ){
        return std::make_shared<A_Render_Driver_Context_ASCII>( context_factory->m_cli_title,
                                                                context_factory->m_window_rows,
                                                                context_factory->m_window_cols,
                                                                min_content_row,
                                                                min_content_col,
                                                                context_factory->m_redirect_stdout,
                                                                context_factory->m_redirect_stderr );
    }

    else{
        BOOST_LOG_TRIVIAL(error) << "unknown ConnectionType Value.";
        return nullptr;
    }

    return nullptr;
}


/**********************************/
/*          Constructor           */
/**********************************/
A_Render_Driver_Context_Factory::A_Render_Driver_Context_Factory( const CORE::ConnectionType& conn_type,
                                                                  const std::string&          cli_title,
                                                                  const int&                  window_rows,
                                                                  const int&                  window_cols,
                                                                  const bool&                 redirect_stdout,
                                                                  const bool&                 redirect_stderr )
  : m_class_name("A_Render_Driver_Context_Factory"),
    m_conn_type(conn_type),
    m_cli_title(cli_title),
    m_window_rows(window_rows),
    m_window_cols(window_cols),
    m_redirect_stdout(redirect_stdout),
    m_redirect_stderr(redirect_stderr)
{
}


} // End of RENDER Namespace
} // End of CLI    Namespace

