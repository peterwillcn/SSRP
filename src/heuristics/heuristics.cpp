#include <limits.h>
#include <string>
#include <vector>

using namespace std;

#include "heuristics.h"
#include "ioFunctions.h"
#include "debug.h"
#include "FWGroup.h"
#include "nashTest.hpp"
#include "STGroup.hpp"

//////
////// Function Declarations
//////

int runNashEquilibriumHeuristic(graphGroup, const vector<journeyInfo>&);

int runShortestPathHeuristic(graphGroup, const vector<journeyInfo>&);

int subGraphHeuristicHelper(const graphGroup&, const vector<journeyInfo>&, int startPoint);

int runSubGraphHeuristic(const graphGroup, const vector<journeyInfo>&);

int runSpanningTreeHeuristic(graphGroup, const vector<journeyInfo>&);

//////
////// Function Definitions
//////

//returns the index of (the first instance of)"key" in v,
// or -1 if it's not there
template<typename t>
int find_in_vector(const vector<t>& v, t key){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == key)
            return i;
    }
    // if we get here, it's not there
    return -1;
}

heuristic::heuristic(string initName,
                     int (*f)(graphGroup, const vector<journeyInfo>&))
    : func(f), name(initName), numberCorrect(0) {
    // Do Nothing
}

int runNashEquilibriumHeuristic(graphGroup mainGraph,
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

    for(int cur_pass = 0; cur_pass < num_passes; cur_pass++){

        if(show_reroutings){
            // then show the current journeys paths
            if(debug)
                output("About to rip some stuff up...");
            for(int cur_printing = 0;
                cur_printing < mainGraph.numJourneys();
                cur_printing++)
                printJourney(mainGraph.getJourney(cur_printing));
        }


        //for each edge...
        for(int j = 0; j < mainGraph.returnN(); j++) {
            for(int k = 0; k < mainGraph.returnN(); k++) {
                // if edge (j,k) has > 1 journey on it
                if(mainGraph.numJourneysUsing(j,k) >= journey_threshold ){
                    //then delete the edge- first remove the journeys using it
                    if(debug){
                        output("removing journeys from edge ("
                                + str(j) + "," + str(k) + ")");
                    }

                    vector<int> journeys_rerouted; // list of journeys we rip up
                    vector<path> saved_paths; // paths of the journeys we rip up
                    vector<floatWInf> saved_costs; // costs of the paths we rip up
                    saved_paths = mainGraph.returnSharedPaths();
                    saved_costs = mainGraph.returnSharedCosts();
                    for(int cur_journey = 0;
                        cur_journey < mainGraph.numJourneys();
                        cur_journey++){
                        if(mainGraph.isJourneyIn(j,k,cur_journey)){ // then rip it up

                            mainGraph.removeJourney(listOfJourneys[cur_journey].journeyNum());
                            journeys_rerouted.push_back(listOfJourneys[cur_journey].journeyNum());
                            if(debug)
                                output("Ripping up " + str(cur_journey));
                        }
                    }
                    //remove the edge from the graph
                    floatWInf saved_edge_cost = mainGraph.totalEdgeCost(j,k);
                    mainGraph.update_edge_cost(j,k,infinity);

                    //now reroute everyone that was displaced
                    mainGraph.addJourneysSP(journeys_rerouted);
                    bool displaced_improvement = false; // do any dispalced journeys
                    //get better?
                    int displaced_improvement_num = 0;
                    bool outside_improvement = false;    //do any outsiders get better?
                    int outsider_improvement_num = 0;

                    float sad_rat_num = 0;
                    float sad_rat_den = 0;
                    //now see if anyone else wants to move
                    for(int cur_journey = 0; cur_journey < mainGraph.numJourneys();
                        cur_journey++){
                        int my_journey_num = listOfJourneys[cur_journey].journeyNum();
                        if(find_in_vector(journeys_rerouted,
                                            listOfJourneys[cur_journey].journeyNum())
                            == -1){
                            //then it's not there

                            mainGraph.removeJourney(my_journey_num);
                            mainGraph.addJourneySP(my_journey_num);
                            if(mainGraph.returnSharedCost(my_journey_num) < saved_costs[my_journey_num])
                                // an outsider got better
                                outsider_improvement_num++;
                        }
                        else{ // then this is a displaced journey
                            if (mainGraph.returnSharedCost(my_journey_num)
                                < saved_costs[my_journey_num])
                                // a displaced journey got better
                                displaced_improvement_num++ ;
                        }
                        floatWInf sad_difference = saved_costs[cur_journey] -
                            mainGraph.returnSharedCost(my_journey_num);
                        if(sad_difference > 0) // cost got better
                            sad_rat_den += sad_difference.value();
                        else  //cost got worse
                            sad_rat_num += -1* sad_difference.value();
                    }  // end loop through all journeys to update the outsiders
                    //and check for improvement

                    //put the edge back
                    mainGraph.update_edge_cost(j,k,saved_edge_cost);
                    if(show_reroutings){
                        // then show the current journeys paths
                        for(int cur_printing = 0; cur_printing < mainGraph.numJourneys(); cur_printing++)
                            printJourney(mainGraph.getJourney(cur_printing));
                    }
                    // did enough displaced journeys improve?
                    if(coalition_one && displaced_improvement_num >0)
                        displaced_improvement = true;
                    if(!coalition_one && displaced_improvement_num > journeys_rerouted.size()/2)
                        displaced_improvement = true;

                    //did enough outsider journeys improve?
                    if(outsider_one && outsider_improvement_num > 0)
                        outside_improvement = true;
                    if(!outsider_one && outsider_improvement_num > (mainGraph.numJourneys() - journeys_rerouted.size())/2)
                        outside_improvement = true;
                    if(displaced_improvement && outside_improvement){
                        // then we keep the new journeys
                        if(debug){
                            output("Keeping the new paths");
                            output("New sad rat : " + str(sad_rat_num*1.0/sad_rat_den));
                            output("New paths:");

                            for(int cur_journey = 0; cur_journey < mainGraph.numJourneys();
                                cur_journey++)
                                printJourney(mainGraph.getJourney(listOfJourneys[cur_journey].journeyNum()));
                        }
                    }
                    else{ // put the old paths back
                        if(debug){
                            output("No improvement- replacing old paths");
                        }
                        mainGraph.removeAllJourneys();
                        mainGraph.addJourneys(saved_paths);
                    }
                } // end "if >1 journey on this edge"
            }
        } // end "for all edges"
    } // end # of passes


//     for(int j = 0; j < mainGraph.numJourneys(); j++) {
//         output("Journey " + str(j) + ":");
//         printJourney(mainGraph.getJourney(j));
//     }

    floatWInf final_total_cost = 0;
    for(int j = 0; j < mainGraph.numJourneys(); j++)
        final_total_cost += mainGraph.returnSharedCost(j);

    // this checks if the final solution is a Nash Equilibrium
    bool nash_equilibrium = nashEquilibrium(mainGraph);

    dumpGraph(mainGraph, "NashEquilib");

    if(debug)
        output("Final total cost: " + str(final_total_cost));
    return final_total_cost.value();
}

int runShortestPathHeuristic(graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys) {
    //output("Running Shortest Path Heuristic");

    floatWInf final_total_cost(0);
    FWGroup FloydPaths;
    vector<int> journeysNum;

    for(int j = 0; j < listOfJourneys.size(); j++)
        journeysNum.push_back(listOfJourneys[j].journeyNum());

    FloydPaths.set(journeysNum, mainGraph);

    //route each journey by it's FW path
    for(int j = 0; j < listOfJourneys.size(); j++){
        mainGraph.addJourney(listOfJourneys[j].journeyNum(),
                             FloydPaths.returnPath(listOfJourneys[j].source(),
                                                   listOfJourneys[j].destination()));
    }

    dumpGraph(mainGraph, "Shortest");

    for(int j = 0; j < listOfJourneys.size(); j++) {
        floatWInf res = mainGraph.returnSharedCost(j);
        final_total_cost += res;
    }

    return final_total_cost.value();
}

int subGraphHeuristicHelper(const graphGroup& mainGraph, const vector<journeyInfo>& listOfJourneys, int startPoint) {
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

    //dumpGraph(newGraph);
    //nashEquilibrium(newGraph);

    int totalCost(0);
    for(int i = 0; i < listOfJourneys.size(); i++) {
        floatWInf cost = newGraph.returnSharedCost(i);
        if(cost.isInfinity()) {
            //output("Journey " +str(i)+ " is not routable.");
        }
        else
            totalCost += cost.value();
    }

    return totalCost;
}

int runSubGraphHeuristic(const graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys) {
    //output("Running Subgraph Heuristic");

    if(mainGraph.directed()) {
        output("Warning: this heuristic has not been tested with directed graphs");
    }

    int bestStart = 0;
    int bestCost = INT_MAX;
    for(int startPoint = 0; startPoint < mainGraph.returnN(); startPoint++) {

        int cost = subGraphHeuristicHelper(mainGraph, listOfJourneys, startPoint);

        if(cost < bestCost) {
            //output("Found a better solution.");
            bestCost = cost;
            bestStart = startPoint;
        }
    }

    return bestCost;

}

int runSpanningTreeHeuristic(graphGroup g, const vector<journeyInfo>& journeyInfos) {
    
    int lowestSoFar = INT_MAX;
    int lowestStartVertex = -1;
    for(int startVertex = 0; startVertex < g.returnN(); startVertex++) {
        STGroup st;
        st.findMinSpanningTree(g.returnGraph(), startVertex);

        graphGroup spanningTree(st.returnMinSpanningTree(), journeyInfos);

        for(int i = 0; i < journeyInfos.size(); i++) {
            spanningTree.addJourneySP(i);
            spanningTree.refindSharedCosts();
        }

        int total = 0;
        for(int i = 0; i < journeyInfos.size(); i++) {
            total += spanningTree.returnSharedCost(i).value();
        }

        if(total < lowestSoFar) {
            lowestSoFar = total;
            lowestStartVertex = startVertex;
        }
    }

    STGroup st;
    st.findMinSpanningTree(g.returnGraph(), lowestStartVertex);

    graphGroup spanningTree(st.returnMinSpanningTree(), journeyInfos);

    for(int i = 0; i < journeyInfos.size(); i++) {
        spanningTree.addJourneySP(i);
        spanningTree.refindSharedCosts();
    }
    
    dumpGraph(spanningTree, "spanTree");
    

    return lowestSoFar;
}

const heuristic shortestPathH("Shortest Path", runShortestPathHeuristic);
const heuristic nashEquilibriumH("Nash-Equilib", runNashEquilibriumHeuristic);
const heuristic subGraphH("Sub-Graph", runSubGraphHeuristic);
const heuristic spanningTreeH("Spanning Tree", runSpanningTreeHeuristic);


vector<heuristic> heuristics;

void setupHeuristics() {
    heuristics.push_back(shortestPathH);
    heuristics.push_back(nashEquilibriumH);
    heuristics.push_back(subGraphH);
    heuristics.push_back(spanningTreeH);
}
