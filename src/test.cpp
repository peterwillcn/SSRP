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
#include <ctime>

int yyparse();

const string usage =
string("") +
FGWHITE + "Usage:\n" + ENDC +
"    " + FGGREEN + "graph mode modeOptions\n" + ENDC +
"\n" +
FGWHITE + "Modes:\n" + ENDC +
"\n" +
"    " + FGGREEN + "graph stat\n" + ENDC +
"    " + FGGREEN + "graph stats\n" + ENDC +
"\n" +
"    " + FGWHITE + "Options:\n" + ENDC +
"        -c INT\n" +
"            The number of times to run the graph heuristics.\n" +
"            Defaults to 10.\n" +
"        -v INT\n" +
"            The number of vertices in the graph.\n" +
"            Defaults to 20.\n" +
"        -j INT\n" +
"            The number of journeys in the graph.\n" +
"            Defaults to 4.\n" +
"        -w INT INT\n" +
"            The min and max values to use for the graph's weights.\n" +
"            Defaults to 1 and 10\n" +
"        -d\n" +
"            Makes the graph directed.\n" +
"        -u\n" +
"            Makes the graph undirected. (Default)\n" +
"\n" +
"    " + FGGREEN + "graph demo\n" + ENDC + "" +
"\n" +
"    " + FGWHITE + "Options:\n" + ENDC +
"        -f FILE\n" +
"            Specifies an input file to use. If none is given, uses stdin.\n" +
"\n" +
"    " + FGWHITE + "Options Common to Both Modes:\n" + ENDC +
"        -p\n" +
"            Prints all graphs to a file.\n" +
"        -np\n" +
"            Do not print graphs to files. (Default)\n" +
"        -h\n" +
"            Print this message and exit. (Should be used without a mode)\n" +
"        -b\n" +
"            Use bi-directional sharing.\n";

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

template <typename T1, typename T2, typename T3>
struct triple {
    T1 first;
    T2 second;
    T3 third;
    triple(T1 initFirst, T2 initSecond, T3 initThird)
        : first(initFirst), second(initSecond), third(initThird)
        {
    }
};

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
    output(" Time (s)");

    vector<triple<int,double,clock_t> > numberCorrect(heuristics.size(), triple<int,double,clock_t>(0, 0.0, 0));

    // Run the loop
    for(int caseNumber = 0; caseNumber < STATcount; caseNumber++) {
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
            clock_t startTime = clock();
            results[i] = heuristics[i].func(mainGraph, listOfJourneys);
            clock_t endTime = clock();
            numberCorrect[i].third = endTime - startTime;
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

        clock_t totalTime = 0;
        for(int i = 0; i < heuristics.size(); i++) {
            totalTime += numberCorrect[i].third;
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
        const long int CLOCK_TICKS = CLOCKS_PER_SEC;
        double runTime = double(totalTime) / double(CLOCK_TICKS);
        output(string(" ") + str(runTime));

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

            if(false) {
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