/**
 * @file    A_User_Status_Render_Window.cpp
 * @author  Marvin Smith
 * @date    7/4/2015
*/
#include "A_User_Status_Render_Window.hpp"


/**************************************/
/*            Constructor             */
/**************************************/
A_User_Status_Render_Window::A_User_Status_Render_Window( State_Manager& state_manager )
  : An_ASCII_Render_Window_Base(),
    m_class_name("A_User_Status_Render_Window"),
    m_window_title("User Status Window"),
    m_state_manager(state_manager)
{
    // Create Table Data
    m_active_table_widths.clear();
    m_active_table_labels.clear();

    m_active_table_labels.push_back("Session-ID");
    m_active_table_widths.push_back(10);
    m_active_table_labels.push_back("Connection-Type");
    m_active_table_widths.push_back(20);
    m_active_table_labels.push_back("Information");
    m_active_table_widths.push_back(50);


    m_event_table_widths.clear();
    m_event_table_labels.clear();

    m_event_table_labels.push_back("Session-ID");
    m_event_table_widths.push_back(15);
    
    m_event_table_labels.push_back("Event-Type");
    m_event_table_widths.push_back(12);
    
    m_event_table_labels.push_back("Message");
    m_event_table_widths.push_back(40);
}


/*************************************************/
/*             Update Buffer Data                */
/*************************************************/
void A_User_Status_Render_Window::Update_Buffer_Data()
{

    // Call on parent method
    An_ASCII_Render_Window_Base::Update_Buffer_Data();


}


/****************************************/
/*          Get the Buffer Data         */
/****************************************/
std::vector<std::string>& A_User_Status_Render_Window::Get_Buffer_Data()
{
    // Print the main content
    Print_Main_Content();

    // Return the buffer table
    return m_buffer_data;
}


/*********************************************************/
/*          Authorize a default trigger command          */
/*********************************************************/
bool A_User_Status_Render_Window::Is_Trigger_Command( const CLI::CMD::A_Command& command )const
{
    // Log Entry
    
    // Misc Variables
    bool result = false;

    // Check command name
    if( command.Get_Name() == "user-status" )
    {
        result = true;
    }

    return result;
}
        

/*******************************************/
/*         Print the Main Content          */
/*******************************************/
void A_User_Status_Render_Window::Print_Main_Content()
{
    // Compute the rendering bounds
    int max_col = m_render_driver->Get_Window_Cols()-3;
    int max_row = m_render_driver->Get_Window_Rows()-4;
    int min_col = m_render_driver->Get_Min_Content_Col();
    int min_row = m_render_driver->Get_Min_Content_Row();

    // Compute the width
    int width  = max_col - min_col;

    
    /// CLI Print Table Utility
    CLI::UTILS::An_ASCII_Print_Table active_print_table( m_active_table_labels,
                                                         m_active_table_widths );
        
    
    /// CLI Event Table Utility
    CLI::UTILS::An_ASCII_Print_Table event_print_table( m_event_table_labels,
                                                        m_event_table_widths );


    // Build the Active List
    int counter = 0;
    auto session_list = m_state_manager.Get_CLI_Manager()->Get_Active_Session_List();
    for( auto session : session_list )
    {
        
        // Add to table
        active_print_table.Add_Entry( counter, 0, " " + std::to_string(session.Get_Session_ID()) );
        active_print_table.Add_Entry( counter, 1, " " + CLI::CORE::ConnectionTypeToString(session.Get_Connection_Type()));
        
        // Increment Counter
        counter++;
    }

    
    // Build the Event List
    counter = 0;
    auto event_list = m_state_manager.Get_Session_Event_List();
    for( auto event : event_list )
    {
        event_print_table.Add_Entry( counter, 0, " " + std::to_string(event.Get_Session().Get_Session_ID()));
        event_print_table.Add_Entry( counter, 2, " " + event.Get_Message());
        
        // Increment Counter
        counter++;
    }

    // Print
    active_print_table.Print_Table( m_buffer_data, min_row, max_row/2-1, min_col );
    
    event_print_table.Print_Table( m_buffer_data, max_row/2+1, max_row, min_col );

}

