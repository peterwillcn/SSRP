#ifndef _IO_FUNCTIONS_H_
#define _IO_FUNCTIONS_H_

#include "basicEdgeGroup.h"
#include "graphGroup.h"
#include "journeyInfo.h"

#include <vector>

extern const bool YES;
extern const bool NO;

////
//// Main I/O Functions:
////

// Reads in an integer from cin
int inputInt(const string& prompt);

// Reads in an integer in the range [low, high) from cin
int inputBoundedInt(const string& prompt, int low, int high);

// Reads in a string from cin
string inputString(const string& prompt);

// Returns the string form of an integer
string str(int);

// Returns the string form of a float
string str(float);

// Returns the string form of a double
string str(double);

// Returns the string form of an unsigned
string str(unsigned);

// Returns the string form of a floatWInf
string str(floatWInf);

// Outputs a string to cout. Appends suffix to the end
void output(const string&, const string& suffix = "\n");

// Reads in a boolean answer from cin.
// Yes/No answer
bool getChoice(string prompt);

////
//// Graph I/O Functions:
////

void readGraph(basicEdgeGroup & inputGroup);
void readGraphFromFile(basicEdgeGroup & inputGroup);
void readGraphs(vector< basicEdgeGroup > & inputGroups);
void exportGraph(basicEdgeGroup& outputGroup);

// Prints a graph to a file.
void dumpGraph(const graphGroup&);

// print a graph
void printGraph(const graphGroup&);

////
//// Journey I/O Functions:
////

void readJourneys(vector< journeyInfo > & journeysInformation);
void readJourneysFromFile(vector< journeyInfo > & journeysInformation);

// print all info on journeys
void printJourneys(const journeyGroup&);

// print all info on a journey
void printJourney(const journey&);

// print actual paths of a journey
void printJourneyPaths(const journey&);

// print actual paths of a journey
void printJourneyPath(const journey&);

// print shared & single costs && savings of a journey
void printJourneyCosts(const journey&);

// print shared & single costs && saving of a journey
void printJourneyCost(const journey&);

#endif