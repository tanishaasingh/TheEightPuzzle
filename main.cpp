#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include "tree.h"
#include "node.h"

using namespace std;

void uniformcostsearch( Tree& tree );              // implement search algorithms 
void ASTARmisplaced( /* tree*/ );                
void ASTAReuclideandistance( /*tree   */ ); 


int main(int argc,char* argv[]){

    int userpuzzlechoice; 
    vector<int> gamepuzzle(9); 
    int algchoice; 
   

    cout << "Welcome to tsing038 / 8 puzzle solver" << endl; 

    cout << "Type “1” to use a default puzzle, or “2” to enter your own puzzle." << endl; 

    cin >> userpuzzlechoice; 

    if (userpuzzlechoice == 1) {         // USER CHOOSES DEFAULT
        
       gamepuzzle = {1, 2, 3, 4, 0, 5, 7, 8, 6};     // GAMEPUZZLE now contains the default val
        
        cout << "Your puzzle set: ";              // display puzzle set 
            for (int i = 0; i < 9; ++i) {
                cout << gamepuzzle[i] << " ";
            }
        cout << endl;

    }

    else if (userpuzzlechoice == 2) {    // USER CHOOSES TO MAKE PUZZLE 

        cout << "Enter your puzzle, use a zero to represent the blank." << endl;

        cout << "Enter the first row, use space or tabs between numbers: ";

            for (int i = 0; i < 3; ++i) {
            cin >> gamepuzzle[i];    }
            

        cout << "Enter the second row: ";

            for (int i = 3; i < 6; ++i) {
            cin >> gamepuzzle[i];    }

        cout << "Enter the third row: ";

            for (int i = 6; i < 9; ++i) {
            cin >> gamepuzzle[i];   }
        

        cout << endl; 
        cout << "Your puzzle set: ";              // display puzzle set 
            for (int i = 0; i < 9; ++i) {
                cout << gamepuzzle[i] << " ";
            }
        cout << endl;
    }

    else {
        cout << "ERROR: WRONG INPUT -- RESTART PROGRAM" << endl; 
        return 0; 
    }
  

  // PUZZLE SET, CHOOSE ALGORITHM 

    cout << endl; 
    cout << "Enter your choice of algorithm" << endl; 
    cout << "1. Uniform Cost Search" << endl; 
    cout << "2. A* with the Misplaced Tile heuristic." << endl; 
    cout << "3. A* with the Euclidean distance heuristic." << endl; 
    cout << endl; 

    cin >> algchoice; 

    
    
    
    return 0;
}

void uniformcostsearch( Tree& tree ) {
    
} 