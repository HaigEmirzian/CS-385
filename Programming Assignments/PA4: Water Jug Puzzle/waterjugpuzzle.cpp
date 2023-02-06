/*******************************************************************************
 * Filename: waterjugpuzzle.cpp
 * Author  : Haig Emirzian and Wesley Nabo
 * Version : 1.0
 * Date    : October 17, 2022
 * Description: Executes the water jug puzzle
 * Pledge  : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <sstream>
#include <queue>
#include <stack>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << directions << " (" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

void BFS(int capA, int capB, int capC, int goalA, int goalB, int goalC) {
    int next_a, next_b, next_c, p_amount;
    State* intial2 =  new State(0,0,capC,"");

    //Initializes initial state
    State* initial = new State(0, 0, capC, "Initial state.");
    
    //Initializes queues and stack of type State*
    queue<State*> States;
    queue<State*> queue;    
    stack<State*> stack;
    delete intial2;

    //Pushes initial state to the queue
    queue.push(initial); 
    //Pushes initial state to the States queue
    States.push(initial);

    //Creates matrix for all states to be put in
    State* **table = new State**[capA + 1];  
    for(long int i =0; i < capA + 1; i++) {
        table[i]= new State*[capB + 1];   
        fill(table[i], table[i] + (capB + 1), nullptr); 
    }
    
    //Runs the algorithm
    while (!queue.empty()){
        //Initializes current to equal to the front of the queue
        State* current = queue.front();  
        State* copy = new State(current->a, current->b, current->c,"");
        copy->parent = current->parent;
        delete copy;
        
        
        //Base case: Checks to see if the current state is the inital state
        if((current->a == goalA) && (current->b == goalB) && (current->c == goalC)){
            //Puts the current state into the table
            table[goalA][goalB] = current;
            cout << initial->to_string() << endl;
            
            while(current->parent != nullptr){
                //Pushes current state to the stack
                stack.push(current);
                current = current->parent;   
            }
            
            while (!stack.empty()){
                //Ouputs the top of the string to the to_string method
                cout << stack.top()->to_string() << endl;
                stack.pop();
            }
            break;
            
        }

        //Checks to see if we visited the state in the table
        if(table[current->a][current->b] != nullptr){
            queue.pop();
            continue;

        } else{

            //C->A
            if(current->a != capA && current->c != 0){   
            
                ///Pouring process
                 next_a = current->a;
                 next_c = current->c;
                 next_b = current->b;
                 p_amount = 0;

                //uses while loop for 
                while(next_a < capA && next_c > 0){ //counts as the water pours 
                    next_a ++;
                    next_c --;
                    p_amount++;
                }

                //Initializes temporary state
                State* temp_state = new State(current->a, current->b, current->c, "initial");

                temp_state->parent = current; //sets parent of temp-state to the current state

                temp_state->a = next_a; //sets it to a
                temp_state->b = next_b; //sets it to b
                temp_state->c = next_c; //sets it to c


                //Determines if output is gallons or a gallon
                if(p_amount > 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallons from C to A.";
                }
                else if(p_amount == 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallon from C to A. ";

                }

                if (table[temp_state->a][temp_state->b] == nullptr){
                    //Pushes temp to queues
                   States.push(temp_state);
                   queue.push(temp_state);
                   
                }
                else{
                    delete temp_state; //deletes the temporary state
                }
                    
            }


            //C->B
            if(current->c != 0 && current->b != capB){       
                //Initializes temporary state
                State* temp_state = new State(current->a, current->b, current->c, "initial");

                //Pouring process
                next_a = current->a;
                 next_c = current->c;
                 next_b = current->b;
                 p_amount = 0;

                //uses while loop for 
                while(next_b < capB && next_c > 0){ //counts as the water pours 
                    next_b ++;
                    next_c --;
                    p_amount++;
                }

                temp_state->parent = current; //sets parent of temp-state to the current state

                temp_state->a = next_a; //sets it to a
                temp_state->b = next_b; //sets it to b
                temp_state->c = next_c; //sets it to c


                //Determines if output is gallons or a gallon
                if(p_amount > 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallons from C to B.";
                }
                else if(p_amount == 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallon from C to B. ";

                }
                
                if(table[temp_state->a][temp_state->b] == nullptr){
                    //Pushes temp to queues
                    States.push(temp_state);
                    queue.push(temp_state);
                    
                } else {
                    delete temp_state;
                }
            }  

            //A->B
            if(current->a != 0 && current->b != capB){   
        
                State* temp_state = new State(current->a, current->b, current->c, "initial");

                //Pouring process
                next_a = current->a;
                 next_c = current->c;
                 next_b = current->b;
                 p_amount = 0;

                //uses while loop for 
                while(next_b < capB && next_a > 0){ //counts as the water pours 
                    next_b ++;
                    next_a --;
                    p_amount++;
                }

                temp_state->parent = current; //sets parent of temp-state to the current state

                temp_state->a = next_a; //sets it to a
                temp_state->b = next_b; //sets it to b
                temp_state->c = next_c; //sets it to c


                //Determines if output is gallons or a gallon
                if(p_amount > 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallons from A to B.";
                }
                else if(p_amount == 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallon from A to B. ";

                }
                
                if(table[temp_state->a][temp_state->b] == nullptr){
                    //Pushes temp to queues
                    queue.push(temp_state);
                    States.push(temp_state);
                } else{
                    delete temp_state;
                }
            }  

            //B->A 
            if(current->b != 0 && current->a != capA){    
                //Initializes temporary state
                State* temp_state = new State(current->a, current->b, current->c, "initial");

                //Pouring process
                next_a = current->a;
                 next_c = current->c;
                 next_b = current->b;
                 p_amount = 0;

                //uses while loop for 
                while(next_a < capA && next_b > 0){ //counts as the water pours 
                    next_a ++;
                    next_b --;
                    p_amount++;
                }

                temp_state->parent = current; //sets parent of temp-state to the current state

                temp_state->a = next_a; //sets it to a
                temp_state->b = next_b; //sets it to b
                temp_state->c = next_c; //sets it to c


                //Determines if output is gallons or a gallon
                if(p_amount > 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallons from B to A.";
                }
                else if(p_amount == 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallon from B to A.";

                }
                
                if(table[temp_state->a][temp_state->b] == nullptr){
                    //Pushes temp to queues
                    States.push(temp_state);
                    queue.push(temp_state);
                    
                } else{
                    delete temp_state;
                }
            }

            //B->C
            if(current->b != 0 && current->c != capC){  

                State* temp_state = new State(current->a, current->b, current->c, "initial");

                //Pouring process
                next_a = current->a;
                 next_c = current->c;
                 next_b = current->b;
                 p_amount = 0;

                //uses while loop for 
                while(next_c < capC && next_b > 0){ //counts as the water pours 
                    next_c ++;
                    next_b --;
                    p_amount++;
                }

                temp_state->parent = current; //sets parent of temp-state to the current state

                temp_state->a = next_a; //sets it to a
                temp_state->b = next_b; //sets it to b
                temp_state->c = next_c; //sets it to c


                //Determines if output is gallons or a gallon
                if(p_amount > 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallons from B to C.";
                }
                else if(p_amount == 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallon from B to C. ";

                }
               
                if(table[temp_state->a][temp_state->b] == nullptr){
                    //if the value wasn't already explored, push to queue
                    States.push(temp_state);
                    queue.push(temp_state);

                    
                } else {
                    delete temp_state;
                }
            }

            //A->C
            if(current->a != 0 && current->c != capC){    
                State* temp_state = new State(current->a, current->b, current->c, "initial");

                //Pouring process
                 next_a = current->a;
                 next_c = current->c;
                 next_b = current->b;
                 p_amount = 0;

                //uses while loop for 
                while(next_c < capC && next_a > 0){ //counts as the water pours 
                    next_c ++;
                    next_a --;
                    p_amount++;
                }

                temp_state->parent = current; //sets parent of temp-state to the current state

                temp_state->a = next_a; //sets it to a
                temp_state->b = next_b; //sets it to b
                temp_state->c = next_c; //sets it to c


                //Determines if output is gallons or a gallon
                if(p_amount > 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallons from A to C.";
                }
                else if(p_amount == 1 && p_amount != 0){
                    temp_state->directions = "Pour " + to_string(p_amount) + " gallon from A to C.";

                }
            
                if(table[temp_state->a][temp_state->b] == nullptr){
                    //if the value wasn't already explored, push to queue
                    States.push(temp_state);
                    queue.push(temp_state);
                    
                } else{
                    delete temp_state;
                }
            }
            table[current->a][current->b] = current;
            queue.pop();      
        }
    }

    //If there are still null pointers in the matrx,
    //then print out "No solution."
    if(table[goalA][goalB] == nullptr){
        cout << "No solution." << endl;
    }

    //Utilizes a for loop to delete table
    for(int i = 0; i < capA + 1; i++) {
        delete [] table[i];
    }
    delete [] table;

    //Pops and deletes queue
    while(!States.empty()){
        State* state_holder = States.front();
        States.pop();
        delete state_holder;
    }
}


int main(int argc, char * const argv[]){

    stringstream iss;
    int capA, capB, capC, goalA, goalB, goalC;

    //Checks to see if the arguments are the right amount
    if(argc != 7){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" <<endl;
        return 1;
    }

    //Loads second element into iss
    iss.str(argv[1]);   

    //Checks to see if capA is a positive integer
    if(!(iss >> capA) || capA <= 0){ 
		cerr << "Error: Invalid capacity '" << argv[1] << "' for jug A." << endl;
		return 1;
	}   

    iss.clear();

    //Loads third element into iss
    iss.str(argv[2]);   

    //Checks to see if capB is a positive integer
    if(!(iss >> capB) || capB <= 0){ 
		cerr << "Error: Invalid capacity '"<< argv[2] <<"' for jug B." << endl;
		return 1;
	}   

    iss.clear();

    //Loads fourth element in iss
    iss.str(argv[3]);   

    //Checks to see if capC is a positive integer
    if(!(iss >> capC) || capC <= 0){ 
		cerr << "Error: Invalid capacity '"<< argv[3] <<"' for jug C." << endl;
		return 1;
	}   

    iss.clear();


    //Loads fifth element in iss
    iss.str(argv[4]);   

    //Checks to see if goalA is a positive integer
    if(!(iss >> goalA) || goalA < 0){ 
		cerr << "Error: Invalid goal '"<< argv[4] <<"' for jug A." << endl;
		return 1;
	}   

    iss.clear();

    //Loads sixth element in iss
    iss.str(argv[5]);   

    //Checks to see if goalB is a positive integer
    if(!(iss >> goalB) || (goalB < 0)){ 
		cerr << "Error: Invalid goal '"<< argv[5] <<"' for jug B." << endl;
		return 1;
	}   

    iss.clear();

    //Loads seventh element in iss
    iss.str(argv[6]);   

    if(!(iss >> goalC) || (goalC < 0)){ 
		cerr << "Error: Invalid goal '"<< argv[6] <<"' for jug C." << endl;
		return 1;
	}   

    iss.clear();

    //Checks to see if goal exceeds capacity
    if(capA < goalA){
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    //Checks to see if goal exceeds capacity
    else if(capB < goalB){
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    //Checks to see if goal exceeds capacity
    else if(capC < goalC){
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }

    //Checks to see if the total goals equals capC
    if(capC != goalA + goalB + goalC){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." <<endl;
        return 1;
    } 

    State state_goal = State(goalA,goalB,goalC, ""); //makes goal state to check 
    BFS(capA, capB, capC, state_goal.a, state_goal.b, state_goal.c); //implements waterjug
    return 0;
}
