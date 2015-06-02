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
#include <vector>

// CLI Libraries
#include "A_Render_Driver_Context_ASCII.hpp"
#include "A_Render_Manager_Base.hpp"
#include "A_Render_State.hpp"
#include "ascii/An_ASCII_Render_Window_Base.hpp"
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
        A_Render_Manager_ASCII( A_Render_Driver_Context_Base::ptr_t context,
                                CMD::A_Command_Parser::ptr_t        command_parser );
        

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
        
        
        /**
         * @brief Command the system to wait on the input command response.
         */
        virtual void Set_Waiting_Command_Response( const CMD::A_Command_Result::ptr_t response );


        /**
         * @brief Get the waiting status
         *
         * @return True if waiting on command result response.
         */
        virtual bool Check_Waiting_Command_Response();

        /**
         * @brief Set the Current Window
         */
        inline virtual void Set_Current_Window( const int& window_id ){
            m_current_window = window_id;
        }
    
    protected:
        
        /**
         * @brief Print CLI
         *
         * @param[in] print_buffer Buffer to post cli contents to.
         */
        virtual void Print_CLI( std::vector<std::string>& print_buffer );


    private:

        /// Class Name
        std::string m_class_name;

        
        /// Render Context
        A_Render_Driver_Context_ASCII::ptr_t m_render_driver_context;
        

        /// List of Render Windows
        std::vector<An_ASCII_Render_Window_Base::ptr_t> m_window_list;


        /// Current Window Index
        int m_current_window;

}; // End of A_Render_Manager_ASCII Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
