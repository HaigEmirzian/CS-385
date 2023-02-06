/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Haig Emirzian
 * Date        : 9/27/22
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>
#include <sstream>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    
    //For each character in input s
    for(const auto &c : s){
        //If the char is < a or > z then its not lowercase
        if(c < 'a' || c > 'z'){
            return false;
        } 
    }
    return true;          
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.

    // You MUST use only a single int for storage and work with bitwise
    // and bitshifting operators.  Using any other kind of solution will
    // automatically result in a grade of ZERO for the whole assignment.

    //Single unsigned int to represent bitset
    unsigned int bitset = 0;

    //Iterate through s to scan each character
    for(const auto &c : s){
        //Store bitshifted values
        unsigned int bitshift = 0;

        //Bitshift by 1
        bitshift = 1 << (c - 'a');

        //Checks for dups if it's 0 or 1
        if(bitset & bitshift){
            return false;

            
        }
        //1 or 0 indicator   
        bitset |= bitshift;
    }
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    //No input arguments
    if(argc < 2 || argc > 2){
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }

    string s;
    istringstream iss;
    iss.str(argv[1]);

    //String either contains uppercase letters, or numbers
    if(!(iss >> s)){
        if(!is_all_lowercase(s)){
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
        }
    }
    
    iss.clear();

    //Checks if chars in string are all unique
    if(is_all_lowercase(s) && !all_unique_letters(s)){
        cout << "Duplicate letters found." << endl;
        return 1;
    }

    //Outputed if all chars are unique and lowercase
    if(all_unique_letters(s) && is_all_lowercase(s)){
        cout << "All letters are unique." << endl;
        return 0;
    }
    //If not all lowercase
    if(!is_all_lowercase(s)){
        cout << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }
    return 0;
}
