/**
 * @file    A_Network_Status_Render_Window.cpp
 * @author  Marvin Smith
 * @date    7/4/2015
*/
#include "A_Network_Status_Render_Window.hpp"


/**************************************/
/*            Constructor             */
/**************************************/
A_Network_Status_Render_Window::A_Network_Status_Render_Window( State_Manager& state_manager )
  : An_ASCII_Render_Window_Base(),
    m_class_name("A_Network_Status_Render_Window"),
    m_window_title("Network Status Window"),
    m_state_manager(state_manager)
{

}


/*************************************************/
/*             Update Buffer Data                */
/*************************************************/
void A_Network_Status_Render_Window::Update_Buffer_Data()
{

    // Call on parent method
    An_ASCII_Render_Window_Base::Update_Buffer_Data();


}

