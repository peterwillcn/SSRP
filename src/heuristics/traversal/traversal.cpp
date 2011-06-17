#include "traversal.h"

#include <vector>
#include <utility>
#include <cmath>

using namespace std;

#include "graphGroup.h"
#include "journeyInfo.h"
#include "treeSearch.h"

#define MAX_COMPUTATION 100

// Returns ceil(log_{base}(n))
int Ceilog(int base, int n) {
    return ceil(log10((long double)n) / log10((long double)base));
}

/*
 * Traversal Heuristic
 *
 * This heuristic represents the choices it can make of routing journeys in the graph with
 * a tree and then usees depth-bound search to try to perform a quick search of the tree.
 *
 * In traversal.cpp a macro MAX_COMPUTATIONS is defined. Changing this value allows you to control how
 * deep in the tree the heuristic searches.
 *
 */
graphGroup runTraversalHeuristic(const graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys) {

    // create the graph group
    graphGroup g;
    g.set(mainGraph.returnGraph(), listOfJourneys);

    // Initialize journeys
    vector<int> journeys(listOfJourneys.size());

    for(int i = 0; i < journeys.size(); i++)
        journeys[i] = i;

    vector<int> solution;

    int DEPTH_VALUE = max(1, Ceilog(journeys.size(), MAX_COMPUTATION));

    //cout << "Depth: " << DEPTH_VALUE << endl;

    treeNode* t = new treeNode(DEPTH_VALUE, journeys, g);
    {
        pair<int,vector<int> > val = t->search();
        t = t->findChild(val.second[0]);
        g.addJourneySP(val.second[0]);
        solution.push_back(val.second[0]);
        for(int i = 0; i < journeys.size(); i++) {
            if(journeys[i] == val.second[0]) {
                journeys.erase(journeys.begin()+i);
                break;
            }
        }
    }

    // At the beginning of the loop:
    // journeys contains a list of all the journey numbers that have yet to be routed.
    // solution contains the journeys that have been routed and in which order.
    // t points to the node that is about to be searched.
    for(int trialNum = 0; journeys.size() > 1; trialNum++) {
        if(t->numChildren() == 0) {
            break; // Do Nothing
        }
        else if(t->numChildren() == 1) {
            solution.push_back(t->journeyNumber());
            solution.push_back(t->child(0)->journeyNumber());
            break;
        }
        else {

            pair<int, vector<int> > val = t->search(DEPTH_VALUE);
            treeNode* oldT = t;
            for(int i = 0; i < oldT->numChildren(); i++) {
                if(oldT->child(i)->journeyNumber() == val.second[0]) {
                    t = oldT->child(i);
                }
                else {
                    delete oldT->child(i);
                }
            }
            g.addJourneySP(val.second[0]);
            solution.push_back(val.second[0]);
            for(int i = 0; i < journeys.size(); i++) {
                if(journeys[i] == val.second[0]) {
                    journeys.erase(journeys.begin()+i);
                    break;
                }
            }
        }
    }

    if(journeys.size() == 1) {
        solution.push_back(journeys[0]);
    }

    graphGroup soln;
    soln.set(mainGraph.returnGraph(), listOfJourneys);

    for(int i = 0; i < solution.size(); i++) {
        soln.addJourneySP(solution[i]);
    }

    return soln;

}