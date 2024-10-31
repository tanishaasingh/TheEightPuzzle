#include <iostream>

#include "tree.h"

#include <vector>
#include <queue>
#include <unordered_set>
#include <cmath>
#include <algorithm>

using namespace std;

Tree::Tree(const std::vector<int>& initState, const std::vector<int>& goalState)
    : initialState(initState), goalState(goalState) {}