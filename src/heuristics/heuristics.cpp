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
#include "heuristics.h"

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

#include "shortestPath.h"
const heuristic shortestPathH("Shortest Path", runShortestPathHeuristic);

#include "nashEquilib.h"
const heuristic nashEquilibriumH("Nash-Equilib", runNashEquilibriumHeuristic);

#include "subGraph.h"
const heuristic subGraphH("Sub-Graph", runSubGraphHeuristic);

int smallestStartVertex = -1;
#include "spanningTree.h"
const heuristic spanningTreeH("Spanning Tree", runSpanningTreeHeuristic);

#include "dease.h"
const heuristic deaseAlgH("Dease Alg", runDeaseHeuristic);

#include "spanNash.h"
const heuristic spanningNashH("SpanNash", runSpanningNashHeuristic);

vector<heuristic> heuristics;

void setupHeuristics() {
    heuristics.push_back(shortestPathH);
    heuristics.push_back(nashEquilibriumH);
    heuristics.push_back(deaseAlgH);
    heuristics.push_back(spanningNashH);
}
