/**
 * @file    A_Command_Parser.cpp
 * @author  Marvin Smith
 * @date    5/18/2015
 */
#include "A_Command_Parser.hpp"

// Boost Libraries
#include <boost/algorithm/string.hpp>

// CLI Libraries
#include "../utility/Log_Utilities.hpp"
#include "../utility/String_Utilities.hpp"

// C++ Standard Libraries
#include <iostream>


namespace CLI{
namespace CMD{

/*****************************/
/*       Constructor         */
/*****************************/
A_Command_Parser::A_Command_Parser( const std::string&                   regex_split_pattern,
                                    const std::vector<A_CLI_Command>&    cli_command_list,
                                    const std::vector<A_Command>&        command_list,
                                    const std::vector<A_Command_Alias>&  alias_list,
                                    const std::string&                   alias_pathname,
                                    const bool&                          alias_list_write_access )
  : m_class_name("A_Command_Parser"),
    m_command_list(command_list),
    m_cli_command_list(cli_command_list),
    m_alias_list(alias_list),
    m_alias_pathname(alias_pathname),
    m_alias_list_write_access(alias_list_write_access),
    m_regex_split_pattern(regex_split_pattern)
{
}


/***************************************/
/*          Evaluate Command           */
/***************************************/
A_Command_Result  A_Command_Parser::Evaluate_Command( const std::string&  test_str,
                                                      const bool&         ignore_alias )const
{
    // Log 
    BOOST_LOG_TRIVIAL(trace) << "Start of Method. File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__ ;
    
    // Split the string
    std::vector<std::string> components = Parse_String( test_str );

    // Get the first element
    std::string command_name = components[0];
    std::string formatted_output;

    // Remove the first element
    if( components.size() > 1 ){
        components.erase(components.begin());
    } else{
        components.clear();
    }
    
    // Iterate over aliases
    for( size_t idx=0; idx < m_alias_list.size(); idx++ )
    {
        // Check if the alias name matches the command input
        if( m_alias_list[idx].Is_Alias_Name_Match( test_str, false, formatted_output ) == true )
        {
            // Process recursively
            return this->Evaluate_Command( formatted_output, 
                                           true );
        }

    }


    // Iterate over cli commands
    for( size_t idx=0; idx < m_cli_command_list.size(); idx++ ){
        if( m_cli_command_list[idx].Is_Match( command_name ) == true )
        {
            return A_Command_Result( m_cli_command_list[idx].Get_Mode(),
                                     A_Command( command_name, 
                                                m_cli_command_list[idx].Get_Description(), 
                                                false),
                                     components 
                                   );
        }

    }

    
    // Iterate over regular commands
    for( size_t idx=0; idx < m_command_list.size(); idx++ ){
    
        // Check if there is a name match
        if( m_command_list[idx].Is_Name_Match( command_name ) == true ){
            return A_Command_Result::Process_Arguments( m_command_list[idx], 
                                                        components );
        }
    }

    
    // Log 
    BOOST_LOG_TRIVIAL(trace) << "End of Method. File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__ ;

    // return the result
    return A_Command_Result( CommandParseStatus::NO_COMMAND_FOUND,
                             A_Command( command_name, "", false),
                             components);

}


/******************************/
/*        Parse String        */
/******************************/
std::vector<std::string>  A_Command_Parser::Parse_String( const std::string& test_str )const
{
    // Create output list
    std::vector<std::string> output;

    // Trim the string
    std::string trimmed_string = UTILS::String_Trim( test_str, " ", UTILS::StringDirection::BOTH );

    // Split
    boost::split( output, trimmed_string, boost::is_any_of( m_regex_split_pattern ));

    // return results
    return output;

}


/***************************************************/
/*          Update the Autocomplete string         */
/***************************************************/
void A_Command_Parser::Update_Autocomplete_String( const std::string&          input_string,
                                                   std::vector<std::string>&   match_list )const
{
    
    // Split up the input string
    std::vector<std::string> components = UTILS::String_Split( input_string );
    for( int i=0; i<(int)components.size(); i++ ){
        components[i] = UTILS::String_Trim(components[i]);
    }
    

    // Clear the match list
    match_list.clear();
    std::string matching_value;

    
    // use the last element
    int idx = components.size()-1;

    
    // Check the command name
    if( idx == 0 ){
        
        // Iterate over commands
        for( size_t i=0; i<m_command_list.size(); i++ ){
            
            // Check the names
            if( m_command_list[i].Is_Name_Substring( components.back() ) == true ){
                match_list.push_back( m_command_list[i].Get_Name() );
            }
        }

        // Iterate over CLI Commands
        for( size_t i=0; i<m_cli_command_list.size(); i++ )
        {
            // Check the names
            if( m_cli_command_list[i].Is_Name_Substring( components.back(), 
                                                         matching_value ) == true )
            {
                match_list.push_back( matching_value );
            }
        }
    }

    // Otherwise, check the arguments
    else{

        // Concat all other arguments to the test string
        std::string test_output = components[0];
        for( size_t i=1; i<components.size()-1; i++ ){
            test_output += " " + components[i];
        }
        
        // The argument in question
        int arg_idx = idx-1;

        // Pass the component to each command
        for( size_t i=0; i<m_command_list.size(); i++ ){
            
            // Check if there is a match
            if( m_command_list[i].Is_Argument_Substring( arg_idx, 
                                                         components.back(), 
                                                         matching_value ) == true )
            {
                match_list.push_back( test_output + " " + matching_value );
            }
        }

        // pass the component to each cli command
        for( size_t i=0; i<m_cli_command_list.size(); i++ ){

        }
        

    }
}


/*****************************/
/*       Add an Alias        */
/*****************************/
void A_Command_Parser::Add_Command_Alias( const A_Command_Alias& alias )
{
    // Check the alias list to make sure it does not already exist.
    std::cout << "Adding alias: " << alias.Get_Alias_Name() << std::endl;

}


/**********************************/
/*         Remove Alias           */
/**********************************/
void A_Command_Parser::Remove_Command_Alias( const A_Command_Alias& alias )
{
    // 

}


} // End of CMD Namespace
} // End of CLI Namespace

