#ifndef __NODE_H__
#define __NODE_H__
#include <iostream>
#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;
class Node {
    public:
        vector <int> state ;  // cur state of puzzle 
        Node* parent;       // ptr to parent 
        int g;              // cost from initial node 
        int h;              // heuristic cost to goal
        int f;              // (g+h) total cost 

        Node(const vector<int>& state, Node *parent = nullptr); 

        bool isGoal(const vector<int>&goal) const; 

        void misplacedTiles(const vector<int>& goal); 

        void euclideanDistance(const vector<int>& goal);

        string stringState() const; 

};

#endif