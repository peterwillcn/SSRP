#ifndef _HEURISTICS_H_
#define _HEURISTICS_H_

#include <vector>
#include "graphGroup.h"
#include "journeyInfo.h"

using namespace std;

struct heuristic {
// Public:
    int (*func)(graphGroup, const vector<journeyInfo>&);

    string name;

    int numberCorrect;

    heuristic(string initName,
              int (*f)(graphGroup, const vector<journeyInfo>&));
};

int runNashEquilibriumHeuristic(graphGroup, const vector<journeyInfo>&);

int runShortestPathHeuristic(graphGroup, const vector<journeyInfo>&);

int subGraphHeuristicHelper(const graphGroup&, const vector<journeyInfo>&, int startPoint);

int runSubGraphHeuristic(const graphGroup, const vector<journeyInfo>&);

int runSpanningTreeHeuristic(graphGroup, const vector<journeyInfo>&);

void setupHeuristics();

extern vector<heuristic> heuristics;

#endif