#ifndef _RAND_H_
#define _RAND_H_

#include <cstdlib>
#include "basicEdgeGroup.h"
#include "journeyGroup.h"

////
//// Random number generators
////

// Generates a random number in range [0, randMax]
int randomGenerator(int randMax);

// Generates a random number in range [min, max]
int randomWeight(int min, int max);

////
//// Graph Generation
////

// Generate some number of graphs
void generateGraphs(vector< basicEdgeGroup > & randomGraphs);

// Generate a single graph
void generateGraph(basicEdgeGroup & randomGraph);

// These functions each generate one type of graph.
void generateFiniteWeightedGraph(basicEdgeGroup& randomGraph);
void generateInfiniteWeigtedGraph(basicEdgeGroup& randomGraph);
void generateLimitedDirectionalGraph(basicEdgeGroup& randomGraph);
void generateHighwaySystem(basicEdgeGroup& randomGraph);
void generateThreadedGrid(basicEdgeGroup& randomGraph);
void generateSparseGraph(basicEdgeGroup& randomGraph);
void generateSparseGraph(basicEdgeGroup& graph, int numberVertices, bool directed, int minWeight, int maxWeight);

////
//// Journey Generation
////

void generateJourneys(vector< journeyInfo > & journeysInformation, int n);

#endif