#include "shortestPath.h"

#include <vector>

using namespace std;

#include "graphGroup.h"
#include "journeyInfo.h"
#include "FWGroup.h"

/*
 * Shortest Path
 *
 * This is the basis of comparison for our other algorithms. It routes things
 * by their shortest paths.
 */
graphGroup runShortestPathHeuristic(graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys) {
    //output("Running Shortest Path Heuristic");

    floatWInf final_total_cost(0);
    FWGroup FloydPaths;
    vector<int> journeysNum;

    for(unsigned j = 0; j < listOfJourneys.size(); j++)
        journeysNum.push_back(listOfJourneys[j].journeyNum());

    FloydPaths.set(journeysNum, mainGraph);

    //route each journey by it's FW path
    for(unsigned j = 0; j < listOfJourneys.size(); j++){
        mainGraph.addJourney(listOfJourneys[j].journeyNum(),
                             FloydPaths.returnPath(listOfJourneys[j].source(),
                                                   listOfJourneys[j].destination()));
    }

    return mainGraph;
}
