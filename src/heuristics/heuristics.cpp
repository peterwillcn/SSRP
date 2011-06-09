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

// Include the heuristic files
#include "dease.h"
#include "heuristics.h"
#include "shortestPath.h"
#include "spanningTree.h"
#include "subGraph.h"
#include "nashEquilib.h"
#include "spanNash.h"

heuristic::heuristic(string initName,
                     int (*f)(graphGroup, const vector<journeyInfo>&))
    : func(f), name(initName), numberCorrect(0) {
    // Do Nothing
}

const heuristic shortestPathH("Shortest Path", runShortestPathHeuristic);
const heuristic nashEquilibriumH("Nash-Equilib", runNashEquilibriumHeuristic);
const heuristic subGraphH("Sub-Graph", runSubGraphHeuristic);
const heuristic spanningTreeH("Spanning Tree", runSpanningTreeHeuristic);
const heuristic deaseAlgH("Dease Alg", runDeaseHeuristic);
const heuristic spanningNashH("SpanNash", runSpanningNashHeuristic);

vector<heuristic> heuristics;

void setupHeuristics() {
    heuristics.push_back(shortestPathH);
    heuristics.push_back(nashEquilibriumH);
    heuristics.push_back(spanningTreeH);
    heuristics.push_back(deaseAlgH);
    heuristics.push_back(spanningNashH);
}
