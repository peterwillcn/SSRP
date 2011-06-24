#ifndef _HEURISTICS_H_
#define _HEURISTICS_H_

/**
 * @file: heuristics.h
 *
 * This file contains the declaration for the heuristic type.
 *
 * See heuristics.cpp for more information on heuristics.
 */

#include <vector>

using namespace std;

#include "graphGroup.h"
#include "journeyInfo.h"

struct heuristic {
// Public:
    graphGroup (*func)(graphGroup, const vector<journeyInfo>&);

    string name;

    int numberCorrect;

    bool useNashAlgorithm;

    heuristic(string initName,
              graphGroup (*f)(graphGroup, const vector<journeyInfo>&),
              bool nashAlg
             );
};

void setupHeuristics();

extern vector<heuristic> heuristics;

#endif
