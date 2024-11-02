#include <iostream>
#include <string>
#include <vector>
#include <algorithm> 
#include "tree.h"
#include "node.h"

using namespace std;

void uniformcostsearch( Tree& tree );              // implement search algorithms 
void ASTARmisplaced( Tree& tree);                
void ASTAReuclideandistance( Tree& tree ); 

vector <vector<int> > operatorMoves( const vector<int>& curstate ) {           //operator 

    vector<vector<int>> nextNode;
    vector<pair<int, int>> OP = {
        {-1, 0}, 
        {1, 0}, 
        {0, -1}, 
        {0, 1}                  };

    int blank = find(curstate.begin(), curstate.end(), 0) - curstate.begin();

    int prow = blank / 3, pcolumn = blank % 3;

    
    for (size_t i = 0; i < OP.size(); ++i) {
        
        int targetrow = prow + OP[i].first;                   // access nodes using index 
        int targetcolumn = pcolumn + OP[i].second;

        if (targetrow >= 0 && targetcolumn >= 0 && targetrow < 3 && targetcolumn < 3) {

            vector<int> nextinline = curstate;
            int targetIndex = targetrow * 3 + targetcolumn;

            nextinline[blank] = nextinline[targetIndex];
            nextinline[targetIndex] = 0;
               //swap(nextinline[blank], nextinline[targetrow * 3 + targetcolumn]);
            nextNode.push_back(nextinline);

        }
    }
    return nextNode;
}

int main(int argc,char* argv[]){

    int userpuzzlechoice; 
    vector<int> gamepuzzle(9); 
    int algchoice; 
   

    cout << "Welcome to tsing038 / 8 puzzle solver" << endl; 

    cout << "Type “1” to use a default puzzle, or “2” to enter your own puzzle." << endl; 

    cin >> userpuzzlechoice; 

    if (userpuzzlechoice == 1) {                  // USER CHOOSES DEFAULT
        
       gamepuzzle = {0,1,2,4,5,3,7,8,6};          // GAMEPUZZLE now contains the default val
        
        cout << "Your puzzle set: ";              // display puzzle set 
            for (int i = 0; i < 9; ++i) {
                cout << gamepuzzle[i] << " ";
            }
        cout << endl;

    }

    else if (userpuzzlechoice == 2) {             // USER CHOOSES TO MAKE PUZZLE 

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

    if (algchoice == 1) {
        Tree tree(gamepuzzle, {1, 2, 3, 4, 5, 6, 7, 8, 0}); // goal state within function call
        uniformcostsearch(tree);
    } 
    else if (algchoice == 2) {
        Tree tree(gamepuzzle, {1, 2, 3, 4, 5, 6, 7, 8, 0}); 
        ASTARmisplaced(tree);
    }  
    else if (algchoice == 3) {
        Tree tree(gamepuzzle, {1, 2, 3, 4, 5, 6, 7, 8, 0}); 
        ASTAReuclideandistance(tree);
    }  


    
    return 0;
}

struct nodecomp {

    bool operator()(Node* a, Node* b) const {

        return a->f > b->f; 

    }
};

// search algorithm implementation 

void uniformcostsearch(Tree& tree) {

    unordered_set<string> expanded;
    priority_queue <Node*, vector<Node*>, nodecomp> frontier; 
    

    Node* begnode = new Node(tree.initialState);

    begnode->g = 0;  

    begnode->misplacedTiles(tree.goalState); 

    frontier.push(begnode);

    while (!frontier.empty()) {

        Node* curnode = frontier.top();
        frontier.pop();

        if (curnode->isGoal(tree.goalState)) {
            vector<Node*> nodevals;
            cout << endl; 
            cout << "Goal!!!" << endl;
            cout << endl; 
            
            
            for (Node* node = curnode; node != nullptr; node = node->parent) {

                nodevals.push_back(node);

            }
            reverse(nodevals.begin(), nodevals.end());

            for (const auto& node : nodevals) {

                for (int val : node->state) {
                    cout << val << " ";
                }
                cout << endl;

            }
            return;

        }

        string state = curnode->stringState();

        if (expanded.find(state) != expanded.end()) continue;

        expanded.insert(state);

        vector<vector<int>> inLine = operatorMoves(curnode->state);
        
        for (size_t i = 0; i < inLine.size(); ++i) {
            vector<int> succ = inLine[i]; 
            Node* nextNode = new Node(succ, curnode);
            nextNode->g = curnode->g + 1; 
            nextNode->misplacedTiles(tree.goalState); 

    if (expanded.find(nextNode->stringState()) == expanded.end()) {
        frontier.push(nextNode);
    }
        }
    }
    cout << "No solution found." << endl;
}

void ASTARmisplaced(Tree& tree) {

    unordered_set<string> expanded;
    priority_queue<Node*, vector<Node*>, nodecomp> frontier; 
    

    Node* begnode = new Node(tree.initialState);
    begnode->g = 0;  
    begnode->misplacedTiles(tree.goalState); 
    frontier.push(begnode);

    while (!frontier.empty()) {
        Node* curnode = frontier.top();
        frontier.pop();

        
        if (curnode->isGoal(tree.goalState)) {

            cout << endl; 
            cout << "Goal!!!" << endl;
            cout << endl;
          
            vector<Node*> nodevals;
            for (Node* node = curnode; node != nullptr; node = node->parent) {

                nodevals.push_back(node);

            }
            reverse(nodevals.begin(), nodevals.end());

            for (const auto& node : nodevals) {
                for (int val : node->state) {
                    cout << val << " ";
                }
                cout << endl;
            }
            return;
        }

        string statek = curnode->stringState();

        if (expanded.find(statek) != expanded.end()) continue;
        expanded.insert(statek);

        vector<vector<int>> inLine = operatorMoves(curnode->state);
         for (size_t i = 0; i < inLine.size(); ++i) {
            vector<int> succ = inLine[i]; 
            Node* nextNode = new Node(succ, curnode);
            nextNode->g = curnode->g + 1; 
            nextNode->misplacedTiles(tree.goalState); 

            if (expanded.find(nextNode->stringState()) == expanded.end()) {
                frontier.push(nextNode);
            }
        }
    }


    cout << "No solution found." << endl;
}


void ASTAReuclideandistance( Tree& tree ) {

    priority_queue<Node*, vector<Node*>, nodecomp> frontier; 
    unordered_set<string> expanded;

    Node* begnode = new Node(tree.initialState);

    begnode->g = 0;

    begnode->euclideanDistance(tree.goalState);



    frontier.push(begnode);

    int nodesExpanded = 0;

    while (!frontier.empty()) {
        Node* current = frontier.top();
        frontier.pop();

        if (current->isGoal(tree.goalState)) {
            cout << endl; 
            cout << "Goal!!!" << endl;
            cout << endl; 
            cout << "To solve this problem the search algorithm expanded a total of " << nodesExpanded << " nodes." << endl;

            
            vector<Node*> nodevals;
            for (Node* node = current; node != nullptr; node = node->parent) {
                nodevals.push_back(node);
            }
            reverse(nodevals.begin(), nodevals.end());
            for (const auto& node : nodevals) {
                for (int val : node->state) {
                    cout << val << " ";
                }
                cout << endl;
            }

    
            for (Node* node : nodevals) {
                delete node;
            }
            return;
        }

        
        string statek = current->stringState();
        if (expanded.find(statek) != expanded.end()) {
            delete current; 
        }

        expanded.insert(statek);
        nodesExpanded++;

     
        cout << "The best state to expand with g(n) = " << current->g << " and h(n) = " << current->h << ": " << endl;
        for (int val : current->state) {
            cout << val << " ";

        }

        cout << endl;

        vector<vector<int>> inLine = operatorMoves(current->state);
        
        for (const auto& succ : inLine) {
            Node* nextNode = new Node(succ, current);
            nextNode->g = current->g + 1;
            nextNode->euclideanDistance(tree.goalState); 

           

            if (expanded.find(nextNode->stringState()) == expanded.end()) {
                frontier.push(nextNode);
            } else {
                delete nextNode; 
            }
        }
        delete current; 
        
    }
    cout << "No solution found." << endl;
}