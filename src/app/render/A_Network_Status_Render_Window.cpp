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


/****************************************/
/*          Get the Buffer Data         */
/****************************************/
std::vector<std::string>& A_Network_Status_Render_Window::Get_Buffer_Data()
{
    // Print the main content
    Print_Main_Content();

    // Return the buffer table
    return m_buffer_data;
}


/*******************************************/
/*         Print the Main Content          */
/*******************************************/
void A_Network_Status_Render_Window::Print_Main_Content()
{
    // Compute the rendering bounds
    int max_col = m_render_driver->Get_Window_Cols()-3;
    int max_row = m_render_driver->Get_Window_Rows()-4;
    int min_col = m_render_driver->Get_Min_Content_Col();
    int min_row = m_render_driver->Get_Min_Content_Row();

    // Compute the width
    int width  = max_col - min_col;
    int height = max_row - min_row;
    int sum = 0;


    // Build the Table Widths and Titles
    std::vector<int> table_widths;
    std::vector<std::string> titles;
    table_widths.push_back(25); sum += 25;  titles.push_back("Asset Name");
    table_widths.push_back(25); sum += 25;  titles.push_back("Asset Address");
    table_widths.push_back(25); sum += 25;  titles.push_back("Status");
    table_widths.push_back(width - sum);    titles.push_back("Last Scan");

    // Build the network print table
    m_network_print_table = std::make_shared<CLI::UTILS::An_ASCII_Print_Table>( titles, table_widths, 
                                                                                CLI::UTILS::An_ASCII_Print_Table_Config(false,false));
    
    // Get the network asset list
    std::vector<Network_Asset> assets = m_state_manager.Get_Network_Scanner()->Get_Network_Assets();
    
    // Iterate over assets
    for( size_t i=0; i<assets.size(); i++ )
    {
        // Add the name
        m_network_print_table->Add_Entry( i, 0, " " + assets[i].Get_Name() );
    
        // Add the address
        m_network_print_table->Add_Entry( i, 1, " " + assets[i].Get_Address() );

        // Add the status
        m_network_print_table->Add_Entry( i, 2, " " + assets[i].Get_Status_String() );

        // Add the timestamp
        m_network_print_table->Add_Entry( i, 3, " " + assets[i].Get_Last_Scan_Time_String() );
    }
    
    // Print
    m_network_print_table->Print_Table( m_buffer_data, min_row, max_row, min_col );
    
}

