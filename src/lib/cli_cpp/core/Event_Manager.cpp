/**
 * @file    Event_Manager.cpp
 * @author  Marvin Smith
 * @date    5/30/2015
 */
#include "Event_Manager.hpp"

// C++ Standard Libraries
#include <iostream>
#include <unistd.h>


// CLI Libraries
#include "../utility/Log_Utilities.hpp"

namespace CLI{
namespace CORE{

static std::shared_ptr<Event_Manager> instance = nullptr;

/**************************/
/*      Constructor       */
/**************************/
Event_Manager::Event_Manager()
  : m_class_name("Event_Manager")
{
}


/**************************/
/*       Destructor       */
/**************************/
Event_Manager::~Event_Manager()
{

}


/********************************/
/*          Initialize          */
/********************************/
void Event_Manager::Initialize()
{
    // Check the singleton instance
    if( instance == nullptr ){
        instance = Event_Manager::ptr_t(new Event_Manager());
    }

}


/********************************/
/*          Initialize          */
/********************************/
void Event_Manager::Finalize()
{
    // Check the singleton instance
    if( instance != nullptr ){
        instance = nullptr;
    }

}

/**********************************************/
/*          Get Instance Of Handler           */
/**********************************************/
Event_Manager::ptr_t Event_Manager::Instance_Of()
{
    // Initialize
    Initialize();

    return instance;
}


/***********************************************/
/*         Register the event handler          */
/***********************************************/
void Event_Manager::Register_CLI_Event_Handler( A_CLI_Event_Handler_Base::ptr_t handler )
{
    // Get an instance
    Event_Manager::ptr_t inst = Instance_Of();

    // add the handler to the list
    inst->m_event_handlers.push_back(handler);
}


/*****************************************/
/*           Process an Event            */
/*****************************************/
void Event_Manager::Process_Event( const int& event )
{

    // Log Entry
    BOOST_LOG_TRIVIAL(trace) << "Start of " << __func__ << " method. Event ID: " << event << ",  File: " << __FILE__ << ", Line: " << __LINE__;
    
    
    // Get an instance
    Event_Manager::ptr_t inst = Instance_Of();

    // Iterate over event managers
    for( size_t i=0; i<inst->m_event_handlers.size(); i++ ){

        // Check if null
        if( inst->m_event_handlers[i] == nullptr ){
            BOOST_LOG_TRIVIAL(warning) << "Event handler at position " << i << " is currently nullptr. Method: " << __func__ << ", File: " << __FILE__ << ", Line: " << __LINE__;
        }

        // Check if supported
        else if( inst->m_event_handlers[i]->Is_Supported_Event( event ) == true ){
            inst->m_event_handlers[i]->Process_Event(event);
        }

    }

    // Log Exit
    BOOST_LOG_TRIVIAL(trace) << "End of " << __func__ << " method. Event ID: " << event << ", File: " << __FILE__ << ", Line: " << __LINE__;
}

} // End of CORE Namespace
} // End of CLI  Namespace
