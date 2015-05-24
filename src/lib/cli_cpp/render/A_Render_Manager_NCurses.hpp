/**
 * @file    A_Render_Manager_NCurses.hpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#ifndef __CLI_CPP_CLI_A_RENDER_MANAGER_NCURSES_HPP__
#define __CLI_CPP_CLI_A_RENDER_MANAGER_NCURSES_HPP__


// C++ Standard Libraries
#include <memory>
#include <string>


// CLI Libraries
#include "A_Render_Driver_Context_Base.hpp"
#include "A_Render_Driver_Context_NCurses.hpp"
#include "A_Render_Manager_Base.hpp"
#include "A_Render_State.hpp"
#include "../thirdparty/ncurses/An_NCurses_Table.hpp"
#include "../thirdparty/ncurses/NCurses_Utilities.hpp"


namespace CLI{
namespace RENDER{


/**
 * @class A_Render_Manager_NCurses
 */
class A_Render_Manager_NCurses : public A_Render_Manager_Base 
{

    public:

        /// Pointer Type
        typedef std::shared_ptr<A_Render_Manager_NCurses> ptr_t;
        
        /**
         * @brief Constructor
         */
        A_Render_Manager_NCurses( A_Render_Driver_Context_Base::ptr_t context );
        
        
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
        void Refresh();
        

        /**
         * @brief Wait on keyboard input.
         *
         * @return character pressed.
         */
        virtual int Wait_Keyboard_Input();


        /**
         * @brief Get the render state
         */
        inline virtual A_Render_State::ptr_t Get_Render_State()const{
            return m_render_state;
        }
        
        
        /**
         * @brief Append Command To History.
         *
         * @param[in] command_string String representing what the user typed in.
         * @param[in] command_result Parsing and evaluation result.
         */
        virtual void Add_Command_History( const std::string&            command_string,
                                          const CMD::A_Command_Result&  command_result );

        
        /**
         * @brief Update the rendering driver context.
         *
         * @param[in] driver_context Rendering driver to register.
         */
        inline virtual void Update_Render_Driver_Context( A_Render_Driver_Context_Base::ptr_t driver_context )
        {
            m_render_driver_context = std::dynamic_pointer_cast<A_Render_Driver_Context_NCurses>( driver_context );
        }


    protected:
        
        /**
         * @brief Print the header
         */
        void Print_Header();
        

        /**
         * @brief Print Main Context.
         */
        void Print_Main_Content();


        /**
         * @brief Print Help Content
         */
        void Print_Help_Content();


        /**
         * @brief Print CLI
         */
        void Print_CLI();

    private:
        
        /**
         * @brief Initialize the NCurses Tables
         */
         void Initialize_Command_Print_Tables();


        /// Class Name
        std::string m_class_name;
        
        /// Render Context
        A_Render_Driver_Context_NCurses::ptr_t m_render_driver_context;

        /// Render State
        A_Render_State::ptr_t m_render_state;
        
        /// NCurses Tables
        NCURSES::An_NCurses_Table::ptr_t m_cli_command_print_table;
        NCURSES::An_NCurses_Table::ptr_t m_command_print_table;

        /// History Print Table
        NCURSES::An_NCurses_Table::ptr_t m_history_print_table;

        /// History Print Table configuration
        NCURSES::An_NCurses_Table_Configuration m_history_print_table_config;

}; // End of A_Render_Manager_NCurses Class

} // End of RENDER Namespace
} // End of CLI    Namespace


#endif
