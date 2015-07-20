/**
 * @file    A_Command_Variable.cpp
 * @author  Marvin Smith
 * @date    7/19/2015
*/
#include "A_Command_Variable.hpp"

// CLI Libraries
#include "../utility/Log_Utilities.hpp"


// Boost Libraries
#include <boost/filesystem.hpp>


// PUGI Xml
#include "../thirdparty/pugixml.hpp"


namespace CLI{
namespace CMD{


/*********************************/
/*          Constructor          */
/*********************************/
A_Command_Variable::A_Command_Variable( const std::string& name,
                                        const std::string& value )
 : m_class_name("A_Command_Variable"),
   m_name(name),
   m_value(value)
{
}


/****************************************/
/*          Process Variables           */
/****************************************/
void A_Command_Variable::Process_Variables( std::vector<A_Command_Variable> const& variable_list,
                                            std::vector<std::string>&              components )
{

    // Check if either list is empty
    if( variable_list.size() <= 0 ||
        components.size() <= 0 )
    {
        return;
    }

    // Iterate over components
    for( size_t cidx=0; cidx<components.size(); cidx++ )
    {
        // Check if component is a variable
        if( Is_Valid_Candidate( components[cidx] ) == false ){
            continue;
        }

        // Iterate over variables
        for( size_t vidx=0; vidx<variable_list.size(); vidx++ )
        {
            // Check if the item is a variable in the list
            if( components[cidx].substr(1) == variable_list[vidx].Get_Name() ){
                components[cidx] = variable_list[vidx].Get_Value();
                break;
            }
        }
    }

}


/************************************************************/
/*      Check if Variable is a Valid Variable Candidate     */
/************************************************************/
bool A_Command_Variable::Is_Valid_Candidate( const std::string& candidate )
{
    // Check if long enough
    if( candidate.size() <= 1 ){
        return false;
    }
    
    // Check if leads with a $
    if( candidate[0] != '$' ){
        return false;
    }

    // Make sure the second value is a char
    if( candidate[1] >= 'a' &&
        candidate[1] <= 'z' )
    {
        return true;
    }
    
    // Make sure the second value is a char
    if( candidate[1] >= 'A' &&
        candidate[1] <= 'Z' )
    {
        return true;
    }

    return false;
}


/********************************/
/*      Equivalent Operator     */
/********************************/
bool A_Command_Variable::operator ==( A_Command_Variable const& other )const
{
    if( m_name  != other.m_name ){ return false; }
    if( m_value != other.m_value){ return false; }
    return true;
}

/*******************************************************/
/*         Load a Variable Configuration File          */
/*******************************************************/
std::vector<A_Command_Variable> A_Command_Variable::Load_Variable_Configuration_File( const std::string& pathname )
{
    
    // Make sure the file exists
    if( boost::filesystem::exists(pathname) == false ){
        return std::vector<A_Command_Variable>();
    }

    
    // Create XML Document
    pugi::xml_document xmldoc;
    pugi::xml_parse_result result = xmldoc.load_file( pathname.c_str() );

    // Make sure it opened properly
    if( result == false ){
        std::stringstream sin;
        sin << "error: " << __FILE__ << ", Line: " << __LINE__ << ". CLI Command Variable Configuration File parsed with errors. Details: " << result.description();
        BOOST_LOG_TRIVIAL(error) << sin.str();
        return std::vector<A_Command_Variable>();
    }

    // Create output list
    std::vector<A_Command_Variable> output;


    // Catch any exceptions
    try{

        // Temp values
        std::string name, value;

        // Get the root node
        pugi::xml_node root_node = xmldoc.child("command-variable-list");

        // Check the node
        if( root_node == pugi::xml_node() ){ 
            return output; 
        }

        
        // Iterate over command nodes
        for( pugi::xml_node_iterator nit = root_node.begin(); nit != root_node.end(); nit++ )
        {
            // Check the node name
            if( std::string(nit->name()) == "variable" ){

                // Get the value
                name  = nit->attribute("name").as_string("");
                value = nit->attribute("value").as_string("");

                if( name != "" && value != "" ){
                    output.push_back( A_Command_Variable( name, value));
                }
            }
        }
    } catch ( std::exception& e ) {
        BOOST_LOG_TRIVIAL(error) << "Exception caught in the Command-Variable Configuration File Parser. Details: " << e.what();
        return output;
    }

    // Return new list
    return output;

}


/********************************************************/
/*        Write an Variable Configuration File          */
/********************************************************/
bool A_Command_Variable::Write_Variable_Configuration_File( const std::string& pathname,
                                                            const std::vector<A_Command_Variable>& variable_list )
{
    
    // Create XML Document
    pugi::xml_document xmldoc;
    
    
    // Catch any exceptions
    try{
    
        // Add the root node
        pugi::xml_node root_node = xmldoc.append_child("command-variable-list");

        // Iterate over the variable list
        for( size_t i=0; i<variable_list.size(); i++ )
        {
            // Create the node
            pugi::xml_node variable_node = root_node.append_child("variable");
            
            // Add the name attribute
            variable_node.append_attribute("name")  = variable_list[i].Get_Name().c_str();
            variable_node.append_attribute("value") = variable_list[i].Get_Value().c_str();

        }

        // Save the file
        xmldoc.save_file( pathname.c_str() );

    } catch ( std::exception& e ) {
        BOOST_LOG_TRIVIAL(error) << "Exception caught in the Command-Variable Configuration File Parser. Details: " << e.what();
        return false;
    }

    // Return true
    return true;
}


} // End of CMD Namespace
} // End of CLI Namespace

