/*******************************************************************************
 * Filename: shortestpaths.cpp
 * Author  : Haig Emirzian and Nicholas Weidman
 * Version : 1.0
 * Date    : December 4, 2022
 * Description: Computes the all-pairs shortest-paths
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <limits>
using namespace std;


//Computes the number of digits in a given number
int num_digits(long num){
    int count=0;
    while(num>0){
        num/=10;
        count++;
    }
    return count;
}

//backtrack through the paths matrix to find the path it takes
string compute_paths(vector <vector<char>> paths, int i, int j){
  string s1(1, 'A'+i);
  if(paths[i][j]=='-'){
    return s1 + " -> ";
  } 
  return compute_paths(paths, i, (int)(paths[i][j]-'A')) + compute_paths(paths, (int)(paths[i][j]-'A'),j);
}

//display an inputted matrix of long ints with its given title.
void display_table(vector <vector<long>> matrix, const string &label, 
                   const bool use_letters = false) { 
  long INF = numeric_limits<long>::max();
  cout << label << endl; 
  long max_val = 0; 
  for (size_t i = 0; i < matrix.size(); i++) { 
    for (size_t j = 0; j < matrix.size(); j++) { 
      long cell = matrix[i][j]; 
      if (cell < INF && cell > max_val) { 
        max_val = matrix[i][j]; 
      } 
    } 
  } 
  int max_cell_width = use_letters ? num_digits(max_val) : 
    num_digits(max(static_cast<long>(matrix.size()), max_val)); 
  cout << ' '; 
  for (size_t j = 0; j < matrix.size(); j++) { 
    cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A'); 
  } 
  cout << endl; 
  for (size_t i = 0; i < matrix.size(); i++) { 
    cout << static_cast<char>(i + 'A'); 
    for (size_t j = 0; j < matrix.size(); j++) { 
      cout << " " << setw(max_cell_width); 
      if (matrix[i][j] == INF) { 
        cout << "-"; 
      } else if (use_letters) { 
        cout << static_cast<char>(matrix[i][j] + 'A'); 
      } else { 
        cout << matrix[i][j]; 
      } 
    } 
    cout << endl; 
  } 
  cout << endl; 
} 

//display an inputted matrix of characters with its given title.
void display_table_char(vector <vector<char>> matrix, const string &label, 
                   const bool use_letters = false) { 
  cout << label << endl; 
  int max_cell_width = 1; 
  cout << ' '; 
  for (size_t j = 0; j < matrix.size(); j++) { 
    cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A'); 
  } 
  cout << endl; 
  for (size_t i = 0; i < matrix.size(); i++) { 
    cout << static_cast<char>(i + 'A'); 
    for (size_t j = 0; j < matrix.size(); j++) { 
      cout << " " << setw(max_cell_width); 
      if (use_letters) { 
        cout << static_cast<char>(matrix[i][j] + 'A'); 
      } else { 
        cout << matrix[i][j]; 
      } 
    } 
    cout << endl; 
  } 
  cout << endl; 
} 

int main(int argc, const char *argv[]) {
    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    stringstream iss;
    try {
        //verify that the number of vertices inputted is valid
        getline(input_file, line);
        iss << line;
        int v;
        //if the number of vertices is invalid, print an error message
        if(!(iss>>v) || v<=0 || v>26){
                cerr << "Error: Invalid number of vertices '"<< line << "' on line 1." << endl;
                return 1;
        }

        //initialize the long int INF to represent infinity
        long INF = numeric_limits<long>::max();

        //initialize a vector of vectors as the distance matrix
        vector <vector<long>> distance_matrix;
        for(int i=0; i<v; i++){
            vector<long> vec;
            for(int j=0; j<v; j++){
              if(i==j){
                vec.push_back(0);
              }
              else{
                vec.push_back(INF);
              }
            }
            distance_matrix.push_back(vec);
        }

        //begin grabbing each line of edges from the file
        unsigned int line_number = 2;
        while (getline(input_file, line)) {
            iss.clear();
            istringstream ss(line);
            string word;
            long distance;
            int cnt=0;
            int i;
            int j;
            while(ss>>word){
                //verify the first vertex is valid
                if(cnt==0){
                    if(word.length()>1 || word.at(0)>64+v || word.at(0)<65){ //if it is not valid, print an error
                        cerr << "Error: Starting vertex '" << word << "' on line " << line_number << " is not among valid values A-"<<(char)(64+v)<<"." << endl;
                        return 1;
                    }
                    i = word.at(0)-65;
                }

                //verify the second vertex is valid
                if(cnt==1){
                    if(word.length()>1 || word.at(0)>64+v || word.at(0)<65){ //if it is not valid, print an error
                        cerr << "Error: Ending vertex '" << word << "' on line " << line_number << " is not among valid values A-"<<(char)(64+v)<<"." << endl;
                        return 1;
                    }
                    j = word.at(0)-65;
                }

                //verify the distance is valid
                if(cnt==2){
                    iss<<word;
                    if(!(iss>>distance) || distance<=0){ //if it is not valid, print an error
                        cerr << "Error: Invalid edge weight '"<<word<<"' on line "<<line_number<<"."<<endl;
                        return 1;
                    } 
                    distance_matrix[i][j]=distance;
                }
                cnt++;
            }
            //verify the line had all 3 arguements, no extras and not too few.
            if(cnt<3 || cnt>3){
                cerr << "Error: Invalid edge data '"<<line<<"' on line "<<line_number<<"." << endl;
                return 1;
            }
            ++line_number;
        }

        //print the distance matrix
        display_table(distance_matrix, "Distance matrix:");

        //initialize a matrix for the path lengths by creating a copy of the distance matrix.
        vector <vector<long>> lengths;
        for(int i=0; i<v; i++){
          vector<long> vec;
          for(int j=0; j<v; j++){
              vec.push_back(distance_matrix[i][j]);
          }
          lengths.push_back(vec);
        }

        //initialize a matrix to keep track of the paths taken.
        vector <vector<char>> paths;
        for(int i=0; i<v; i++){
            vector<char> vec;
            for(int j=0; j<v; j++){
                vec.push_back('-');
            }
            paths.push_back(vec);
        }

        //using Floyd's Algorithm, compute the path lengths matrix and the paths matrix
        for(size_t k=0; k<lengths.size(); k++)
        {
          for(size_t i=0; i<lengths.size(); i++)
          {
            for(size_t j=0; j<lengths.size(); j++){
              if(lengths[i][k]!=INF && lengths[k][j]!=INF){
                if(lengths[i][k]+lengths[k][j] < lengths[i][j]){
                  lengths[i][j]= lengths[i][k]+lengths[k][j];
                  paths[i][j]='A'+k;
                }
              }
            }
          }
        }

        //print the shortest path lengths matrix
        display_table(lengths, "Path lengths:");
        //print the matrix that keeps track of the paths taken
        display_table_char(paths, "Intermediate vertices:");
        
        //print every possible path
        for(int i=0; i<v; i++){
          for(int j=0; j<v; j++){
            cout << (char)('A' + i) << " -> " << (char)('A' + j) << ", distance: ";
            if(lengths[i][j]!=INF)
              cout << lengths[i][j] << ", path: ";
            else{
              cout << "infinity, path: none" << endl;
            }
            if(paths[i][j]=='-' && lengths[i][j]!=INF){
              if(i==j){
                cout << (char)('A' + i) << endl;
              }
              else{
                cout << (char)('A' + i) << " -> " << (char)('A' + j) << endl;
              }
            }
            if(paths[i][j]!='-'){
              cout << compute_paths(paths, i, j)<< (char)('A' + j) << endl;
            }
          }
        }
        

        // Don't forget to close the file.
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }
    return 0;
}
