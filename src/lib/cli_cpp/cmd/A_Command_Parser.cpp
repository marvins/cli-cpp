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
                                    const bool&                          alias_list_write_access,
                                    const std::vector<A_Command_Variable>& variable_list,
                                    const std::string&                   variable_pathname,
                                    const bool&                          variable_list_write_access )
  : m_class_name("A_Command_Parser"),
    m_command_list(command_list),
    m_cli_command_list(cli_command_list),
    m_variable_list(variable_list),
    m_variable_pathname(variable_pathname),
    m_variable_list_write_access(variable_list_write_access),
    m_alias_list(alias_list),
    m_alias_pathname(alias_pathname),
    m_alias_list_write_access(alias_list_write_access),
    m_regex_split_pattern(regex_split_pattern)
{
}


/***************************************/
/*          Evaluate Command           */
/***************************************/
A_Command_Result::ptr_t  A_Command_Parser::Evaluate_Command( const int&          instance_id,
                                                             const std::string&  test_str,
                                                             const bool&         ignore_alias )const
{
    // Log 
    BOOST_LOG_TRIVIAL(trace) << "Start of Method. File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__ ;
    
    // Split the string
    std::vector<std::string> components = UTILS::String_Split( test_str, m_regex_split_pattern );

    // Get the first element
    std::string command_name = components[0];
    std::string formatted_output;

    // Remove the first element
    if( components.size() > 1 ){
        components.erase(components.begin());
    } else{
        components.clear();
    }

    // Process potential variable names
    A_Command_Variable::Process_Variables( m_variable_list, components );
    
    // Iterate over aliases
    for( size_t idx=0; idx < m_alias_list.size(); idx++ )
    {
        // Check if the alias name matches the command input
        if( m_alias_list[idx].Is_Alias_Name_Match( test_str, false, formatted_output ) == true )
        {
            // Process recursively
            return this->Evaluate_Command( instance_id,
                                           formatted_output, 
                                           true );
        }

    }


    // Iterate over cli commands
    for( size_t idx=0; idx < m_cli_command_list.size(); idx++ ){

        // Check if there is a name match
        if( m_cli_command_list[idx].Is_Name_Match( command_name ) == true )
        {
            return A_Command_Result::Process_CLI_Arguments( instance_id,
                                                            m_cli_command_list[idx],
                                                            components );
        }

    }

    
    // Iterate over regular commands
    for( size_t idx=0; idx < m_command_list.size(); idx++ ){
    
        // Check if there is a name match
        if( m_command_list[idx].Is_Name_Match( command_name ) == true ){
            return A_Command_Result::Process_Arguments( instance_id,
                                                        m_command_list[idx], 
                                                        components );
        }
    }

    
    // Log 
    BOOST_LOG_TRIVIAL(trace) << "End of Method. File: " << __FILE__ << ", Line: " << __LINE__ << ", Func: " << __func__ ;

    // return the result
    return std::make_shared<A_Command_Result>( instance_id,
                                               CommandParseStatus::NO_COMMAND_FOUND,
                                               A_Command( command_name, "", false),
                                               components);

}


/***************************************************/
/*          Update the Autocomplete string         */
/***************************************************/
void A_Command_Parser::Update_Autocomplete_String( const std::string&    input_string,
                                                   std::string&          match_name )const
{
    
    // Split up the input string
    std::vector<std::string> components = UTILS::String_Split( input_string );
    for( int i=0; i<(int)components.size(); i++ ){
        components[i] = UTILS::String_Trim(components[i]);
    }

    // Default the match name
    match_name = "";

    // Clear the match list
    std::vector<std::string> match_list;
    std::string matching_value;

    // Make sure there is at least one component
    if( components.size() <= 0 ){
        return;
    }

    
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

        // Iterate over aliases
        for( size_t i=0; i<m_alias_list.size(); i++ )
        {
            // Check the names
            if( m_alias_list[i].Is_Alias_Name_Substring( components.back() ) == true ){
                match_list.push_back( m_alias_list[i].Get_Alias_Name());
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
            
            // Check if there is an argument match
            if( m_cli_command_list[i].Is_Argument_Substring( arg_idx,
                                                             components.back(),
                                                             matching_value ) == true )
            {
                match_list.push_back( test_output + " " + matching_value );
            }
        }
    }

    // Make sure at least one match was found
    if( (int)match_list.size() <= 0 ){
        return;
    }

    // Prune the list down to the minimum spanning item
    match_name = match_list[0];
    for( size_t i=1; i<match_list.size(); i++ ){
        match_name = UTILS::String_Substring_Match( match_name, match_list[i]);
    }

}


/******************************/
/*       Add a Command        */
/******************************/
void A_Command_Parser::Add_Command( A_Command const& command )
{
    // Add to list
    m_command_list.push_back(command);
}


/*****************************/
/*       Add an Alias        */
/*****************************/
void A_Command_Parser::Add_Command_Alias( const A_Command_Alias& alias )
{
    // Make sure the alias does not already exist.
    for( size_t i=0; i<m_alias_list.size(); i++ ){
        if( m_alias_list[i].Get_Alias_Name() == alias.Get_Alias_Name() ){
            return;
        }
    }

    // Add the alias to the list
    m_alias_list.push_back(alias);

    // Open the file and write the alias out
    if( m_alias_list_write_access == true ){
        A_Command_Alias::Write_Alias_Configuration_File( m_alias_pathname, 
                                                         m_alias_list );
    }

}


/**********************************/
/*         Remove Alias           */
/**********************************/
void A_Command_Parser::Remove_Command_Alias( const A_Command_Alias& alias )
{
    // Modify flag
    bool modified = false;

    //  Make sure the alias does exist in the list
    for( int i=0; i<(int)m_alias_list.size(); i++ ){
        if( m_alias_list[i].Get_Alias_Name() == alias.Get_Alias_Name() ){
            m_alias_list.erase( m_alias_list.begin() + i );
            i--;
            modified = true;
        }
    }

    // Write the list
    if( m_alias_list_write_access && modified ){
        A_Command_Alias::Write_Alias_Configuration_File( m_alias_pathname, 
                                                         m_alias_list );
    }

}


/*************************/
/*      Add Variable     */
/*************************/
void A_Command_Parser::Add_Command_Variable( A_Command_Variable const& new_var )
{
    // Make sure the variable does not already exist.
    for( size_t i=0; i<m_variable_list.size(); i++ ){
        if( m_variable_list[i].Get_Name() == new_var.Get_Name() ){
            return;
        }
    }

    // Add the variable to the list
    m_variable_list.push_back(new_var);

    // Open the file and write the variable out
    if( m_variable_list_write_access == true ){
        A_Command_Variable::Write_Variable_Configuration_File( m_variable_pathname, 
                                                               m_variable_list );
    }
}


/*****************************/
/*      Remove Variable      */
/*****************************/
void A_Command_Parser::Remove_Command_Variable( A_Command_Variable const& old_var )
{
    // Modify flag
    bool modified = false;

    //  Make sure the variable does exist in the list
    for( int i=0; i<(int)m_variable_list.size(); i++ ){
        if( m_variable_list[i].Get_Name() == old_var.Get_Name() ){
            m_variable_list.erase( m_variable_list.begin() + i );
            i--;
            modified = true;
        }
    }

    // Write the list
    if( m_variable_list_write_access == true && modified == true ){
        A_Command_Variable::Write_Variable_Configuration_File( m_variable_pathname, 
                                                               m_variable_list );
    }
}


/********************************************/
/*          Print to Logging String         */
/********************************************/
std::string A_Command_Parser::To_Log_String( int offset )const
{
    std::string gap( offset, ' ');

    std::stringstream sin;

    sin << gap << " - " << m_class_name << std::endl;
    sin << gap << "     - Command-List\n";
    for( auto command : m_command_list ){
        sin << gap << "        - " << command.Get_Name() << std::endl;
    }
    sin << gap << "     - CLI Command-List\n";
    for( auto command : m_cli_command_list ){
        sin << gap << "        - " << command.Get_Formal_Name() << std::endl;
    }
    sin << gap << "     - Alias-List\n";
    for( auto alias : m_alias_list ){
        sin << gap << "        - " << alias.Get_Alias_Name() << std::endl;
    }

    return sin.str();
}

} // End of CMD Namespace
} // End of CLI Namespace

