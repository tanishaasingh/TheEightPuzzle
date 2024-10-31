#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <vector>

using namespace std;

class Tree {
public:
    vector<int> initialState;  // The starting state of the puzzle
    vector<int> goalState;      // The goal state of the puzzle

    // Constructor
    Tree (const vector<int>& initState, const vector<int>& goalState);
};

#endif 