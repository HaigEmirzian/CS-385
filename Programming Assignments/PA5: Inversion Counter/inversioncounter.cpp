/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Haig Emirzian
 * Version     : 1.0
 * Date        : 10/27/22
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;

// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

/**
 * Counts the number of inversions in an array in Theta(n^2) time.
 */
long count_inversions_slow(int array[], int length) {
    // TODO
    //Counts the number of inversions
    long counter = 0;
   
    //Base case
    if(length == 1){
        return counter;
    }

    //Double for loop to iterate through each number and compare with other numbers
    for(long i = 0; i < length; i++){
        for(long j = i + 1; j < length; j++){
            //If A[i] > A[j], then add to counter
            if(array[i] > array[j]){
                ++counter;
            }
        }
    }
    return counter;
}

/**
 * Counts the number of inversions in an array in Theta(n lg n) time.
 */
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort!
    //Base case
    if(length == 1){
        return 0;
    }

    //Initializes new array
    int* arr = new int[length];
    //Runs mergesort for the fast way
    long count = mergesort(array, arr, 0, (length - 1));
    //Delete array to prevent memory leaks
    delete[] arr;
    return count;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    //Initialzes the counter and mid
    //Intializes low into i1 and i2 which tracks the second half of the array
    long count = 0;
    int i1 = low;
    int mid = low + ((high - low) / 2);
    int i2 = mid + 1;
    int i = low;
    
    //Base case: length is 1, then return 0
    if(low >= high){
        return count;
    }

    //Add to count if low is less than high
    if(low < high){
        count += mergesort(array, scratch, low, mid);
        count += mergesort(array, scratch, mid + 1, high);
    }

    //Copies from array to scrtach while iterating
    while(i1 <= mid && i2 <= high){
        if(array[i1] <= array[i2]){
            scratch[i++] = array[i1++];
        } else{
            //Else checks if array[i1] is greater than array[i2]
            scratch[i++] = array[i2++];
            count += (mid - i1 + 1);
        }
    }

    //Iterates through array to add low-mid to scratch
    for(int j = i1; j <= mid; j++){
        scratch[i++] = array[i1++];
    }
    //Iterates through array to add mid+1-high to scratch
    for(int j = i2; j <= high; j++){
        scratch[i++] = array[i2++];
    }

    //Copies each element
    for(int i = low; i <= high; i++){
        array[i] = scratch[i];
    }

    return count;    
}

int main(int argc, char *argv[]) {
    // TODO: parse command-line argument
    string strA = "";
    string strB = "slow";

    //Checks if the arguments are anything but 1 argument or 2 arguments
    if(argc != 1 && argc != 2){
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    }

    //Checks to see if arguments are >= 2 and compares if input is the slow algo
    if(argc >= 2 && strB.compare(argv[1]) != 0){
        cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;

    
    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }

    // TODO: produce output  
    //If input is empty
    if(index == 0){
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    } 

    //Outputs number of inversions
    if(argc == 1){
        cout << "Number of inversions: " << count_inversions_fast(&values[0], index) << endl;
    } else{
        cout << "Number of inversions: " << count_inversions_slow(&values[0], index) << endl;
    }

    return 0;
}
