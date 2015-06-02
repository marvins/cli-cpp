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
        */
        A_Render_Driver_Context_ASCII( const std::string&  cli_title,
                                       const int&          window_rows,   
                                       const int&          window_cols,
                                       const int&          min_content_row,
                                       const int&          min_content_col);

    
        /**
         * @brief Get the number of rows.
         * 
         * @return Window rows.
        */
        inline int Get_Window_Rows()const{
            return m_window_rows;
        }


        /**
         * @brief Get the number of columns.
         *
         * @return Window columns.
        */
        inline int Get_Window_Cols()const{
            return m_window_cols;
        }


        /**
         * @brief Get the min content row.
         */
        inline int Get_Min_Content_Row()const{
            return m_min_content_row;
        }


        /**
         * @brief Get the min content column.
        */
        inline int Get_Min_Content_Col()const{
            return m_min_content_col;
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

}; // End of A_Render_Driver_Context_NCurses

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif

