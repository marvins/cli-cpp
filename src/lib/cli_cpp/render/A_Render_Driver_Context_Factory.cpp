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
void A_Render_Driver_Context_Factory::Initialize( const CORE::ConnectionType& conn_type,
                                                  const std::string&          cli_title,
                                                  const int&                  window_rows,
                                                  const int&                  window_cols,
                                                  const bool&                 redirect_stdout,
                                                  const bool&                 redirect_stderr )
{
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " Method. File: " << __FILE__ << ", Line: " << __LINE__;

    // Get the instance
    A_Render_Driver_Context_Factory& context_factory = Get_Factory_Instance();


    // Call the constructor
    context_factory.m_conn_type       = conn_type;
    context_factory.m_cli_title       = cli_title;
    context_factory.m_window_rows     = window_rows;
    context_factory.m_window_cols     = window_cols;
    context_factory.m_redirect_stdout = redirect_stdout;
    context_factory.m_redirect_stderr = redirect_stderr;
    context_factory.m_is_initialized  = true;
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " Method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/*******************************/
/*          Finalize           */
/*******************************/
void A_Render_Driver_Context_Factory::Finalize()
{
    
    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " Method. File: " << __FILE__ << ", Line: " << __LINE__;

    // Get the instance
    A_Render_Driver_Context_Factory& context_factory = Get_Factory_Instance();

    // Reset
    context_factory = A_Render_Driver_Context_Factory();
    
    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " Method. File: " << __FILE__ << ", Line: " << __LINE__;
}


/******************************************/
/*          Create an Instance            */
/******************************************/
A_Render_Driver_Context_Base::ptr_t A_Render_Driver_Context_Factory::Create_Instance()
{
    // Make sure the factory exists
    if( Is_Initialized() == false ){
        BOOST_LOG_TRIVIAL(error) << "Render-Driver Context Factory is null.";
        return nullptr;
    }

    // Get the context factory
    A_Render_Driver_Context_Factory& context_factory = Get_Factory_Instance();
    
    // Set the min content row
    int min_content_row = 2;
    int min_content_col = 1;

    // Return new instance
    if( context_factory.m_conn_type == CORE::ConnectionType::SOCKET ){
        return std::make_shared<A_Render_Driver_Context_ASCII>( context_factory.m_cli_title,
                                                                context_factory.m_window_rows,
                                                                context_factory.m_window_cols,
                                                                min_content_row,
                                                                min_content_col,
                                                                context_factory.m_redirect_stdout,
                                                                context_factory.m_redirect_stderr );
    }

    else{
        BOOST_LOG_TRIVIAL(error) << "Unknown ConnectionType value (" << CORE::ConnectionTypeToString(context_factory.m_conn_type) << "). File: " << __FILE__ << ", Class: " << context_factory.m_class_name << ", Method: " << __func__ << ", Line: " << __LINE__;
        return nullptr;
    }

    return nullptr;
}


/**********************************/
/*          Constructor           */
/**********************************/
A_Render_Driver_Context_Factory::A_Render_Driver_Context_Factory()
  : m_class_name("A_Render_Driver_Context_Factory"),
    m_conn_type(CORE::ConnectionType::UNKNOWN),
    m_cli_title(""),
    m_window_rows(-1),
    m_window_cols(-1),
    m_redirect_stdout(false),
    m_redirect_stderr(false),
    m_is_initialized(false)
{
}


} // End of RENDER Namespace
} // End of CLI    Namespace

