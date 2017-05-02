/**
 * @file    Network_Scanner.hpp
 * @author  Marvin Smith
 * @date    7/5/2015
*/
#ifndef __CLI_CPP_APP_UTILS_NETWORK_SCANNER_HPP__
#define __CLI_CPP_APP_UTILS_NETWORK_SCANNER_HPP__

// C++ Standard Libraries
#include <chrono>
#include <memory>
#include <string>
#include <thread>
#include <vector>


/**
 * @brief Network Asset
*/
class Network_Asset
{
    public:
        
        /**
         * @brief Constructor
         *
         * @param[in] name
         * @param[in] address
         * @param[in] ping_max_attempts
         * 
        */
        Network_Asset( const std::string&  name,
                       const std::string&  address,
                       const int&          ping_max_attempts );

        
        /**
         * @brief Get the Name
         *
         * @return Name
        */
        inline std::string Get_Name()const{
            return m_name;
        }


        /**
         * @brief Get the Address.
         *
         * @return Address.
        */
        inline std::string Get_Address()const{
            return m_address;
        }


        /**
         * @brief Get the status string.
        */
        std::string Get_Status_String()const;


        /**
         * @brief Get the Timestamp String
        */
        std::string Get_Last_Scan_Time_String()const;
        

        /**
         * @brief Scan Asset
        */
        void Scan_Asset();

    private:
        
        /// Class Name
        std::string m_class_name;

        /// Asset Name
        std::string m_name;

        /// Address
        std::string m_address;

        /// Max attempts
        int m_ping_max_attempts;

        /// Status
        int m_status;

        /// Last Scan Timestamp
        std::chrono::system_clock::time_point m_last_scan_time;


}; // End of Network_Asset Class


/**
 * @brief Network scanning object which runs in the background.
*/
class Network_Scanner
{

    public:
       
        /// Pointer Type
        typedef std::shared_ptr<Network_Scanner> ptr_t;

        /**
         * @brief Constructor
         */
        Network_Scanner();


        /**
         * @brief Start the scanner
        */
        void Start_Scanner();


        /**
         * @brief Stop the scanner.
        */
        void Stop_Scanner();


        /**
         * @brief Add Network Ping Address.
         * 
         * @param[in] asset_name Name of the system.
         * @param[in] address Address to ping.
         * @param[in] max_attempts
        */
        void Add_Network_Asset( std::string const& asset_name,
                                std::string const& network_address,
                                int const&         max_attempts  );
        

        /**
         * @brief Get network assets
         */
        inline std::vector<Network_Asset> Get_Network_Assets()const{
            return m_network_assets;
        }

    private:

        /**
         * @brief Scan Thread Runner
        */
        void Scan_Runner();
        

        /// Class Name
        std::string m_class_name;

        
        /// Background Thread
        std::thread m_scan_thread;
        

        /// Running flag
        bool m_is_running;


        /// Asset List
        std::vector<Network_Asset> m_network_assets;

}; // End of Network_Scanner Class

#endif
