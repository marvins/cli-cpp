/**
 * @file    A_Network_Status_Render_Window.hpp
 * @author  Marvin Smith
 * @date    7/2/2015
*/
#ifndef __CLI_CPP_APP_RENDER_A_NETWORK_STATUS_RENDER_WINDOW_HPP__
#define __CLI_CPP_APP_RENDER_A_NETWORK_STATUS_RENDER_WINDOW_HPP__

// CLI Libraries
#include <cli_cpp/render/ascii/An_ASCII_Render_Window_Base.hpp>


// Demo Libraries
#include "../core/State_Manager.hpp"


/**
 * @class A_Network_Status_Render_Window
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
         * @brief Get the Window Title
        */
        inline virtual std::string  Get_Window_Title()const{
            return "Network Status Window";
        }
    

    private:

        /// Class Name
        std::string m_class_name;

        
        /// Window Name
        std::string m_window_title;


        /// State Manager
        State_Manager& m_state_manager;

}; // End of A_Network_Status_Render_Window_Base



#endif
