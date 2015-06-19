/**
 * @file    String_Utilities.cpp
 * @author  Marvin Smith
 * @date    5/20/2015
 */
#include "String_Utilities.hpp"

// Boost Libraries
#include <boost/algorithm/string.hpp>

// CLI Libraries
#include "Log_Utilities.hpp"


namespace CLI{
namespace UTILS{

/// Default String Trim Pattern
const std::string DEFAULT_TRIM_PATTERN = " \n\0";

/************************************/
/*         Strip A String           */
/************************************/
std::string String_Trim( const std::string&  data )
{
    return String_Trim( data, DEFAULT_TRIM_PATTERN, StringDirection::BOTH );
}


/************************************/
/*         Strip A String           */
/************************************/
std::string String_Trim( const std::string&  data,
                         const std::string&  strip_pattern )
{
    return String_Trim( data, 
                        strip_pattern,
                        StringDirection::BOTH );
}

/************************************/
/*         Strip A String           */
/************************************/
std::string String_Trim( const std::string&  data,
                         const StringDirection& strip_direction )
{
    return String_Trim( data, DEFAULT_TRIM_PATTERN, strip_direction);
}

/************************************/
/*         Strip A String           */
/************************************/
std::string String_Trim( const std::string&  data,
                         const std::string&  patterns,
                         const StringDirection& strip_direction )
{
    // Skip empty strings
    if( data.size() <= 0 ){
        return data;
    }
    if( patterns.size() <= 0 ){
        BOOST_LOG_TRIVIAL(error) << "Pattern input is currently empty. File: " <<__FILE__ << ", Line: " << __LINE__;
        return data;
    }

    // Set our output
    std::string output = data;

    // trim from start
    if( strip_direction == StringDirection::LEFT ||
        strip_direction == StringDirection::BOTH )
    {
        boost::trim_left_if( output, boost::is_any_of(patterns));
    }

    // trim right
    if( strip_direction == StringDirection::RIGHT || 
        strip_direction == StringDirection::BOTH )
    {
        boost::trim_right_if( output, boost::is_any_of(patterns));
    }

    return output;
}


/************************************/
/*          Fill A String           */
/************************************/
std::string String_Fill( const std::string&      data,
                         const char&             fill_char,
                         const int&              fill_cnt,
                         const StringDirection&  fill_direction )
{
    // Create padding
    std::string padding( fill_cnt, fill_char);
    
    // If both
    if( fill_direction == StringDirection::BOTH ){
        return String_Fill( String_Fill( data, 
                                         fill_char, 
                                         fill_cnt, 
                                         StringDirection::LEFT),
                            fill_char,
                            fill_cnt,
                            StringDirection::RIGHT );
    }

    // If left
    if( fill_direction == StringDirection::LEFT ){
        return (padding + data);
    }

    // If Right
    if( fill_direction == StringDirection::RIGHT ){
        return (data + padding);
    }

    // Return nothing different
    return data;
}


/***************************************/
/*          Format a String            */
/***************************************/
std::string Format_String( const std::string&      data,
                           const int&              output_size,
                           const StringAlignment&  alignment,
                           const char&             fill_char )
{
    // Create output string
    std::string fixed_data = data;
    std::string output;

    // Fill difference
    const int fill_difference = output_size - data.size();

    // Check the data size, crop if necessary and return
    if( ((int)fixed_data.size()) > output_size ){
        fixed_data = fixed_data.substr(0,output_size);
        return fixed_data;
    }

    // If left alignment, this is pretty easy.  Just put the output down and fill left
    if( alignment == StringAlignment::LEFT ){
        output = String_Fill( fixed_data, 
                              fill_char, 
                              fill_difference, 
                              StringDirection::RIGHT );
        return output;
    }

    // If Right Alignment, put the string down and fill right
    if( alignment == StringAlignment::RIGHT ){
        output = String_Fill( fixed_data,
                              fill_char,
                              fill_difference,
                              StringDirection::LEFT );
        return output;
    }


    // If Center Alignment Fill with Half Each.  
    if( alignment == StringAlignment::CENTER ){

        // Fill Left First
        output = String_Fill( fixed_data,
                              fill_char,
                              fill_difference/2,
                              StringDirection::LEFT);
        
        // Fill Right and Return
        return String_Fill(  output,
                             fill_char,
                             output_size - output.size(),
                             StringDirection::RIGHT );

    }

    // Return junk if we get here
    return data;
}


/***********************************************/
/*               Split the string              */
/***********************************************/
std::vector<std::string> String_Split( const std::string& data, 
                                       const std::string& pattern )
{
    // Create output
    std::vector<std::string> output, result;

    // Perform split
    boost::split( output, data, boost::is_any_of(pattern));

    for( int i=0; i<(int)output.size(); i++ ){
        if( String_Trim(output[i]).size() > 0 ){
            result.push_back(String_Trim(output[i]));
        }
    }

    // return value
    return result;
}


/***************************************/
/*       Format a Command String       */
/***************************************/
std::string Format_Command_String( const std::string& input_data )
{

    // Split into components
    std::vector<std::string> components = String_Split( input_data, " ");

    // Skip if there is just junk
    if( input_data.size() <= 0 ){
        return "";
    }

    // Merge back
    std::string output = "";

    for( size_t i=0; i<components.size(); i++ ){
        output += " " + components[i];
    }

    // Return output
    return output;
}


} // End of UTILS Namespace
} // End of CLI   Namespace

