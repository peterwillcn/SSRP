#include "nashEquilib.h"

#include <vector>

using namespace std;

#include "graphGroup.h"
#include "journeyInfo.h"
#include "FWGroup.h"
#include "ioFunctions.h"
#include "debug.h"

/*
 * Nash Equilibrium
 *
 * This is the vanilla version of the nash equilibrium algorithm. Everything is
 * routed by their shortest paths, and then the nash equilibrium algorithm is
 * run on them.
 */
graphGroup runNashEquilibriumHeuristic(graphGroup mainGraph,
                                       const vector<journeyInfo>& listOfJourneys) {

    bool printGraphInfo = false;
    bool show_reroutings = false;
    int num_passes = 5;
    int journey_threshold = 3;
    bool coalition_one = false;
    bool outsider_one = false;

    vector< vector< floatWInf > > minSavings;
    vector< vector< floatWInf > > maxSavings;
    vector< vector< floatWInf > > averageSavings;
    string fileName;

    FWGroup FloydPaths;
    vector<int> journeysNum;

    for(int j = 0; j < listOfJourneys.size(); j++)
        journeysNum.push_back(listOfJourneys[j].journeyNum());

    FloydPaths.set(journeysNum, mainGraph);

    if(debug)
        output("Running tests...");

    if(printGraphInfo)
        printGraph(mainGraph);

    //route each journey by it's FW path
    for(int j = 0; j < listOfJourneys.size(); j++){
        mainGraph.addJourney(listOfJourneys[j].journeyNum(),
                             FloydPaths.returnPath(listOfJourneys[j].source(),
                                                   listOfJourneys[j].destination()));
    }

    return mainGraph;
}