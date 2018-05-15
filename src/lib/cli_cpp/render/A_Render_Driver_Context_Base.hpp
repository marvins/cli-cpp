/**
 * @file    A_Render_Driver_Context_Base.hpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#ifndef __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_BASE_HPP__
#define __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_BASE_HPP__

// C++ Standard Libraries
#include <memory>
#include <string>

// CLI Libraries
#include "../cmd/A_Command_Result.hpp"


namespace CLI{
namespace RENDER{


/**
 * @brief Render-Driver Context Configuration
 */
class Render_Driver_Config_Base
{
    public:
        
        /// Pointer Type
        typedef std::shared_ptr<Render_Driver_Config_Base> ptr_t;
        
        /**
         * @brief Constructor
         */
        Render_Driver_Config_Base( const std::string& cli_title,
                                   bool               redirect_stdout,
                                   bool               redirect_stderr );
        
        
        /**
         * @brief Get the CLI Title
         */
        inline std::string Get_CLI_Title()const{
            return m_cli_title;
        }
        
        
        /**
         * @brief Flag if we are redirecting stdout
         */
        inline bool Get_Redirect_Stdout_Flag()const{
            return m_redirect_stdout;
        }
        
        
        /**
         * @brief Flag if we are redirecting stderr
         */
        inline bool Get_Redirect_Stderr_Flag()const{
            return m_redirect_stderr;
        }
        
        
        /**
         * @brief Print to Log String
         */
        virtual std::string To_Log_String( int indent )const;
        
    private:
        
        /// Class Name
        std::string m_class_name;
        
        /// CLI Title
        std::string m_cli_title;
        
        /// Redirect stdout
        bool m_redirect_stdout;
        
        /// Redirect stderr
        bool m_redirect_stderr;
};

/**
 * @class A_Render_Driver_Context_Base
*/
class A_Render_Driver_Context_Base{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Render_Driver_Context_Base> ptr_t;

        /**
         * @brief Constructor
        */
        A_Render_Driver_Context_Base( const Render_Driver_Config_Base::ptr_t config );
        

        /**
         * @brief Destructor
        */
        virtual ~A_Render_Driver_Context_Base();
        
        
        /**
         * @brief Command the system to wait on the input command response.
         */
        void Set_Waiting_Command_Response( const CMD::A_Command_Result::ptr_t response );


        /**
         * @brief Get the waiting status
         *
         * @return True if waiting on command result response.
         */
        bool Check_Waiting_Command_Response();


        /**
         * @brief Set the CLI Window Size
         *
         * @param[in] rows Number of Rows 
         * @param[in] cols Number of Columns
         */
        virtual void Set_CLI_Window_Size( int rows,
                                          int cols ) = 0;


        /**
         * @brief Set the CLI Min Content Bounds
         *
         * @param[in] row Min row for printing data.
         * @param[in] col Min column for printing data.
        */
        virtual void Set_CLI_Window_Min_Content_Bounds( int row,
                                                        int col ) = 0;
        
        
        /**
         * @brief Get the CLI Title
         */
        virtual std::string Get_CLI_Title()const = 0;
        
        
        /**
         * @brief Get the number of rows.
         * 
         * @return Window rows.
        */
        virtual int Get_Window_Rows()const = 0;


        /**
         * @brief Get the number of columns.
         *
         * @return Window columns.
        */
        virtual int Get_Window_Cols()const = 0;


        /**
         * @brief Get the min content row.
         */
        virtual int Get_Min_Content_Row()const = 0;


        /**
         * @brief Get the min content column.
        */
        virtual int Get_Min_Content_Col()const = 0;
        
        
        /**
         * @brief Flag if we are redirecting stdout
         */
        inline bool Get_Redirect_Stdout_Flag()const{
            return m_redirect_stdout;
        }
        
        
        /**
         * @brief Flag if we are redirecting stderr
         */
        inline bool Get_Redirect_Stderr_Flag()const{
            return m_redirect_stderr;
        }


    private:

        /// Class Name
        std::string m_class_name;
    
        /// Configuration
        Render_Driver_Config_Base::ptr_t m_config;
        
        /// Waiting Response
        bool m_waiting_command_response;
        
        /// Waiting command
        CMD::A_Command_Result::ptr_t m_waiting_command_response_value;
        
        /// Redirect STDERR,STDOUT
        bool m_redirect_stdout;
        bool m_redirect_stderr;

}; // End of A_Render_Driver_Context_Base Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
