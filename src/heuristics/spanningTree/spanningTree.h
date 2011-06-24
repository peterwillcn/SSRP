#ifndef _SPANNING_TREE_HEURISTIC_
#define _SPANNING_TREE_HEURISTIC_

#include <vector>

using namespace std;

#include "graphGroup.h"
#include "journeyInfo.h"

/*
 * Spanning Tree Algorithm
 *
 * This is the vanilla version of the spanning tree algorithm. It finds the
 * spanning tree for a graph, then routes journeys on the spanning tree.
 */
graphGroup runSpanningTreeHeuristic(graphGroup g, const vector<journeyInfo>& journeyInfos);

#endif
