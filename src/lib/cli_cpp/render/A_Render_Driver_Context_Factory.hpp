/**
 * @file    A_Render_Driver_Context_Driver_Factory.hpp
 * @author  Marvin Smith
 * @date    5/22/2015
*/
#ifndef __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_FACTORY_HPP__
#define __CLI_CPP_RENDER_A_RENDER_DRIVER_CONTEXT_FACTORY_HPP__

// C++ Standard Libraries
#include <string>

// CLI Libraries
#include "../core/ConnectionType.hpp"
#include "A_Render_Driver_Context_Base.hpp"

namespace CLI{
namespace RENDER{

/**
 * @class A_Render_Driver_Context_Factory
 *
 * @brief Constructs the proper Render Driver Context object.
 */
class A_Render_Driver_Context_Factory
{
    public:
        
        /**
         * @brief Initialize the context driver.
         *
         * @param[in] conn_type Connection type.
         * @param[in] cli_title Command-Line Interface Title.
         * @param[in] window_rows Window rows.
         * @param[in] window_cols Window columns.
         * @param[in] redirect_stdout Flag if we want to redirect stdout.
         * @param[in] redirect_stderr Flag if we want to redirect stderr.
         *
         * @return Render context.
        */
        static A_Render_Driver_Context_Base::ptr_t Initialize( const CORE::ConnectionType& conn_type,
                                                               const std::string&          cli_title,
                                                               const int&                  window_rows,
                                                               const int&                  window_cols,
                                                               const bool&                 redirect_stdout,
                                                               const bool&                 redirect_stderr );

}; // End of A_Render_Driver_Context_Factory Class

} // End of RENDER Namespace
} // End of CLI    Namespace

#endif
