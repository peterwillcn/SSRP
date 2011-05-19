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
void generateGraph(basicEdgeGroup & randomGraph, int n, int type, int style);
void readGraphs(vector< basicEdgeGroup > & inputGroups);
void exportGraph(basicEdgeGroup& outputGroup);
void generateGraphs(vector< basicEdgeGroup > & randomGraphs, int n, int type, int style);
///journey readers:
void readJourneys(vector< journeyInfo > & journeysInformation);
void readJourneysFromFile(vector< journeyInfo > & journeysInformation);
void generateJourneys(vector< journeyInfo > & journeysInformation, int n);

// <- zfj
int getInput(int&, string prompt);

string getInput(string&, string prompt);

bool getChoice(string prompt);

void dumpGraph(const graphGroup&);
// zfj ->

#endif