#include <utility>
#include "treeSearch.h"
#include "graphGroup.h"
#include <vector>

using namespace std;

bool treeNode::rootNode() {
    return journey == -1;
}

treeNode::treeNode(int journeyNum, vector<int> journeysNotRouted, graphGroup& associatedGraph)
    : journey(journeyNum), graph(associatedGraph) {
    // Do Nothing
    for(int i = 0; i < journeysNotRouted.size(); i++) {
        vector<int> temp = journeysNotRouted;
        temp.erase(temp.begin()+i);
        children.push_back(new treeNode(journeysNotRouted[i], temp, graph));
    }
}

treeNode::treeNode(vector<int> journeysNotRouted, graphGroup& associatedGraph)
    : journey(-1), graph(associatedGraph) {
    // Do Nothing
    for(int i = 0; i < journeysNotRouted.size(); i++) {
        vector<int> temp = journeysNotRouted;
        temp.erase(temp.begin()+i);
        children.push_back(new treeNode(journeysNotRouted[i], temp, graph));
    }
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
    return children.size();
}

treeNode* treeNode::findChild(int journeyNumber) {
    for(int i = 0; i < numChildren(); i++) {
        if(child(i)->journeyNumber() == journeyNumber)
            return child(i);
    }
    return NULL;
}

treeNode* treeNode::child(int i) {
    return children[i];
}

int treeNode::journeyNumber() const {
    return journey;
}

pair<int,vector<int> > treeNode::search(int d) {
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