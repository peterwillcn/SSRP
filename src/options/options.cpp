#include <cstdlib>
#include <iostream>
#include <FlexLexer.h>
#include "options.h"
using namespace std;

MODE programMode = DEMO;

bool readFromFile = false;

istream* inFile = NULL;

yyFlexLexer* scanner = NULL;

unsigned STATcount = 10;
unsigned STATvertices = 20;
unsigned STATjourneys = 4;
unsigned STATminWeight = 1;
unsigned STATmaxWeight = 10;
bool STATdirected = false;
unsigned numErrors = 0;
string inFileName = "";
bool dumpGraphToFile = false;
bool biSharing = false;
bool printHeuristicsInfo = false;
int DEPTH_VALUE = 2;
bool usePareto = false;

// Stuff for Dease

int weight_threshold = 0;
unsigned num_passes = 5;
int journey_threshold = 3;
