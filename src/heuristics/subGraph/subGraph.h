#ifndef _SUBGRAPH_HEURISTIC_
#define _SUBGRAPH_HEURISTIC_

#include <vector>

using namespace std;

#include "graphGroup.h"
#include "journeyInfo.h"

/*
 * Sub-Graph heuristic
 *
 * This is a theoretical algorithm used to prove statistically that there is
 * always a nash equilibrium in certain types of graphs. This algorithm does
 * considerably worse than most other algorithms, and so is not in use.
 */
graphGroup runSubGraphHeuristic(const graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys);

#endif