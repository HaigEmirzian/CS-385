/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Haig Emirzian
 * Date        : October 3, 2022
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;


vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time.

    vector<vector<int>> ways;
    vector<vector<int>> result;

    //base case: if input is empty
    if(num_stairs <= 0){
        ways.push_back(vector<int>());
    } else {

        //Makes sure the user can move up to 3 stairs at a time
        for(int i = 1; i < 4; i++){
            //Makes sure the input is in range of 1-3
            if(num_stairs >= i){
                //Recursive call to get input in range of 1-3
                result = get_ways(num_stairs - i);

                //Iterates through the smallest vector
                for(size_t j = 0; j < result.size(); j++){
                    //Adds each step into the smallest vector
                    result.at(j).insert(result.at(j).begin(), 1, i);
                }
                //Adds the smaller vector into the bigger vector
                ways.insert(ways.end(), result.begin(), result.end());
            }   
        }
    }
    return ways;
}

//Counts number of digits to with the spacing in the output
int num_digits(int num){
    int count = 0;
    while(num != 0){
        num = num / 10;
        count++;
    }   
    return count;
}


void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.

    int max_width = num_digits(ways.size());
    int count = 1;

    //Double iteration to help create the values in an array format
    for(size_t i = 0; i < ways.size(); i++) {
        //right aligns the number of rows
        cout << right << setw(max_width) << count++;
        //beginning of the array
        cout << ". [";
        //loads steps into array
        for(size_t j = 0; j < ways[i].size(); j++) {
            //prints the value without an extra comma
            if(j + 1 == ways[i].size()){
                cout << ways[i][j];
            //prints a comma after every value
            } else{
                cout << ways[i][j] << ", ";
            }
        }
        //ends the array with a bracket
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    int num_stairs;

    //No input arguments or too many arguments
    if(argc < 2 || argc > 2){
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }

    //Takes in user input
    istringstream  iss(argv[1]);
    
    //Input has to be an int and cannot be less than 1
    if(!(iss >> num_stairs) || num_stairs < 1){
        cout << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }

    iss.clear();

    vector<vector<int>> ways = get_ways(num_stairs);

    //Outputs the number of ways to climb
    if(ways.size() == 1){
        cout << ways.size() << " way to climb " << num_stairs << " stair." << endl;
    } else{
        cout << ways.size() << " ways to climb " << num_stairs << " stairs." << endl;
    }

    //Displays stairs
    display_ways(get_ways(num_stairs));

    return 0;
}
