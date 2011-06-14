#include "graphGroup.h"
#include "journeyInfo.h"
#include "treeSearch.h"
#include <vector>
#include <utility>
using namespace std;

graphGroup runTraversalHeuristic(const graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys) {

    // create the graph group
    graphGroup g;
    g.set(mainGraph.returnGraph(), listOfJourneys);

    // Initialize journeys
    vector<int> journeys(listOfJourneys.size());

    for(int i = 0; i < journeys.size(); i++)
        journeys[i] = i;

    vector<int> solution;

    treeNode* t = new treeNode(-1, 0, journeys, g);
    t = t->child(t->search(DEPTH_VALUE).second[0]);

    // t->print();

    // At the beginning of the loop:
    // journeys contains a list of all the journey numbers that have yet to be routed.
    // solution contains the journeys that have been routed and in which order.
    // t points to the node that is about to be searched.
    for(int trialNum = 0; journeys.size() > 1; trialNum++) {

        //cout << "Trial " << trialNum << ":\n";
        //cout << "Journeys: ";
        //outputVector(journeys);

        //cout << "Solution: ";
        //outputVector(solution);

        pair<int, vector<int> > val = t->search(DEPTH_VALUE);
        t = t->child(val.second[0]);
        g.addJourneySP(val.second[0]);
        solution.push_back(val.second[0]);
        for(int i = 0; i < journeys.size(); i++) {
            if(journeys[i] == val.second[0]) {
                journeys.erase(journeys.begin()+i);
                break;
            }
        }

    }

    solution.push_back(journeys[0]);
    g.addJourneySP(journeys[0]);

    return g;

}