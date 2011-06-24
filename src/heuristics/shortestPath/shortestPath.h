#ifndef _SHORTEST_PATH_HEURISTIC_
#define _SHORTEST_PATH_HEURISTIC_

#include <vector>

using namespace std;

#include "journeyInfo.h"
#include "graphGroup.h"

/*
 * Shortest Path
 *
 * This is the basis of comparison for our other algorithms. It routes things
 * by their shortest paths.
 */
graphGroup runShortestPathHeuristic(graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys);

#endif
