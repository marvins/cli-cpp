/**
 * @file    A_Render_Driver_Context_ASCII.hpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#ifndef __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_ASCII_HPP__
#define __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_ASCII_HPP__

// CLI Libraries
#include "A_Render_Driver_Context_Base.hpp"

// C++ Standard Libraries
#include <memory>
#include <string>


namespace CLI{
namespace RENDER{


/**
 * @brief ASCII Configuration
 */
class Render_Driver_Config_ASCII : public Render_Driver_Config_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<Render_Driver_Config_ASCII> ptr_t;
        
        /**
         * @brief Constructor
         */
        Render_Driver_Config_ASCII( const std::string&         cli_title,
                                    bool                       redirect_stdout,
                                    bool                       redirect_stderr,
                                    int                        window_rows,
                                    int                        window_cols,
                                    int                        min_content_row,
                                    int                        min_content_col,
                                    std::chrono::milliseconds  async_tab_refresh );
        
        
        /**
         * @brief Get the Window Size in Rows
         * @return
         */
        inline int Get_Window_Rows()const{
            return m_window_rows;
        }
        
        /**
         * @brief Get the Window Size in Cols
         */
        inline int Get_Window_Cols()const{
            return m_window_cols;
        }
        
        
        /**
         * @brief Get the Min Content Row
         */
        inline int Get_Min_Content_Row()const{
            return m_min_content_row;
        }
        
        
        /**
         * @brief Get the Min Content Col
         */
        inline int Get_Min_Content_Col()const{
            return m_min_content_col;
        }
        
        
        /**
         * @brief Get the Async Time Refresh
         */
        inline std::chrono::milliseconds Get_Async_Tab_Refresh_Time()const{
            return m_async_tab_refresh;
        }
        
        
        /**
         * @brief Print to Log String
         */
        std::string To_Log_String( int indent )const override;
    
    private:
        
        /// Class Name
        std::string m_class_name;
        
        /// Window Sizes
        int m_window_rows;
        int m_window_cols;
        int m_min_content_row;
        int m_min_content_col;
        
        /// Async Tab Refresh Time
        std::chrono::milliseconds m_async_tab_refresh;
        
};


/**
 * @class A_Render_Driver_Context_ASCII
 *
 * @brief ASCII render driver context.
*/
class A_Render_Driver_Context_ASCII : public A_Render_Driver_Context_Base 
{

    public:

        /// Pointer Type
        typedef std::shared_ptr<A_Render_Driver_Context_ASCII> ptr_t;

        
        /**
         * @brief Constructor
         *
         * @param config
         */
        A_Render_Driver_Context_ASCII( Render_Driver_Config_Base::ptr_t config );


        /**
         * @brief Set CLI Window Size
         *
         * @param[in] rows Number of rows.
         * @param[in] cols Number of columns.
         *
         *  This operation will also reset the Max content bounds
         *  to match the CLI window size to avoid the user going out of
         *  bounds on the CLI window.
         */
        void Set_CLI_Window_Size( int rows,
                                  int cols ) override;


        /**
         * @brief Set CLI Window Min Content Bounds
         *
         * @param[in] row Minimum row for data.
         * @param[in] col Minimum column for data.
         */
        virtual void Set_CLI_Window_Min_Content_Bounds( int row,
                                                        int col ) override;
        
        
        /**
         * @brief Get the CLI Title
         */
        inline std::string Get_CLI_Title()const override{
            return m_cli_title;
        }
        
        
        /**
         * @brief Get the Window Size in Rows
         * @return
         */
        inline int Get_Window_Rows()const override{
            return m_window_rows;
        }
        
        /**
         * @brief Get the Window Size in Cols
         */
        inline int Get_Window_Cols()const override{
            return m_window_cols;
        }
        
        
        /**
         * @brief Get the Min Content Row
         */
        inline int Get_Min_Content_Row()const override{
            return m_min_content_row;
        }
        
        
        /**
         * @brief Get the Min Content Col
         */
        inline int Get_Min_Content_Col()const override{
            return m_min_content_col;
        }
        

    private:
        
        /// Class Name 
        std::string m_class_name;

        /// Configuration
        Render_Driver_Config_ASCII::ptr_t m_config;
        
        // Misc Info
        std::string m_cli_title;
        
        /// Current Window-Sizes
        int m_window_rows;
        int m_window_cols;
        int m_min_content_row;
        int m_min_content_col;

}; // End of A_Render_Driver_Context_NCurses

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif

