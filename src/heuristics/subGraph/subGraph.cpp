#include "subGraph.h"

#include <vector>
#include <limits.h>

using namespace std;

#include "ioFunctions.h"
#include "graphGroup.h"
#include "journeyInfo.h"
#include "basicEdgeGroup.h"

/*
 * Sub-Graph heuristic
 *
 * This is a theoretical algorithm used to prove statistically that there is
 * always a nash equilibrium in certain types of graphs. This algorithm does
 * considerably worse than most other algorithms, and so is not in use.
 */
graphGroup subGraphHeuristicHelper(const graphGroup& mainGraph, const vector<journeyInfo>& listOfJourneys, int startPoint) {
    basicEdgeGroup subGraph;
    subGraph.setUndirected();
    graphGroup newGraph;
    subGraph.setN(mainGraph.returnN());

    vector<int> startPoints(listOfJourneys.size());
    vector<int> midPoints(listOfJourneys.size());
    vector<int> endPoints(listOfJourneys.size());

    // Find the endpoints
    for(int i = 0; i < listOfJourneys.size(); i++) {
        startPoints[i] = listOfJourneys[i].source();
        endPoints[i] = listOfJourneys[i].destination();
    }

    for(int i = 0; i < listOfJourneys.size(); i++) {
        path p = mainGraph.findSP(endPoints[i], endPoints[(i+1)%listOfJourneys.size()]);

        midPoints[i] = p.getElement(p.length()/2);
    }

    // Now we have the mid points, the start point, and the ending points for all the journeys.
    // We can start to reduce the graph.

    for(int i = 0; i < listOfJourneys.size(); i++) {
        path p = mainGraph.findSP(endPoints[i], midPoints[i]);

        //cout << "Adding edge (" << endPoints[i] << ", " << midPoints[i] << ", " << p.cost() << ")\n";
        subGraph.addEdge(endPoints[i], midPoints[i], p.cost());
        subGraph.addEdge(midPoints[i], endPoints[i], p.cost());

        p = mainGraph.findSP(midPoints[i], endPoints[(i+1)%listOfJourneys.size()]);

        //cout << "Adding edge (" << midPoints[i] << ", " << endPoints[(i+1)%listOfJourneys.size()] << ", " << p.cost() << ")\n";
        subGraph.addEdge(midPoints[i], endPoints[(i+1)%listOfJourneys.size()], p.cost());
        subGraph.addEdge(endPoints[(i+1)%listOfJourneys.size()], midPoints[i], p.cost());
    }

    for(int i = 0; i < midPoints.size(); i++) {
        path p = mainGraph.findSP(startPoint, midPoints[i]);

        //cout << "Adding edge (" << startPoint << ", " << midPoints[i] << ", " << p.cost() << ")\n";
        subGraph.addEdge(startPoint, midPoints[i], p.cost());
        subGraph.addEdge(midPoints[i], startPoint, p.cost());
    }

    for(int i = 0; i < startPoints.size(); i++) {
        path p = mainGraph.findSP(startPoints[i], startPoint);

        subGraph.addEdge(startPoints[i], startPoint, p.cost());
        subGraph.addEdge(startPoint, startPoints[i], p.cost());
    }

    newGraph.set(subGraph, listOfJourneys);

    for(int i = 0; i < listOfJourneys.size(); i++) {
        newGraph.addJourneySP(i);
        newGraph.refindSharedCosts();
    }

    return newGraph;
}

graphGroup runSubGraphHeuristic(const graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys) {
    //output("Running Subgraph Heuristic");

    if(mainGraph.directed()) {
        output("Warning: this heuristic has not been tested with directed graphs");
    }

    int bestStart = 0;
    int bestCost = INT_MAX;
    for(int startPoint = 0; startPoint < mainGraph.returnN(); startPoint++) {

        graphGroup g = subGraphHeuristicHelper(mainGraph, listOfJourneys, startPoint);
        int cost = 0;
        for(int i = 0; i < listOfJourneys.size(); i++)
            cost += g.returnSharedCost(i).value();

        if(cost < bestCost) {
            //output("Found a better solution.");
            bestCost = cost;
            bestStart = startPoint;
        }
    }

    return subGraphHeuristicHelper(mainGraph, listOfJourneys, bestStart);
}
