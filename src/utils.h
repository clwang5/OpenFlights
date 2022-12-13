#include <utility>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <cassert>
#include <fstream>

/**
 * Takes a filename and reads in all the text from the file
 * Newline characters are also just characters in ASCII
 * 
 * @param filename The name of the file that will fill the string
 * @return A string containing the whole text of the given file
 */
std::string file_to_string(const std::string & filename);


/**
 * Given a string and character, split the string by the character and store in a vector
 * A 'split' string treats the character as a breakpoint and creates a separate item
 * in the output vector for each substring. 
 * 
 * NOTE: The separator character is not included in the substrings.
 * 
 * The total number of substrings created (the length of fields) is returned 
 *  
 * @param str1 The string being split
 * @param sep The separator character
 * @param fields The string vector storing all substrings created by the split
 * @return The number of substrings created
 */
int SplitString(const std::string & str1, char sep, std::vector<std::string> &fields);