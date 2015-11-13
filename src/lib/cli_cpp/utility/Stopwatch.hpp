/**
 * @file    Stopwatch.hpp
 * @author  Marvin Smith
 * @date    11/12/2015
*/
#ifndef __CLI_CPP_UTILITY_STOPWATCH_HPP__
#define __CLI_CPP_UTILITY_STOPWATCH_HPP__

namespace CLI{

// C++ Libraries
#include <chrono>


/**
 * @class Stopwatch
*/
template <typename DataType,
          typename ClockType = std::chrono::steady_clock>
class Stopwatch
{
    public:
        
        /**
         * @brief Constructor
        */
        Stopwatch(){}


        /**
         * @brief Start the Stopwatch
         */
        void Start()
        {
            m_start_time = ClockType::now();
        }


        /**
         * @brief Stop the Stopwatch.
        */
        void Stop()
        {
            m_stop_time = ClockType::now();
        }


        /**
         * @brief Get the Duration.
         */
        std::chrono::duration<DataType> Get_Duration()const{
            return std::chrono::duration_cast<std::chrono::duration<DataType>>(m_stop_time - m_start_time);
        }


    private:
        
        /// Start Time
        typename ClockType::time_point m_start_time;

        /// Stop Type
        typename ClockType::time_point m_stop_time;

}; // End of Stopwatch Class


} // End of CLI Namespace

#endif
