/**
 * @file    A_Command_Result.hpp
 * @author  Marvin Smith
 * @date    5/19/2015
 */
#ifndef __CLI_CMD_A_CLI_COMMAND_RESULT_HPP__
#define __CLI_CMD_A_CLI_COMMAND_RESULT_HPP__

// CLI Libraries
#include "A_Command.hpp"
#include "A_CLI_Command.hpp"
#include "CommandParseStatus.hpp"
#include "../utility/String_Utilities.hpp"

// C++ Standard Libraries
#include <condition_variable>
#include <memory>
#include <mutex>
#include <string>
#include <type_traits>

namespace CLI{
namespace CMD{

/**
 * @class A_Command_Result
 */
class A_Command_Result{

    public:
        
        /// Pointer Type
        typedef std::shared_ptr<A_Command_Result> ptr_t;
        

        /**
         * @brief Constructor
        */
        A_Command_Result();


        /**
         * @brief Constructor
         *
         * @param[in] instance_id   Instance of client who issued command.
         * @param[in] parse_status  Parsing operation status.
         * @param[in] command       Command that was executed.
         */
        A_Command_Result( const int&                  instance_id,
                          CommandParseStatus const&   parse_status,
                          A_Command const&            command,
                          const bool&                 refresh_screen_on_response = false );
       

        /**
         * @brief Constructor
         *
         * @param[in] instance_id      Instance of client who issues command.
         * @param[in] parse_status     Parsing operation status.
         * @param[in] command          Command that was executed.
         * @param[in] argument_values  List of arguments provided to the command.
         */
        A_Command_Result( const int&                      instance_id,
                          CommandParseStatus const&       parse_status,
                          A_Command const&                command,
                          std::vector<std::string> const& argument_values,
                          const bool&                     refresh_screen_on_response = false );
       

        /**
         * @brief Constructor 
         *
         * @param[in] argument_values  List of arguments provided to the command.
         */
        A_Command_Result( std::string const&                request_id,
                          std::vector<std::string> const&   argument_values,
                          const bool&                       refresh_screen_on_response = false );

    
        /**
         * @brief Get the Instance ID.
         *
         * @return Instance-ID of the client.
        */
        inline int Get_Instance_ID()const{
            return m_instance_id;
        }

        
        /**
         * @brief Get the Request ID.
         * 
         * @return Request ID for the request
         */
        inline std::string  Get_Request_ID()const {
            return m_request_id;
        }
        
        
        /**
         * @brief Get the Parsing Status.
         *
         * @return Parse status.
         */
        inline CommandParseStatus Get_Parse_Status()const{
            return m_parse_status;
        }


        /**
         * @brief Get the Parsing Status
        */
        std::string Get_Parse_Status_String()const;


        /**
         * @brief Get the command.
         *
         * @return Command.
         */
        inline A_Command Get_Command()const{
            return m_command;
        }

    
        /**
         * @brief Process Command Results
         *
         * @param[in] instance_id Instance of client who issue command.
         * @param[in] command     Command that was executed.
         * @param[in] arguments   List of arguments to check for validity.
         *
         * @return Result of the operation.
         */
        static A_Command_Result::ptr_t  Process_Arguments( const int&                       instance_id,
                                                           const A_Command&                 command,
                                                           const std::vector<std::string>&  arguments );


        /**
         * @brief Process CLI Command Results.
         *
         * @param[in] instance_id  Instance of Client who issued command.
         * @param[in] command      CLI Command that was executed.
         * @param[in] arguments    List of arguments to check for validity.
         *
         * @return Result of the operation.
        */
        static A_Command_Result::ptr_t  Process_CLI_Arguments( const int&                       instance_id,
                                                               const A_CLI_Command&             command,
                                                               const std::vector<std::string>&  arguments );

        /**
         * @brief Print to a debug string.
         */
        std::string To_Debug_String( const int& offset = 0 )const;

        
        /**
         * @brief Set the response from the system.
         *
         * @param[in] response Response to set.
         */
        void Set_System_Response( const std::string& response );

        
        /**
         * @brief Get the system response.
         *
         * @return system response value
         */
        inline std::string Get_System_Response()const{
            return m_system_response_value;
        }


        /**
         * @brief Check system response.
         *
         * @return True if received, false otherwise.
         */
        inline bool Check_System_Response()const{
            return m_system_response_set;
        }

        
        inline void Set_Response_Timeout_Msec(int       timeout_msec) {
            m_response_timeout_msec = timeout_msec;
        }

        
        /**
         * @brief Wait For a Response
         */
        void        Wait_For_Response();
        

        /**
         * @brief Get argument value count.
         *
         * @return number of arguments
        */
        inline int Get_Argument_Value_Count()const{
            return m_argument_values.size();
        }


        /**
         * @brief Get the argument value list.
         *
         * @returen Argument value list.
        */
        inline std::vector<std::string> Get_Argument_Value_List()const{
            return m_argument_values;
        }
        

        /**
         * @brief Get argument value.
         *
         * @param[in] idx argument index.
         *
         * @return result Result value.
         */
        template <typename TP>
        typename std::enable_if<std::is_same<TP,std::string>::value,std::string>::type
        Get_Argument_Value( const int& idx )const
        {
            // Check if we need to use the default
            if( (int)m_argument_values.size() <= idx ){
                return m_command.Get_Command_Argument(idx).Get_Default_Value();
            }
            
            // Otherwise, return the actual argument
            return m_argument_values[idx];
        }

       
        /**
         * @brief Get argument value.
         *
         * @param[in] idx argument index.
         *
         * @return result Result value.
         */
        template <typename TP>
        typename std::enable_if<std::is_arithmetic<TP>::value,TP>::type
        Get_Argument_Value( const int& idx )const
        {
            // Check if we need to use the default
            if( (int)m_argument_values.size() <= idx ){
                return UTILS::str2num<TP>( m_command.Get_Command_Argument(idx).Get_Default_Value());
            }
            
            // Otherwise, return the actual argument
            return UTILS::str2num<TP>( m_argument_values[idx] );
        }



    private:


        A_Command_Result( A_Command_Result const& ) = delete;

        void operator = ( A_Command_Result const& ) = delete;

        /// Class Name
        std::string m_class_name;

    
        /// Instance ID
        int m_instance_id;

        /// Status
        CommandParseStatus m_parse_status;

        /// Command Found
        A_Command m_command;

        /// Argument Values
        std::vector<std::string> m_argument_values;

        /// Request ID
        std::string     m_request_id;
        
        /// System response
        bool m_system_response_set = false;

        /// Response 
        std::string m_system_response_value;
        
        /// Flag if we want to refresh screen on set system response
        bool m_refresh_screen_on_response = false;
        
        /// Mutex for protecting response
        std::mutex                  m_response_mutex;

        /// Condition Variable for announcing changes to response
        std::condition_variable     m_response_event;
        
        /// Response wait timeout in milliseconds
        int                         m_response_timeout_msec = 2000000000;
        
}; // End of A_Command_Result Class

} // End of CMD Namespace
} // End of CLI Namespace

#endif
