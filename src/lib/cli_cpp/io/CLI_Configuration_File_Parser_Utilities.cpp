/**
 * @file    CLI_Configuration_File_Parser_Utilities.cpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#include "CLI_Configuration_File_Parser_Utilities.hpp"

namespace CLI{
namespace IO{
namespace CONFIG{
namespace XML{


/**************************************************************/
/*          Load the Event Manager XML Config Node            */
/**************************************************************/
EVT::Event_Manager_Config  Load_Event_Manager_Config_XML_Node( pugi::xml_node& event_node )
{
    // Make sure the node exists
    if( event_node == pugi::xml_node() ){
        throw std::runtime_error("event-manager node does not exist.");
    }

    // Make sure the name is right
    if( std::string(event_node.name()) != "event-manager" ){
        throw std::runtime_error("Expected event-manager node, but got " + std::string(event_node.name()) + " instead.");
    }

    ///////////////////////////////////////////////
    //    Get the event queue size
    pugi::xml_node event_queue_max_cap_node = event_node.child("event-queue-max-capacity");
    if( event_queue_max_cap_node == pugi::xml_node() ){
        throw std::runtime_error("event-queue-max-capacity node was not found.");
    }
    int event_queue_max_cap = event_queue_max_cap_node.attribute("value").as_int(-1);
    if( event_queue_max_cap <= 0 ){
        throw std::runtime_error("event-queue-max-capacity @value cannot be less than 1.");
    }
    
    ///////////////////////////////////////////////
    //    Get the work queue size
    pugi::xml_node event_work_queue_node = event_node.child("work-queue-thread-count");
    if( event_work_queue_node == pugi::xml_node() ){
        throw std::runtime_error("work-queue-thread-count node was not found.");
    }
    int thread_count = event_work_queue_node.attribute("value").as_int(-1);
    if( thread_count < 2 ){
        throw std::runtime_error("work-queue-thread-count @value cannot be less than 2.");
    }


    // Create the return object
    return EVT::Event_Manager_Config( event_queue_max_cap,
                                      thread_count );

}


} // End of XML    Namespace
} // End of CONFIG Namespace
} // End of IO     Namespace
} // End of CLI    Namespace

