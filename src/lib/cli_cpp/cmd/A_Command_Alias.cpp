/**
 * @file    A_Command_Alias.cpp
 * @author  Marvin Smith
 * @date    6/19/2015
 */
#include "A_Command_Alias.hpp"

// CLI Libraries
#include "../utility/Log_Utilities.hpp"
#include "../utility/String_Utilities.hpp"


// Boost Libraries
#include <boost/filesystem.hpp>


// PUGI Xml
#include "../thirdparty/pugixml.hpp"


// C++ Standard Libraries
#include <sstream>


namespace CLI{
namespace CMD{


/*********************************/
/*          Constructor          */
/*********************************/
A_Command_Alias::A_Command_Alias()
  : m_class_name("A_Command_Alias"),
    m_alias_name(""),
    m_command_text("")
{
}

/********************************/
/*         Constructor          */
/********************************/
A_Command_Alias::A_Command_Alias( const std::string& alias_name,
                                  const std::string& command_text )
  : m_class_name("A_Command_Alias"),
    m_alias_name(UTILS::Format_Command_String(alias_name)),
    m_command_text(command_text)
{
}


/*************************************/
/*        Is Alias Name Match        */
/*************************************/
bool A_Command_Alias::Is_Alias_Name_Match( const std::string&  test_input,
                                           const bool&         match_whole,
                                           std::string&        formatted_output ) const
{
    // Clear the output
    formatted_output = "";
   
    // Format the string
    std::string formatted_input = UTILS::Format_Command_String( test_input );

    // If we are matching the whole, just do a compare
    if( match_whole == true ){
        if( formatted_input == m_alias_name ){
            formatted_output = m_command_text;
            return true;
        } else {
            return false;
        }
    }

    // If the alias is larger than the formatted input, then we
    // know it is false
    if( m_alias_name.size() > formatted_input.size() ){
        return false;
    }

    // If the alias is the same size, do a compare
    if( m_alias_name.size() == formatted_input.size() ){
        if( m_alias_name == formatted_input ){
            formatted_output = m_command_text;
            return true;
        }
        else{
            return false;
        }
    }

    // Lastly, do a substring if smaller
    if( formatted_input.substr(0, m_alias_name.size()) == m_alias_name ){
        
        // Append the output
        formatted_output = m_command_text + formatted_input.substr(m_alias_name.size());
        return true;
    }

    // Otherwise, it failed
    return false;
}


/*****************************************************/
/*         Load an Alias Configuration File          */
/*****************************************************/
std::vector<A_Command_Alias> A_Command_Alias::Load_Alias_Configuration_File( const std::string& pathname )
{
    
    // Make sure the file exists
    if( boost::filesystem::exists(pathname) == false ){
        return std::vector<A_Command_Alias>();
    }

    
    // Create XML Document
    pugi::xml_document xmldoc;
    pugi::xml_parse_result result = xmldoc.load_file( pathname.c_str() );

    // Make sure it opened properly
    if( result == false ){
        std::stringstream sin;
        sin << "error: " << __FILE__ << ", Line: " << __LINE__ << ". CLI Command Configuration File parsed with errors. Details: " << result.description();
        BOOST_LOG_TRIVIAL(error) << sin.str();
        return std::vector<A_Command_Alias>();
    }

    // Create output list
    std::vector<A_Command_Alias> output;


    // Catch any exceptions
    try{

        // Temp values
        std::string name, value;

        // Get the root node
        pugi::xml_node root_node = xmldoc.child("command-alias-list");

        // Check the node
        if( root_node == pugi::xml_node() ){ 
            return output; 
        }

        
        // Iterate over command nodes
        for( pugi::xml_node_iterator nit = root_node.begin(); nit != root_node.end(); nit++ )
        {
            // Check the node name
            if( std::string(nit->name()) == "alias" ){

                // Get the value
                name  = nit->attribute("name").as_string("");
                value = nit->attribute("value").as_string("");

                if( name != "" && value != "" ){
                    output.push_back( A_Command_Alias( name, value));
                }
            }
        }
    } catch ( std::exception& e ) {
        BOOST_LOG_TRIVIAL(error) << "Exception caught in the Command-Alias Configuration File Parser. Details: " << e.what();
        return output;
    }

    // Return new list
    return output;

}


/*****************************************************/
/*        Write an Alias Configuration File          */
/*****************************************************/
bool A_Command_Alias::Write_Alias_Configuration_File( const std::string& pathname,
                                                      const std::vector<A_Command_Alias>& alias_list )
{
    
    // Create XML Document
    pugi::xml_document xmldoc;
    
    
    // Catch any exceptions
    try{
    
        // Add the root node
        pugi::xml_node root_node = xmldoc.append_child("command-alias-list");

        // Iterate over the alias list
        for( size_t i=0; i<alias_list.size(); i++ )
        {
            // Create the node
            pugi::xml_node alias_node = root_node.append_child("alias");
            
            // Add the name attribute
            alias_node.append_attribute("name")  = alias_list[i].Get_Alias_Name().c_str();
            alias_node.append_attribute("value") = alias_list[i].Get_Command_Text().c_str();

        }

        // Save the file
        xmldoc.save_file( pathname.c_str() );

    } catch ( std::exception& e ) {
        BOOST_LOG_TRIVIAL(error) << "Exception caught in the Command-Alias Configuration File Parser. Details: " << e.what();
        return false;
    }

    // Return true
    return true;
}



/**********************************************/
/*        Create Alias from CLI Input         */
/**********************************************/
A_Command_Alias A_Command_Alias::From_CLI_Input( const std::string& input, bool& valid )
{
    // Default valid flag to false
    valid = false;

    // Check the input string
    if( (int)input.size() <= 0 )
    {
        return A_Command_Alias();
    }

    // Create a component list
    std::vector<std::string> components = UTILS::String_Split( input );

    // Check the component list
    if( components.size() < 2 ){
        return A_Command_Alias();
    }

    std::vector<std::string> arg_components;
    for( size_t i=1; i<components.size(); i++ ){
        arg_components.push_back(components[i]);
    }

    // Merge
    std::string name  = components[0];
    std::string value = UTILS::String_Merge(arg_components);
    
    // Return the output
    valid = true;
    return A_Command_Alias( name, value );
}


/***************************************/
/*      Write to Debugging String      */
/***************************************/
std::string A_Command_Alias::To_Debug_String()const{
    
    // create stringstream
    std::stringstream sin;
    sin << m_class_name << std::endl;
    sin << "    Alias Name   : " << m_alias_name << std::endl;
    sin << "    Command Text : " << m_command_text << std::endl;
    
    return sin.str();
}

} // End of CMD Namespace
} // End of CLI Namespace

