#include <iostream>
#include <string>
#include <algorithm> 

using namespace std;

int main(int argc,char* argv[]){

    int userpuzzlechoice; 
    int gamepuzzle[9] = {}; 
    int puzzle1[] = {1, 2, 3, 4, 0, 5, 7, 8, 6};

    cout << "Welcome to tsing038 / 8 puzzle solver" << endl; 

    cout << "Type “1” to use a default puzzle, or “2” to enter your own puzzle." << endl; 

    cin >> userpuzzlechoice; 

    if (userpuzzlechoice == 1) {         // USER CHOOSES DEFAULT
        
        copy(puzzle1, puzzle1 + 9, gamepuzzle);    // GAMEPUZZLE now contains the same values as PUZZLE 1
        
        cout << "Your puzzle set: ";              // display puzzle set 
            for (int i = 0; i < 9; ++i) {
                cout << gamepuzzle[i] << " ";
            }
        cout << endl;

    }
    else if (userpuzzlechoice == 2) {    // USER CHOOSES TO MAKE PUZZLE 
        cout << "test 1" << endl; 
    }
    else {
        cout << "ERROR: WRONG INPUT -- RESTART PROGRAM" << endl; 
        return 0; 
    }
  

   /* Type “1” to use a default puzzle, or “2” to enter your own puzzle.
2
Enter your puzzle, use a zero to represent the blank
Enter the first row, use space or tabs between numbers 1 2 3
Enter the second row, use space or tabs between numbers 4 8 0
Enter the third row, use space or tabs between numbers 7 6 5*/

    
    
    
    
    return 0;
}