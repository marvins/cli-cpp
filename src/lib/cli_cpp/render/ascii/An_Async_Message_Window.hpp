/**
 * @file    An_Async_Message_Window.hpp
 * @author  Marvin Smith
 * @date    4/11/2017
 */
#pragma once

// CLI Libraries
#include "An_ASCII_Render_Window_Base.hpp"
#include "../../utility/An_ASCII_Print_Table.hpp"

namespace CLI{
namespace RENDER{

/**
 * @class An_Async_Message_Window
*/
class An_Async_Message_Window : public An_ASCII_Render_Window_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<An_Async_Message_Window> ptr_t;
        
        /**
         * @brief Constructor
        */
        An_Async_Message_Window( A_Render_Driver_Context_ASCII::ptr_t render_driver );

    
        /**
         * @brief Retrieve the buffer data
        */
        virtual std::vector<std::string>& Get_Buffer_Data();
        

        /**
         * @brief Get the Window Title.
         *
         * @return Window Title.
        */
        inline virtual std::string Get_Window_Title()const{
            return "Async Message History Window";
        }

        
        /**
         * @brief Send Asynchronous Message to Window.
         *
         * @param[in] topic_name
         * @param[in] message
        */
        virtual void Send_Asynchronous_Message( const std::string& topic_name,
                                                const std::string& message );

        
    protected:
        
        /**
         * @brief Print the Main Content.
         */
        void Print_Main_Content();


        /**
         * @brief Initialize the Print Table
         */
        void Initialize_Print_Table();


    private:
        
        /// Class Name
        std::string m_class_name;

        /// Shortcut print line
        std::string m_shortcut_print_line;

        /// List of Async Messages
        std::vector<std::tuple<std::string,std::string,std::string>> m_msg_history;

        /// Print Table
        UTILS::An_ASCII_Print_Table::ptr_t m_print_table;

}; // End of A_Main_Window Class

} // End of RENDER Namespace
} // End of CLI    Namespace


