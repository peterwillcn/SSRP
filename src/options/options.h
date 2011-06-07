#include <iostream>
using namespace std;

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

// If this value is true, no prompts are written to output for input values.
// Defaults to false
extern bool readFromFile;
// Defaults to NULL
extern istream* inFile;

// Should we actually dump the graph when the dumpGraph function is called?
// Defaults to true
extern bool dumpGraphToFile;