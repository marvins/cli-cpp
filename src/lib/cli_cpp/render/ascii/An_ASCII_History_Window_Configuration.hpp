/**
 * @file    An_ASCII_History_Window_Configuration.hpp
 * @author  Marvin Smith
 * @date    5/26/2015
*/
#ifndef __AN_ASCII_HISTORY_WINDOW_CONFIGURATION_HPP__
#define __AN_ASCII_HISTORY_WINDOW_CONFIGURATION_HPP__

// C++ Standard Libraries
#include <string>

namespace CLI{
namespace RENDER{
namespace ASCII{

/**
 * @class An_ASCII_History_Window_Configuration
*/
class An_ASCII_History_Window_Configuration
{

    public:
        
        /**
         * @brief Constructor
         */
        An_ASCII_History_Window_Configuration();
         
    
    private:
        
        /// Class name
        std::string m_class_name;

}; // End of An_ASCII_History_Window_Configuration Class

} // End of ASCII  Namespace
} // End of RENDER Namespace
} // End of CLI    Namespace


#endif
