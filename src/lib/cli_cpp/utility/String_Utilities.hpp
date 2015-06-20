/**
 * @file    String_Utilities.hpp
 * @author  Marvin Smith
 * @date    5/20/2015
 */
#ifndef __CLI_UTILS_STRING_UTILITIES_HPP__
#define __CLI_UTILS_STRING_UTILITIES_HPP__

// C++ Standard Libraries
#include <cinttypes>
#include <sstream>
#include <string>
#include <vector>

namespace CLI{
namespace UTILS{

/**
 * @brief Convert a Number to a String.
 *
 * @param[in] value Value to convert.
 *
 * @return String format.
 */
template <typename TP>
std::string num2str( TP const& value )
{
    std::stringstream sin;
    sin << value;
    return sin.str();
}


/**
 * @brief Convert a String into a Number.
 *
 * @param[in] value to convert.
 *
 * @return number format.
 */
template <typename TP>
TP str2num( const std::string& value )
{
    std::stringstream sin;
    sin << value;
    TP output;
    sin >> output;
    return output;
}


/**
 * @enum StringAlignment
 */
enum class StringAlignment : uint8_t{
    CENTER = 1,
    LEFT   = 2,
    RIGHT  = 3,
}; // End of StringAlignment Enum Class


/**
 * @enum StringDirection
 */
enum class StringDirection : uint8_t{
    LEFT  = 1,
    RIGHT = 2,
    BOTH  = 3,
}; // End of StringDirection Enum Class


/**
 * @brief Trim a string.
 *
 * @param[in] data Data to trim.
 * @param[in] strip_patterns Pattern to strip.
 * @param[in] strip_direction Direction to strip.
 * 
 * @return Resulting string.
 */
std::string String_Trim( const std::string&     data,
                         const std::string&     strip_patterns,
                         const StringDirection& strip_direction);


/**
 * @brief Trim a string.
 *
 * @param[in] data Data to trim.
 * @param[in] strip_direction Direction to strip.
 *
 * @return Trimmed string.
 */
std::string String_Trim( const std::string&     data,
                         const StringDirection& strip_direction);


/**
 * @brief Trim a string.
 *
 * @param[in] data Data to trim.
 * @param[in] strip_pattern Pattern to strip.
 *
 * @return Trimmed string.
 */
std::string String_Trim( const std::string&     data,
                         const std::string&     strip_pattern );


/**
 * @brief Trim a string.
 *
 * @param[in] data Data to trim.
 * 
 * @return Resulting string.
 */
std::string String_Trim( const std::string&     data );

                
/**
 * @brief String Fill
*/
std::string String_Fill( const std::string&      data,
                         const char&             fill_char,
                         const int&              fill_cnt,
                         const StringDirection&  fill_direction = StringDirection::RIGHT );


/**
 * @brief Format a string
 *
 * @param[in] data Data to align
 * @param[in] alignment Alignment format.
 */
std::string Format_String( const std::string&     data,
                           const int&             output_size,
                           const StringAlignment& alignment = StringAlignment::CENTER,
                           const char&            fill_char = ' ' );


/**
 * @brief Split the string into multiple elements.
 *
 * @param[in] data Data to split.
 * @param[in] pattern Pattern to split with.
 *
 * @return List of strings.
 */
 std::vector<std::string> String_Split( const std::string& data,
                                        const std::string& pattern = " ");


/**
 * @brief Merge the components into a string.
 *
 * @param[in] components.
*/
std::string String_Merge( std::vector<std::string> const& components );


/**
 * @brief Format a string into proper command format.
 *
 * This method will take an input string and format it to look like what the command 
 * alias input wants.  In essence, it will split the string into components with spaces
 * being the delimiter.  Then it will re-merge them such that there is one space between them.
 *
 * The following example should illustrate this.
 *
 * - Input: " ls  -lf "   Output: "ls -ls"
 *
 * @param[in] input_data String input to format.
 *
 * @return Formatted String.
 */
std::string Format_Command_String( const std::string& input_data );


/**
 * @brief Return the matching substring between the two strings.
 *
 * @param[in] str1 First string to compare.
 * @param[in] str2 Second string to compare.
 *
 * @return Substring match.
*/
std::string String_Substring_Match( const std::string& str1,
                                    const std::string& str2 );


/**
 * @brief Return the matching substring between the items in the string list.
 *
 * @param[in] string_list List of strings to match.
 *
 * @return Substring match
*/
std::string String_Substring_Match( const std::vector<std::string>& string_list );


} // End of UTILS Namespace
} // End of CLI   Namespace

#endif
