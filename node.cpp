#include <iostream>
#include "node.h"
//#include "tree.h"

#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;

Node::Node(const vector<int>& initialState, Node *parent) :
        state(initialState), 
        parent(parent), 
        g(0),
        h(0),
        f(0)                                 
    {}


bool Node::isGoal(const vector<int>& goal) const {

    return state == goal;
    
    }

void Node::misplacedTiles(const vector<int>& goal) {
    h = 0;
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] != goal[i] && state[i] != 0) {
            h++;
        }
    }
    f = g + h;
}

void Node::euclideanDistance(const std::vector<int>& goal) {
    h = 0;
    for (size_t i = 0; i < state.size(); ++i) {
        if (state[i] != 0) {
            int targetX = (goal[i] - 1) / 3;
            int targetY = (goal[i] - 1) % 3;
            int currentX = i / 3;
            int currentY = i % 3;
            h += abs(targetX - currentX) + abs(targetY - currentY);
        }
    }
    f = g + h;
}

string Node::stringState() const {
    std::string result;
    for (int num : state) {
        result += std::to_string(num);
    }
    return result;
}


