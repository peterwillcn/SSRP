#ifndef _TREE_SEARCH_H_
#define _TREE_SEARCH_H_

#include <utility>
#include "graphGroup.h"
#include <vector>
using namespace std;

class treeNode {
private:

    treeNode* parent;

    vector<treeNode*> children;

    graphGroup& graph;

    vector<int> journeys;

    int journey;

    bool rootNode();

    treeNode(int journeyNum, vector<int> journeysNotRouted, graphGroup& associatedGraph);

public:

    treeNode(vector<int> journeys, graphGroup& associatedGraph);

    ~treeNode();

    void print() const;

    int numChildren() const;

    treeNode* findChild(int journeyNumber);

    treeNode* child(int i);

    int journeyNumber() const;

    pair<int, vector<int> > search(int d);
};

#endif