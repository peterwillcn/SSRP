#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <limits.h>
#include <utility>
#include <FlexLexer.h>

using namespace std;

// -- before --

#include "basicStructures.h"
#include "vertex.h"
#include "path.h"
#include "edge.h"
#include "basicEdgeGroup.h"
#include "journeyInfo.h"
#include "journey.h"
#include "journeyGroup.h"
#include "edgeGroup.h"
#include "graphGroup.h"
#include "ioFunctions.h"
#include "FWGroup.h"
#include "STGroup.hpp"
#include "nashTest.hpp"
#include "debug.h"
#include "options.h"
#include "rand.h"
#include "heuristics.h"

// -- after --

#include "color.h"

int yyparse();

const string usage = "\
Usage:\n\
    graph mode modeOptions\n\
\n\
Modes:\n\
\n\
    graph stat\n\
\n\
    Options:\n\
        -c INT\n\
            The number of times to run the graph heuristics.\n\
            Defaults to 10.\n\
        -v INT\n\
            The number of vertices in the graph.\n\
            Defaults to 20.\n\
        -j INT\n\
            The number of journeys in the graph.\n\
            Defaults to 4.\n\
        -w INT INT\n\
            The min and max values to use for the graph's weights.\n\
            Defaults to 1 and 10\n\
        -d\n\
            Makes the graph directed.\n\
        -u\n\
            Makes the graph undirected. (Default)\n\
        -p\n\
            Prints all graphs to a pdf file.\n\
        -np\n\
            Do not print graphs to pdf files. (Default)\n\
\n\
    graph demo\n\
\n\
    Options:\n\
        -f FILE\n\
            Specifies an input file to use. If none is given, uses stdin.\n\
";

const string welcomeHeader =
"\n\
+------------------------------------------------------------------------------+\n\
|                          Shared Shorest Path Project                         |\n\
| Authors: Christopher Earl (2006)                                             |\n\
|          Brooks Emerick (2008)                                               |\n\
|          Sean Quigley (2009)                                                 |\n\
|          Nicole Peterson (2010)                                              |\n\
|          Ronald Fenelus (2011)                                               |\n\
|          Zeal Jagannatha (2011)                                              |\n\
| Mentor:  Sean McCulloch                                                      |\n\
+------------------------------------------------------------------------------+\n";

void doStats() {

    // Options
    const int NUM_VERTICES = STATvertices;
    const bool DIRECTED = STATdirected;
    const int MIN_WEIGHT = STATminWeight;
    const int MAX_WEIGHT = STATmaxWeight;
    const int NUM_JOURNEYS = STATjourneys;

    cout << "Using stat mode.\n";
    cout << "Vertices:   " << NUM_VERTICES << endl;
    cout << "Journeys:   " << NUM_JOURNEYS << endl;
    cout << "Min Weight: " << MIN_WEIGHT << endl;
    cout << "Max Weight: " << MAX_WEIGHT << endl;
    cout << "Count:      " << STATcount << endl;
    cout << "Directed:   " << boolalpha << DIRECTED << endl;

    // Turn off graph dumping
    //dumpGraphToFile = false;

    // Output formatting
    pad(" ", 10); output("|", "");
    for(int i = 0; i < heuristics.size(); i++){
        outputCenter(heuristics[i].name, heuristics[i].name.size()+2);
        output("|", "");
    }
    output("");

    vector<pair<int,double> > numberCorrect(heuristics.size(), pair<int,double>(0, 0.0));

    // Run the loop
    for(int i = 0; i < STATcount; i++) {
        int graphNum = getGraphNumber();
        output("Case:", "");
        outputRight(str(graphNum),5);
        output("|", "");

        basicEdgeGroup g;
        graphGroup mainGraph;
        vector<journeyInfo> listOfJourneys;

        generateSparseGraph(g, NUM_VERTICES, DIRECTED, MIN_WEIGHT, MAX_WEIGHT);

        listOfJourneys.resize(NUM_JOURNEYS);
        for(int i = 0; i < NUM_JOURNEYS; i++)
            listOfJourneys[i].setJourneyNum(i);
        generateJourneys(listOfJourneys, NUM_VERTICES);
        mainGraph.set(g, listOfJourneys);

        vector<int> results(heuristics.size());

        for(int i = 0; i < heuristics.size(); i++) {
            results[i] = heuristics[i].func(mainGraph, listOfJourneys);
        }

        int best = INT_MAX;
        int numBest = 0;
        for(int i = 0; i < heuristics.size(); i++) {
            if(results[i] < best) {
                best = results[i];
                numBest = 1;
            }
            else if(results[i] == best) {
                numBest++;
            }
        }

        for(int i = 0; i < heuristics.size(); i++) {
            if(results[i] == best) {
                numberCorrect[i].first++;
                numberCorrect[i].second += 1.0 / double(numBest);
                outputGreenRight(str(results[i]), heuristics[i].name.size()+2);
                output("|", "");
            }
            else {
                outputRight(str(results[i]), heuristics[i].name.size()+2);
                output("|", "");
            }
        }
        output("");

        incrementGraphNumber();
    }

    outputLeft("Totals:", 10);
    output("|", "");
    for(int i = 0; i < heuristics.size(); i++) {
        outputCenter(heuristics[i].name, heuristics[i].name.size()+2);
        output("|", "");
    }
    output("");

    pad(" ", 10);
    output("|", "");
    for(int i = 0; i < heuristics.size(); i++) {
        output(str(numberCorrect[i].first), "");
        outputRight(str(numberCorrect[i].second, 4),
                    heuristics[i].name.size()+2
                    -str(numberCorrect[i].first).size());
        output("|", "");
    }
    output("");
}

int main(int argc, char* argv[]) {

    output(welcomeHeader);

    ostringstream temp;
    for(int i = 1; i < argc; i++) {
        temp << argv[i] << " ";
    }
    istringstream* yyin = new istringstream(temp.str());
    scanner = new yyFlexLexer(yyin);
    yyparse();

    if(numErrors > 0) {
        output(usage);
        return 1;
    }

    else {

        setupHeuristics();

        if(programMode == STAT) {

            doStats();

        }

        else {
            // programMode == DEMO

            if(true) {
                inFile = new ifstream("input");
            }
            else {
                inFile = &cin;
            }

            graphGroup mainGraph;
            basicEdgeGroup basicGraph;
            vector<journeyInfo> listOfJourneys;

            // Generate the graph and journeys
            readGraph(basicGraph);
            readJourneys(listOfJourneys, basicGraph);

            for(int i = 0; i < listOfJourneys.size(); i++) {
                output("Journey " +str(i)+ ": ", "");
                output(str(listOfJourneys[i].source()) + " -> " + str(listOfJourneys[i].destination()));
            }

            // Set the journey numbers for each journey:
            // Journey i's journey number is i
            for(int i = 0; i < listOfJourneys.size(); i++)
                listOfJourneys[i].setJourneyNum(i);
            mainGraph.set(basicGraph, listOfJourneys);

            int shortestPathCost = 0;
            for(int i = 0; i < heuristics.size(); i++) {
                int result = heuristics[i].func(mainGraph, listOfJourneys);
                if(i == 0)
                    shortestPathCost = result;
                output("Running heuristic: " + heuristics[i].name);
                output("\tHas total cost of: " + str(result));
                if(i > 0)
                    output("\tImprovement over shortest path: " + str(shortestPathCost - result));
                output("");
            }

            if(inFile != &cin)
                delete inFile;

        }

        return 0;
    }
}