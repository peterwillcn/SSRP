#ifndef _IO_FUNCTIONS_H_
#define _IO_FUNCTIONS_H_

#include "basicEdgeGroup.h"
#include "journeyInfo.h"

#include <vector>

//read functions:
///graph readers:
void readGraph(basicEdgeGroup & inputGroup);
void readGraphFromFile(basicEdgeGroup & inputGroup);
void generateGraph(basicEdgeGroup & randomGraph, int n, int type, int style);
void readGraphs(vector< basicEdgeGroup > & inputGroups);
void generateGraphs(vector< basicEdgeGroup > & randomGraphs, int n, int type, int style);
void exportGraph(basicEdgeGroup& outputGroup);
///journey readers:
void readJourneys(vector< journeyInfo > & journeysInformation);
void readJourneysFromFile(vector< journeyInfo > & journeysInformation);
void generateJourneys(vector< journeyInfo > & journeysInformation, int n);
void generateJourneys(vector< journeyInfo > & journeysInformation, int n);

#endif