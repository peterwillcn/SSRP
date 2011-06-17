#ifndef _TRAVERSAL_HEURISTIC_
#define _TRAVERSAL_HEURISTIC_

#include <vector>

using namespace std;

#include "graphGroup.h"
#include "journeyInfo.h"

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
graphGroup runTraversalHeuristic(const graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys);

#endif