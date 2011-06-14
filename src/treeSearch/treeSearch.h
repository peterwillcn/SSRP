#ifndef _TREE_SEARCH_H_
#define _TREE_SEARCH_H_

#include <utility>
#include "graphGroup.h"
#include <vector>
using namespace std;

class treeNode {
private:

    treeNode* parent;

    int depth;

    vector<treeNode*> children;

    graphGroup& graph;

    vector<int> journeys;

    int journey;

public:

    treeNode(int journeyNum, int d, vector<int> journeysNotRouted, graphGroup& associatedGraph);

    ~treeNode();

    void print() const;

    int numChildren() const;

    treeNode* child(int i);

    pair<int, vector<int> > search(int d);
};

#endif