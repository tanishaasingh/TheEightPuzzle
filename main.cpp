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

// search algorithm implementation 

void uniformcostsearch(Tree& tree) {
    // Priority queue for the frontier, using a custom comparator
    auto cmp = [](Node* a, Node* b) { return a->f > b->f; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> frontier(cmp);
    unordered_set<string> explored;

    Node* startNode = new Node(tree.initialState);
    startNode->g = 0;  // Cost from the initial node
    startNode->misplacedTiles(tree.goalState); // Calculate h for start node
    frontier.push(startNode);

    while (!frontier.empty()) {
        Node* current = frontier.top();
        frontier.pop();

        // Check if the current node is the goal
        if (current->isGoal(tree.goalState)) {
            cout << endl; 
            cout << "Goal!!!" << endl;
            cout << endl; 
            // Backtrack to print the solution if needed
            vector<Node*> path;
            for (Node* node = current; node != nullptr; node = node->parent) {
                path.push_back(node);
            }
            reverse(path.begin(), path.end());
            for (const auto& node : path) {
                for (int val : node->state) {
                    cout << val << " ";
                }
                cout << endl;
            }
            return;
        }

        string state_key = current->stringState();

        if (explored.find(state_key) != explored.end()) continue;
        explored.insert(state_key);

        vector<vector<int>> successors = operatorMoves(current->state);
        for (const auto& succ : successors) {
            Node* nextNode = new Node(succ, current);
            nextNode->g = current->g + 1; // Increment cost
            nextNode->misplacedTiles(tree.goalState); // Calculate h

            if (explored.find(nextNode->stringState()) == explored.end()) {
                frontier.push(nextNode);
            }
        }
    }
    cout << "No solution found." << endl;
}

void ASTARmisplaced(Tree& tree) {
   auto cmp = [](Node* a, Node* b) { return a->f > b->f; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> frontier(cmp);
    unordered_set<string> explored;

    Node* startNode = new Node(tree.initialState);
    startNode->g = 0;  // Cost from the initial node
    startNode->misplacedTiles(tree.goalState); // Calculate h for start node
    frontier.push(startNode);

    while (!frontier.empty()) {
        Node* current = frontier.top();
        frontier.pop();

        // Check if the current node is the goal
        if (current->isGoal(tree.goalState)) {
            cout << endl; 
            cout << "Goal!!!" << endl;
            cout << endl;
            // Backtrack to print the solution if needed
            vector<Node*> path;
            for (Node* node = current; node != nullptr; node = node->parent) {
                path.push_back(node);
            }
            reverse(path.begin(), path.end());
            for (const auto& node : path) {
                for (int val : node->state) {
                    cout << val << " ";
                }
                cout << endl;
            }
            return;
        }

        string state_key = current->stringState();

        if (explored.find(state_key) != explored.end()) continue;
        explored.insert(state_key);

        vector<vector<int>> successors = operatorMoves(current->state);
        for (const auto& succ : successors) {
            Node* nextNode = new Node(succ, current);
            nextNode->g = current->g + 1; // Increment cost
            nextNode->misplacedTiles(tree.goalState); // Calculate h

            if (explored.find(nextNode->stringState()) == explored.end()) {
                frontier.push(nextNode);
            }
        }
    }
    cout << "No solution found." << endl;
}


void ASTAReuclideandistance( Tree& tree ) {
  auto cmp = [](Node* a, Node* b) { return a->f > b->f; };
    priority_queue<Node*, vector<Node*>, decltype(cmp)> frontier(cmp);
    unordered_set<string> explored;

    Node* startNode = new Node(tree.initialState);
    startNode->g = 0;
    startNode->euclideanDistance(tree.goalState);
    frontier.push(startNode);

    int nodesExpanded = 0;

    while (!frontier.empty()) {
        Node* current = frontier.top();
        frontier.pop();

        // Check if the current node is the goal
        if (current->isGoal(tree.goalState)) {
            cout << endl; 
            cout << "Goal!!!" << endl;
            cout << endl; 
            cout << "To solve this problem the search algorithm expanded a total of " << nodesExpanded << " nodes." << endl;

            // Backtrack to print the solution
            vector<Node*> path;
            for (Node* node = current; node != nullptr; node = node->parent) {
                path.push_back(node);
            }
            reverse(path.begin(), path.end());
            for (const auto& node : path) {
                for (int val : node->state) {
                    cout << val << " ";
                }
                cout << endl;
            }

            // Free all nodes in the path
            for (Node* node : path) {
                delete node;
            }
            return;
        }

        // Check if the state has already been explored
        string state_key = current->stringState();
        if (explored.find(state_key) != explored.end()) {
            delete current; // Free memory of the current node
            continue;
        }

        explored.insert(state_key);
        nodesExpanded++;

        // Print the current node's g(n) and h(n)
        cout << "The best state to expand with g(n) = " << current->g << " and h(n) = " << current->h << ": " << endl;
        for (int val : current->state) {
            cout << val << " ";
        }
        cout << endl;

        vector<vector<int>> successors = operatorMoves(current->state);
        for (const auto& succ : successors) {
            Node* nextNode = new Node(succ, current);
            nextNode->g = current->g + 1; // Increment cost
            nextNode->euclideanDistance(tree.goalState); // Calculate h

            // Check if this state is already explored
            if (explored.find(nextNode->stringState()) == explored.end()) {
                frontier.push(nextNode);
            } else {
                delete nextNode; // Free memory if the state has already been explored
            }
        }
        delete current; // Free memory of the current node
    }
    cout << "No solution found." << endl;
}