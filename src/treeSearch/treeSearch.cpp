#include <utility>
#include "treeSearch.h"
#include "graphGroup.h"
#include <vector>

using namespace std;

bool treeNode::rootNode() {
    return journey == -1;
}

treeNode::treeNode(int depth,
                   int journeyNum,
                   vector<int> journeysNotRouted,
                   graphGroup& associatedGraph,
                   int DepthValue
                  )
    : journey(journeyNum),
      journeys(journeysNotRouted),
      graph(associatedGraph),
      depthValue(DepthValue),
      depthBelow(0)
{
    //cout << "Creating node for " << journeyNum << " at depth " << depth << endl;
    createUpToDepth(depth);
}

void treeNode::createUpToDepth(int depth) const {

    //cout << "Creating up to depth: " << depth << endl;

    depth = min(depth,int(journeys.size()));

    // If we've created past the depth, quit.
    if(depth < depthBelow) {
        //cout << "depth (" << depth << ") < depthBelow (" << depthBelow << ")\n";
        return;
    }

    // Otherwise, we need to create something past our leaves.
    if(depth <= 0) {
        depthBelow = 0;
        return;
    }

    // If we're not at a leaf
    if(depthBelow != 0)
    {
        // Have our children create down to the depth-1
        for(int i = 0; i < children.size(); i++)
        {
            children[i]->createUpToDepth(depth-1);
        }
    }

    // If we are at a leaf and we need to create more nodes
    else
    {
        // Then create new nodes for our children,
        // Recursively having them create down to the depth-1
        for(int i = 0; i < journeys.size(); i++)
        {
            vector<int> temp = journeys;
            temp.erase(temp.begin()+i);
            children.push_back(new treeNode(depth-1, journeys[i], temp, graph, depthValue));
        }
    }

    depthBelow = depth;
}

treeNode::treeNode(int depth,
                   vector<int> journeysNotRouted,
                   graphGroup& associatedGraph)
    : journey(-1),
      journeys(journeysNotRouted),
      graph(associatedGraph),
      depthValue(depth),
      depthBelow(0)
{
    //cout << "Creating root node at depth " << depth << endl;
    createUpToDepth(depth);
}

treeNode::~treeNode() {
    for(int i = 0; i < children.size(); i++) {
        delete children[i];
    }
}

void treeNode::print() const {
    cout << "( " << journey << " ";
    if(children.size() > 0) {
        cout << "{ ";
        for(int i =0 ; i < children.size(); i++) {
            children[i]->print();
            if(i < children.size()-1)
                cout << ", ";
        }
        cout << "} ";
    }
    cout << ") ";
}

int treeNode::numChildren() const {
    if(children.size() == 0 && journeys.size() > 0)
        createUpToDepth(1);
    return children.size();
}

treeNode* treeNode::findChild(int journeyNumber) {
    if(children.size() == 0 && journeys.size() > 0)
        createUpToDepth(1);
    for(int i = 0; i < numChildren(); i++) {
        if(child(i)->journeyNumber() == journeyNumber)
            return child(i);
    }
    return NULL;
}

treeNode* treeNode::child(int i) {
    if(children.size() == 0 && journeys.size() > 0)
        createUpToDepth(1);
    return children[i];
}

int treeNode::journeyNumber() const {
    return journey;
}

pair<int,vector<int> > treeNode::search(int d) {
    // First fix the default perameter
    if(d == -1)
        d = depthValue;

    //cout << "Searching to depth " << d << endl;

    // Then check to see if we have to create more of the tree
    if(d > depthBelow && d != 0)
        createUpToDepth(d);
    // Base case:
    //          d == 0
    //          return < 0, < journey > >
    // Recursive case:
    //          find min cost of the children
    //          return it's search result with our journey preappended to it.
    if(numChildren() == 1) {
        int cost;
        graph.addJourneySP(child(0)->journeyNumber());
        cost = graph.totalSharedCost().value();
        graph.removeJourney(child(0)->journeyNumber());

        return pair<int,vector<int> >(cost, vector<int>(1, child(0)->journeyNumber()));
    }
    if(d == 0) {
        int bestCost;
        int bestChild;
        for(int i = 0; i < numChildren(); i++) {
            graph.addJourneySP(child(i)->journeyNumber());
            if(graph.totalSharedCost() < bestCost || i == 0) {
                bestCost = graph.totalSharedCost().value();
                bestChild = child(i)->journeyNumber();
            }
            graph.removeJourney(child(i)->journeyNumber());
        }

        return pair<int,vector<int> >(bestCost, vector<int>(1, bestChild));
    }
    else {
        int bestCost;
        vector<int> bestPath;
        for(int i = 0; i < numChildren(); i++) {
            graph.addJourneySP(child(i)->journeyNumber());
            pair<int,vector<int> > temp = child(i)->search(d-1);
            if(temp.first < bestCost || i == 0) {
                bestCost = temp.first;
                bestPath = temp.second;
            }
            graph.removeJourney(child(i)->journeyNumber());
        }

        return pair<int,vector<int> >(bestCost, bestPath);
    }
}