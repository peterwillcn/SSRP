#ifndef _IO_FUNCTIONS_H_
#define _IO_FUNCTIONS_H_

#include "basicEdgeGroup.h"
#include "graphGroup.h"
#include "journeyInfo.h"

#include <vector>

extern const bool YES;
extern const bool NO;

//read functions:
///graph readers:
void readGraph(basicEdgeGroup & inputGroup);
void readGraphFromFile(basicEdgeGroup & inputGroup);
void generateGraph(basicEdgeGroup & randomGraph);
void readGraphs(vector< basicEdgeGroup > & inputGroups);
void exportGraph(basicEdgeGroup& outputGroup);
void generateGraphs(vector< basicEdgeGroup > & randomGraphs);
///journey readers:
void readJourneys(vector< journeyInfo > & journeysInformation);
void readJourneysFromFile(vector< journeyInfo > & journeysInformation);
void generateJourneys(vector< journeyInfo > & journeysInformation, int n);

void generateFiniteWeightedGraph(basicEdgeGroup& randomGraph);
void generateInfiniteWeigtedGraph(basicEdgeGroup& randomGraph);
void generateLimitedDirectionalGraph(basicEdgeGroup& randomGraph);
void generateHighwaySystem(basicEdgeGroup& randomGraph);
void generateThreadedGrid(basicEdgeGroup& randomGraph);
void generateSparseGraph(basicEdgeGroup& randomGraph);

// <- zfj
int inputInt(const string& prompt);

string inputString(const string& prompt);

string str(int);

string str(float);

string str(double);

string str(floatWInf);

void output(const string&, const string& suffix = "\n");

bool getChoice(string prompt);

void dumpGraph(const graphGroup&);
// zfj ->

#endif