/**
 * @file    A_Render_Manager_ASCII.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __CLI_A_CONSOLE_RENDER_MANAGER_ASCII_HPP__
#define __CLI_A_CONSOLE_RENDER_MANAGER_ASCII_HPP__

// C++ Standard Libraries
#include <deque>
#include <memory>
#include <string>

// CLI Libraries
#include "A_Render_Driver_Context_ASCII.hpp"
#include "A_Render_Manager_Base.hpp"
#include "A_Render_State.hpp"
#include "ascii/An_ASCII_Help_Menu.hpp"
#include "ascii/An_ASCII_History_Window.hpp"
#include "../cmd/A_Command_History.hpp"
#include "../utility/An_ASCII_Print_Table.hpp"


namespace CLI{
namespace RENDER{

/**
 * @class A_Render_Manager_ASCII
 */
class A_Render_Manager_ASCII : public A_Render_Manager_Base {

    public:

        
        /// Pointer Type
        typedef std::shared_ptr<A_Render_Manager_ASCII> ptr_t;
        
        
        /**
         * @brief Constructor
         */
        A_Render_Manager_ASCII( A_Render_Driver_Context_Base::ptr_t context );
        

        /**
         * @brief Constructor given width and size
         *
         * @param[in] window_rows Number of window rows.
         * @param[in] window_cols Number of window columns.
         */
        A_Render_Manager_ASCII( const int& window_rows,
                                const int& window_cols );
        
        /**
         * @brief Initialize
        */
        virtual void Initialize();


        /** 
         * @brief Finalize
        */
        virtual void Finalize();


        /**
         * @brief Refresh the Screen.
         */
        virtual void Refresh();
        

        /**
         * @brief Get the render state.
         *
         * @return Render state.
         */
        inline virtual A_Render_State::ptr_t Get_Render_State()const{
            return m_render_state;
        }


        /**
         * @brief Get the buffer.
         *
         * @return Console buffer.
         */
        std::vector<std::string>& Get_Console_Buffer();
        
        
        /**
         * @brief Update the rendering driver context.
         *
         * @param[in] driver_context Rendering driver to register.
         */
        inline virtual void Update_Render_Driver_Context( A_Render_Driver_Context_Base::ptr_t driver_context )
        {
            m_render_driver_context = std::dynamic_pointer_cast<A_Render_Driver_Context_ASCII>( driver_context );
        }
        
        
    protected:
        
        /**
         * @brief Print the header
         */
        virtual void Print_Header( std::vector<std::string>& print_buffer );
        

        /**
         * @brief Print Main Context.
         */
        virtual void Print_Main_Content();


        /**
         * @brief Print Footer
         */
        virtual void Print_Footer();


        /**
         * @brief Print CLI
         *
         * @param[in] print_buffer Buffer to post cli contents to.
         */
        virtual void Print_CLI( std::vector<std::string>& print_buffer );


    private:

        /**
         * @brief Build the console buffer.
         */
        void Build_Console_Buffer();


        /**
         * @brief Build the help main buffer
         */
        void Build_Help_General_Buffer();


        /// Class Name
        std::string m_class_name;


        /// Render State
        A_Render_State::ptr_t m_render_state;


        /// Console Buffer
        std::vector<std::string> m_console_buffer;
        
        /// Render Context
        A_Render_Driver_Context_ASCII::ptr_t m_render_driver_context;
        
        /// ASCII History Window
        ASCII::An_ASCII_History_Window::ptr_t m_history_window;

        /// ASCII Help Menu
        ASCII::An_ASCII_Help_Menu::ptr_t m_help_menu;

        /// Window Size
        int m_window_rows;
        int m_window_cols;

}; // End of A_Render_Manager_ASCII Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
