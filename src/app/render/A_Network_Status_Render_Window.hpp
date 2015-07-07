/**
 * @file    A_Network_Status_Render_Window.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef __CLI_CPP_APP_RENDER_A_NETWORK_STATUS_RENDER_WINDOW_HPP__
#define __CLI_CPP_APP_RENDER_A_NETWORK_STATUS_RENDER_WINDOW_HPP__

// CLI Libraries
#include <cli_cpp/render/ascii/An_ASCII_Render_Window_Base.hpp>
#include <cli_cpp/utility/An_ASCII_Print_Table.hpp>


// Demo Libraries
#include "../core/State_Manager.hpp"


/**
 * @class A_Network_Status_Render_Window
 *
 * This is a simple custom rendering window which will print the current status of values 
 * within the application's state manager.  This is an example of how you can extend the 
 * rendering manager within CLI-CPP to provide custom screens and windows.
*/
class A_Network_Status_Render_Window : public CLI::RENDER::An_ASCII_Render_Window_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Network_Status_Render_Window> ptr_t;
        

        /**
         * @brief Construct the network status window.
         *
         * @param[in] state_manager State manager to update the scene from
         */
        A_Network_Status_Render_Window( State_Manager&  state_manager );
        

        /**
         * @brief Update the current buffer data.
         *
         * @brief Note that this will do nothing unless implemented.
         */
        virtual void Update_Buffer_Data();
        
        
        /**
         * @brief Retrieve the buffer data
         *
         * @return Buffer data array.
        */
        virtual std::vector<std::string>& Get_Buffer_Data();

        
        /**
         * @brief Get the Window Title
        */
        inline virtual std::string  Get_Window_Title()const{
            return "Network Status Window";
        }
    
    protected:
        
        /**
         * @brief Print the main window content.
         */
        void Print_Main_Content();


    private:

        /// Class Name
        std::string m_class_name;

        
        /// Window Name
        std::string m_window_title;


        /// State Manager
        State_Manager& m_state_manager;
        
        /// CLI Print Table Utility
        CLI::UTILS::An_ASCII_Print_Table::ptr_t  m_network_print_table;

}; // End of A_Network_Status_Render_Window_Base



#endif
