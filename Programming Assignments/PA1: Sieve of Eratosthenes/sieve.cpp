/*******************************************************************************
 * Name: sieve.cpp
 * Author: Haig Emirzian
 * Date: 9/18/22
 * Description: Sieve of Eratosthenes (finds prime numbers up to and including the limit)
 * Pledge: I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

PrimesSieve::PrimesSieve(int limit):
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}

void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.

    const int max_prime_width = num_digits(max_prime_), primes_per_row = 80 / (max_prime_width + 1);
    int num_primes_ = count_num_primes();

    cout << "\n" << "Number of primes found: " << num_primes_ << endl;
    cout << "Primes up to " << limit_ << ":" << endl;

    if(num_primes_ < primes_per_row){
        int counter = 0;
        for(int i = 2; i <= limit_; i++){
            if(is_prime_[i] == true){
                cout << i;
                counter++;
                if(counter < num_primes_){
                    cout << " ";
                }
                }
                }
                } else{
                    int counter = 0;
                    int prime_count = 0;
                    for(int i = 2; i <= limit_; i++){
                        if(is_prime_[i] == true){
                            cout << setw(max_prime_width) << i;
                            counter++;
                            prime_count++;
                            if(prime_count == primes_per_row){
                                cout << "\n";
                                prime_count = 0;
                            } else if(counter < num_primes_){
                                cout << " ";
                            }
                        }
                    }
                }
            }

int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    int count = 0;
    for(int i = 2; i <= limit_; i++){
        if(is_prime_[i] == true){
            count++;
        }
    }    
    return count;
}

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    for(int i = 2; i <= limit_; i++){
        is_prime_[i] = true;
    }

    for(int i = 2; i < sqrt(limit_); i++){
        if(is_prime_[i] == true){
            for(int j = i*i; j < limit_ + 1; j += i){
                is_prime_[j] = false;
            }
        }
    }
    for(int i = limit_; i >=2; i--){
        if(is_prime_[i] == true){
            max_prime_ = i;
            break;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 0;
    while(num != 0){
        num = num / 10;
        count++;
    }
    return count;
}

int main() {

    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    PrimesSieve test = PrimesSieve(limit);
    test.display_primes();

    return 0;
}
