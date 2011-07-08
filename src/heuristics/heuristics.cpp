/**
 *
 * @file: src/heuristics/heuristics.cpp
 *
 * This file holds the definitions for the heuristic type's members and
 * the definitions of the built-in heuristics.
 *
 * @section newHeuristics Adding New Heuristics
 * 
 * To add new heuristics, create a heuristic function of type:
 *      graphGroup f(graphGroup, const vector<journeyInfo>&);
 * 
 * After this is done, create a constant heuristic with this function and a name,
 * then push it onto the heuristics vector inside setupHeuristics().
 */

#include "heuristics.h"

#include <string>

using namespace std;

#include "graphGroup.h"

heuristic::heuristic(string initName,
                     graphGroup (*f)(graphGroup, const vector<journeyInfo>&),
                     bool nashAlg
                    )
    : func(f), name(initName), numberCorrect(0), useNashAlgorithm(nashAlg) {
    // Do Nothing
}

#include "shortestPath/shortestPath.h"
const heuristic shortestPathH("Shortest", runShortestPathHeuristic, true);

#include "nashEquilib/nashEquilib.h"
const heuristic nashEquilibriumH("Nash-Equilib", runNashEquilibriumHeuristic, true);

#include "subGraph/subGraph.h"
const heuristic subGraphH("Sub-Graph", runSubGraphHeuristic, true);

#include "spanningTree/spanningTree.h"
const heuristic spanningTreeH("SpanTree", runSpanningTreeHeuristic, true);

#include "dease/dease.h"
const heuristic deaseAlgH("Dease", runDeaseHeuristic, true);

#include "spanNash/spanNash.h"
const heuristic spanningNashH("SpanNash", runSpanningNashHeuristic, true);

#include "traversal/traversal.h"
const heuristic traversalH("Traversal", runTraversalHeuristic, true);

vector<heuristic> heuristics;

void setupHeuristics() {
    //heuristics.push_back(shortestPathH);
    heuristics.push_back(spanningNashH);
}
