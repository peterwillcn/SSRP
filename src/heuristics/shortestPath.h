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