#include <string>
#include <iostream>
#include <vector>
#include <sstream>
#include "commandParser.h"

#include "ioFunctions.h"
#include "options.h"

using namespace std;

//
// commandParser
//

// Private

vector<string> commandParser::argumentVector(int argc, const char* const argv[]) {
    vector<string> v;
    for(int i = 0; i < argc; i++) {
        v.push_back(string(argv[i]));
    }
    return v;
}

// Protected

string commandParser::usage() const {
    return "\
Usage: \n\
graph MODE [OPTIONS]\n\
\n\
MODE : stats\n\
       demo\n\
\n\
Modes:\n\
    Demo Mode:\n\
\n\
        graph demo [INPUT_FILE]\n\
\n\
        Creates a single graph and runs the heuristics on it.\n\
\n\
        The only option available is to specify an optional input file. If the\n\
        input file is specified, no prompts are written to stdout. If no input\n\
        file is specified, all input/output comes from stdin.\n\
\n\
        Input file formatting:\n\
            Input files should be formatted for input using exactly the same\n\
            prompts as if no input file is given.\n\
\n\
    Stats Mode:\n\
\n\
        graph stats [COUNT]\n\
\n\
        Creates a large number of graphs, runs the heuristics on them, and then\n\
        gives comparison and statistics information about how well the\n\
        heuristics did.\n\
\n\
        The only option available is to specify a count that affects how many\n\
        graphs are generated. If none is provided, the default value is 10\n\
";
}

bool commandParser::isValid(const string& str) const {
    return lookup(str) != npos;
}

void commandParser::error(const string& str) {
    cerr << "Invalid command line argument: " << str << "\n\n";
    numErrors++;
}

int commandParser::activate(int ref, const vector<string>& args) {
    int numberParams = 1;
    if(args[ref] == "demo") {
        programMode = DEMO;
        if(args.size() != ref+1) {
            inputFromFile = true;
            inputFilename = args[ref+1];
            numberParams = 2;
            readFromFile = true;
        }
        else
            readFromFile = false;
    }
    else if(args[ref] == "stats") {
        programMode = STATS;
        if(args.size() != ref+1) {
            istringstream s(args[ref+1]);
            s >> statRunCount;
            numberParams = 2;
        }
    }
    return numberParams;
}

int commandParser::lookup(const string& str) const {
    for(int i = 0; i < argList.size(); i++){
        if(argList[i] == str)
            return i;
    }
    return npos;
}

// Public

commandParser::commandParser()
    :   numErrors(0),
        assembleOutput(false),
        inputFromFile(false),
        inputFilename(""),
        statRunCount(10)
{
    argList.push_back(commandArgument("demo"));
    argList.push_back(commandArgument("stats"));
}

void commandParser::parse(const int argc, const char* const argv[]) {
    vector<string> arguments = argumentVector(argc, argv);
    if(argc == 1) {
        cout << "Missing command line argument: MODE\n";
        numErrors++;
    }
    for(int i = 1; i < argc;) {
        if(isValid(arguments[i])) {
            i += activate(i, arguments);
        }
        else {
            error(arguments[i]);
            i++;
        }
    }
    if(error())
        cerr << usage() << endl;
}

bool commandParser::error() const {
    return numErrors != 0;
}

bool commandParser::success() const {
    return numErrors == 0;
}

bool commandParser::fileInput() const {
    return inputFromFile;
}

string commandParser::inputFile() const {
    return inputFilename;
}

int commandParser::statRuns() const {
    return statRunCount;
}