#ifndef _TREE_SEARCH_H_
#define _TREE_SEARCH_H_

#include <utility>
#include "graphGroup.h"
#include <vector>
using namespace std;

class treeNode {
private:

    mutable vector<treeNode*> children;

    graphGroup& graph;

    vector<int> journeys;

    int journey;

    bool rootNode();

    treeNode(int depth,
             int journeyNum,
             vector<int> journeysNotRouted,
             graphGroup& associatedGraph,
             int DepthValue
            );

    void createUpToDepth(int depth) const;

    mutable int depthBelow;

    const int depthValue;

public:

    treeNode(int depth, vector<int> journeys, graphGroup& associatedGraph);

    ~treeNode();

    void print() const;

    int numChildren() const;

    treeNode* findChild(int journeyNumber);

    treeNode* child(int i);

    int journeyNumber() const;

    pair<int, vector<int> > search(int d = -1);
};

#endif
