#ifndef _DEASE_HEURISTIC_
#define _DEASE_HEURISTIC_

#include <vector>

using namespace std;

#include "journeyInfo.h"
#include "graphGroup.h"

/*
 * Dease Algorithm
 *
 * Finds edges that are commonly shared and deletes them. This is to encourage
 * sharing and try to find a nash equilibrium.
 */
graphGroup runDeaseHeuristic(graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys);

#endif