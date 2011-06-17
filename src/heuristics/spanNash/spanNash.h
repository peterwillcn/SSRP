#ifndef _SPANNING_NASH_HEURISTIC_
#define _SPANNING_NASH_HEURISTIC_

#include <vector>

using namespace std;

#include "graphGroup.h"
#include "journeyInfo.h"

/*
 * Spanning Tree / Nash Equilibrium Heuristic
 *
 * This algorithm finds the spanning tree for a graph and then routes Journeys
 * on this spanning tree. It then transforms these routes back into the original
 * graph, and runs the nash equilibrium heuristic.
 */
graphGroup runSpanningNashHeuristic(graphGroup g, const vector<journeyInfo>& journeyInfos);

#endif