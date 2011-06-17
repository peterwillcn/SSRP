#ifndef _NASH_EQUILIB_HEURISTIC_
#define _NASH_EQUILIB_HEURISTIC_

#include <vector>

using namespace std;

#include "journeyInfo.h"
#include "graphGroup.h"

/*
 * Nash Equilibrium
 *
 * This is the vanilla version of the nash equilibrium algorithm. Everything is
 * routed by their shortest paths, and then the nash equilibrium algorithm is
 * run on them.
 */
graphGroup runNashEquilibriumHeuristic(graphGroup mainGraph, const vector<journeyInfo>& listOfJourneys);

#endif