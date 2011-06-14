#include <utility>
#include "treeSearch.h"
#include "graphGroup.h"
#include <vector>

using namespace std;

treeNode::treeNode(int journeyNum, int d, vector<int> journeysNotRouted, graphGroup& associatedGraph)
    : journey(journeyNum), depth(d), journeys(journeysNotRouted), graph(associatedGraph) {
    // Do Nothing
    for(int i = 0; i < journeys.size(); i++) {
        vector<int> temp = journeys;
        temp.erase(temp.begin()+i);
        children.push_back(new treeNode(journeys[i], d+1, temp, graph));
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

treeNode* treeNode::child(int i) {
    return children[i];
}

pair<int,vector<int> > treeNode::search(int d) {
    pair<int,vector<int> > retVal;
    //print(); cout << endl;
    // Recursive function
    // Base case:
    //          d == 0
    //          return < 0, < journey > >
    // Recursive case:
    //          find min cost of the children
    //          return it's search result with our journey preappended to it.
    if(journey != -1)
        graph.addJourneySP(journey);
    if(d == 0 || children.size() == 0) {
        if(journey == -1)
            retVal = pair<int,vector<int> >(-1, vector<int>());
        else
            retVal = pair<int,vector<int> >(graph.totalSharedCost().value(),
                                            vector<int>(1, journey));
    }
    else {
        int bestCost;
        vector<int> bestPath;
        for(int i = 0; i < children.size(); i++) {
            pair<int,vector<int> > temp = children[i]->search(d-1);
            if(temp.first < bestCost || i == 0) {
                bestCost = temp.first;
                bestPath = temp.second;
            }
        }

        // If we aren't the root node
        if(journey != -1)
            // Preappend our journey number
            bestPath.insert(bestPath.begin(), journey);
        retVal = pair<int, vector<int> >(bestCost, bestPath);
    }
    if(journey != -1)
        graph.removeJourney(journey);
    return retVal;
}