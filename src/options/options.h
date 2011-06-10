#include <iostream>
#include <FlexLexer.h>
using namespace std;

enum MODE { STAT = 0, DEMO = 1 };

extern MODE programMode;

//////
////// Global Options file for entire project
//////

// Options in this file should be const and have descriptive names.

////
//// Options for edge counting
////

// Use bi-directional edge sharing?
//const bool useBiDirectionalSharing = false;

////
//// Options for dotty graph output
////

// Final output format.
// For a full list see:
//     http://www.graphviz.org/content/output-formats
const string graphFormat = "pdf";

// Graphviz program to use.
const string graphvizCmd = "dot";

// Configuration file to use.
const string configFile  = ".graphConfig";

// Print journey label nodes?
const bool printLabelNodes = false;

// Use double circles for journey endpoints?
const bool useDoubleEndpoints = false;

// Background color of the graph.
const string background = "white";

////
//// Options provided for command line input
////

// If this value is true, no prompts are written to output for input values.
// Defaults to false
extern bool readFromFile;
// Defaults to NULL
extern istream* inFile;

extern yyFlexLexer* scanner;

extern int STATcount;
extern int STATvertices;
extern int STATjourneys;
extern int STATminWeight;
extern int STATmaxWeight;
extern bool STATdirected;
extern int numErrors;
extern string inFileName;
extern bool dumpGraphToFile;
extern bool biSharing;
extern bool findNash;
extern bool printHeuristicsInfo;

// Stuff for Dease algorithm
extern int weight_threshold;
extern int num_passes;
extern int journey_threshold;