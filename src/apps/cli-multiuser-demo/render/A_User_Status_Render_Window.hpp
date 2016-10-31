/**
 * @file    A_User_Status_Render_Window.hpp
 * @author  Marvin Smith
 * @date    10/26/2016
*/
#ifndef __CLI_CPP_APPS_MULTIUSER_RENDER_A_USER_STATUS_RENDER_WINDOW_HPP__
#define __CLI_CPP_APPS_MULTIUSER_RENDER_A_USER_STATUS_RENDER_WINDOW_HPP__

// CLI Libraries
#include <cli_cpp/render/ascii/An_ASCII_Render_Window_Base.hpp>
#include <cli_cpp/utility/An_ASCII_Print_Table.hpp>


// Demo Libraries
#include "../core/State_Manager.hpp"


/**
 * @class A_User_Status_Render_Window
 *
 * This is a simple custom rendering window which will print the current status of values 
 * within the application's state manager.  This is an example of how you can extend the 
 * rendering manager within CLI-CPP to provide custom screens and windows.
*/
class A_User_Status_Render_Window : public CLI::RENDER::An_ASCII_Render_Window_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_User_Status_Render_Window> ptr_t;
        

        /**
         * @brief Construct the network status window.
         *
         * @param[in] state_manager State manager to update the scene from
         */
        A_User_Status_Render_Window( State_Manager&  state_manager );
        

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
            return "User Status Window";
        }
        
        
        /**
         * @brief Check if a Command is supported for enabling window.
         */
        virtual bool Is_Trigger_Command( const CLI::CMD::A_Command& command )const;
   

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

        /// User Table Info
        std::vector<std::string> m_active_table_labels;
        std::vector<int>         m_active_table_widths;

        /// Event Table Info
        std::vector<std::string> m_event_table_labels;
        std::vector<int>         m_event_table_widths;

        
}; // End of A_User_Status_Render_Window_Base



#endif
