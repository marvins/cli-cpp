/**
 * @file    A_Command_Variable.cpp
 * @author  Marvin Smith
 * @date    7/19/2015
*/
#include "A_Command_Variable.hpp"

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
            if( components[cidx] == variable_list[vidx].Get_Name() ){
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


} // End of CMD Namespace
} // End of CLI Namespace

