/**
 * @file    cli-cpp-config-generator.cpp
 * @author  Marvin Smith
 * @date    7/5/2015
*/

// CLI-C++ Libraries
#include <cli_cpp.hpp>

// C++ Standard Libraries
#include <cstdlib>
#include <deque>
#include <iostream>
#include <string>


/**
 * @brief Configuration Options
*/
class Options{

    public:

        /**
         * @brief Constructor
        */
        Options()
          : m_config_pathname_set(false)
        {
        }


        /**
         * @brief Get the Configuration Pathname
        */
        std::string Get_Config_Pathname()const{
            return m_config_pathname;
        }


        /**
         * @brief Set the Configuration Pathname.
        */
        void Set_Config_Pathname( const std::string& config_pathname )
        {
            m_config_pathname_set = true;
            m_config_pathname     = config_pathname;
        }

        /**
         * @brief Check if the Configuration Path is set.
        */
        bool Config_Pathname_Set()const{
            return m_config_pathname_set;
        }


    private:

        /// Configuration Pathname.
        std::string m_config_pathname;

        /// Config Pathname set
        bool m_config_pathname_set;

}; // End of Options Class


/**
 * @brief Parse the Command-Line
 *
 * @param[in] argc Number of command arguments.
 * @param[in] argv List of command arguments.
*/
Options Parse_Command_Line( int argc, char* argv[] );


/**
 * @brief Print the Usage Instructions
 *
 * @param[in] application_name
*/
void Usage( std::string const& application_name );


/**
 * @brief Main Driver
*/
int main( int argc, char* argv[] )
{
    // Parse Command-Line
    Options options = Parse_Command_Line( argc, argv );

    // Grab the configuration pathname
    std::string config_pathname = options.Get_Config_Pathname();

    // Parse configuration options
    CLI::IO::CONFIG::A_CLI_Configuration_File_Parser parser( config_pathname );

    // Write the configuration file
    parser.Write();

    // exit
    return 0;
}


/*************************************/
/*      Parse the Command-Line       */
/*************************************/
Options Parse_Command_Line( int argc, char* argv[] )
{
    // Grab the application name
    std::string application_name = argv[0];


    // Create list
    std::deque<std::string> args;
    for( int i=1; i<argc; i++ ){
        args.push_back(argv[i]);
    }

    // Output options
    Options options;
    std::string arg;

    // Prune list
    while( args.size() > 0 ){

        // Get the next argument
        arg = args[0];
        args.pop_front();

        // Check if help requested
        if( arg == "-h" ||
            arg == "--help" )
        {
            Usage( application_name );
            std::exit(0);
        }

        // Otherwise, grab the pathname
        else{
            if( options.Config_Pathname_Set() == true ){
                std::cerr << "error: Configuration pathname already set.  Unknown argument." << std::endl;
                Usage(application_name);
                std::exit(1);
            }
            options.Set_Config_Pathname(arg);
        }

    }

    // Make sure the config pathname was set.
    if( options.Config_Pathname_Set() == false ){
        std::cerr << "error: No configuration pathname set." << std::endl;
        Usage( application_name );
        std::exit(1);
    }

    // Return output
    return options;
}


/***************************************/
/*      Print Usage Instructions       */
/***************************************/
void Usage( const std::string& application_name )
{

    // Print the command
    std::cout << "usage: " << application_name << " [options]  <config-path>" << std::endl;
    std::cout << std::endl;

    // Print the options
    std::cout << "Options:" << std::endl;
    std::cout << "  -h | --help   : Print usage instructions and exit." << std::endl;
    std::cout << std::endl;

    // Print the remaining options
    std::cout << "Required Items: " << std::endl;
    std::cout << "  config-path : Path to the xml configuration file.  If one does not exist," << std::endl;
    std::cout << "                then it will be created.  If it does exist, it will be " << std::endl;
    std::cout << "                updated with any missing parameters." << std::endl;
    std::cout << std::endl;

}


