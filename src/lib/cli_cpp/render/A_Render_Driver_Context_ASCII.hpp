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
         * @param[in] window_rows Number of window rows.
         * @param[in] window_cols Number of window columns.
         * @param[in] min_content_row Minimum row at which content can appear.
         * @param[in] min_content_col Minimum column at which content can appear.
         * @param[in] redirect_stdout Flag if we want to redirect standard output.
         * @param[in] redirect_stderr Flag if we want ot redirect standard error output.
        */
        A_Render_Driver_Context_ASCII( const std::string&  cli_title,
                                       const int&          window_rows,   
                                       const int&          window_cols,
                                       const int&          min_content_row,
                                       const int&          min_content_col,
                                       const bool&         redirect_stdout,
                                       const bool&         redirect_stderr,
                                       const std::chrono::milliseconds& async_tab_refresh_ms );

    
        /**
         * @brief Get the number of rows.
         * 
         * @return Window rows.
        */
        inline virtual int Get_Window_Rows()const{
            return m_window_rows;
        }


        /**
         * @brief Get the number of columns.
         *
         * @return Window columns.
        */
        inline virtual int Get_Window_Cols()const{
            return m_window_cols;
        }


        /**
         * @brief Get the min content row.
         */
        inline virtual int Get_Min_Content_Row()const{
            return m_min_content_row;
        }


        /**
         * @brief Get the min content column.
        */
        inline virtual int Get_Min_Content_Col()const{
            return m_min_content_col;
        }


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
        virtual void Set_CLI_Window_Size( const int& rows,
                                          const int& cols );


        /**
         * @brief Set CLI Window Min Content Bounds
         *
         * @param[in] row Minimum row for data.
         * @param[in] col Minimum column for data.
         */
        virtual void Set_CLI_Window_Min_Content_Bounds( const int& row,
                                                        const int& col );

        
        /**
         * @brief Get the Async Tab Refresh Time in MS
         */
        inline virtual std::chrono::milliseconds Get_Async_Tab_Refresh_Time_MS()const{
            return m_async_tab_refresh_ms;
        }

    private:
        
        /// Class Name 
        std::string m_class_name;

        /// Socket Window Rows
        int m_window_rows;

        /// Window Cols
        int m_window_cols;
        
        /// Min Content Row
        int m_min_content_row;

        /// Min Content Column
        int m_min_content_col;

        /// Async Message Tab Update Time
        std::chrono::milliseconds m_async_tab_refresh_ms;

}; // End of A_Render_Driver_Context_NCurses

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif

