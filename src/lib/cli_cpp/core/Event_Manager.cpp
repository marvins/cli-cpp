/**
 * @file    Event_Manager.cpp
 * @author  Marvin Smith
 * @date    5/30/2015
 */
#include "Event_Manager.hpp"

// C++ Standard Libraries
#include <iostream>
#include <unistd.h>


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
    // Get an instance
    Event_Manager::ptr_t inst = Instance_Of();

    // Iterate over event managers
    for( size_t i=0; i<inst->m_event_handlers.size(); i++ ){
        inst->m_event_handlers[i]->Process_Event(event);
    }

}

} // End of CORE Namespace
} // End of CLI  Namespace
