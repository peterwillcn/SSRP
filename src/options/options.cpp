#include <cstdlib>
#include <iostream>
#include <FlexLexer.h>
#include "options.h"
using namespace std;

MODE programMode = DEMO;

bool readFromFile = false;

istream* inFile = NULL;

yyFlexLexer* scanner = NULL;

int STATcount = 10;
int STATvertices = 20;
int STATjourneys = 4;
int STATminWeight = 1;
int STATmaxWeight = 10;
bool STATdirected = false;
int numErrors = 0;
string inFileName = "";
bool dumpGraphToFile = false;