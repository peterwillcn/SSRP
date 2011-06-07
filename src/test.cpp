//Christopher Earl
//test.cpp
// contains main() to test various classes
//Version that removed edges from the graph and reroutes

#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <limits.h>

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

#include "commandParser.h"
#include "color.h"

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

void doStats(int NUM_TEST_CASES) {

    // Options
    const int NUM_VERTICES = 50;
    const bool DIRECTED = false;
    const int MIN_WEIGHT = 1;
    const int MAX_WEIGHT = 10;
    const int NUM_JOURNEYS = 10;

    // Turn off graph dumping
    //dumpGraphToFile = false;

    // Output formatting
    pad(" ", 10); output("|", "");
    for(int i = 0; i < heuristics.size(); i++){
        outputCenter(heuristics[i].name, heuristics[i].name.size()+2);
        output("|", "");
    }
    output("");

    vector<double> numberCorrect(heuristics.size(), 0.0);

    // Run the loop
    for(int i = 0; i < NUM_TEST_CASES; i++) {
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
                numberCorrect[i] += 1.0 / double(numBest);
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
        outputRight(str(numberCorrect[i]), heuristics[i].name.size()+2);
        output("|", "");
    }
    output("");
}

int main(int argc, char* argv[]) {

    output(welcomeHeader);

    commandParser c;
    c.parse(argc, argv);

    if(c.error()) {

        return 1;

    }

    else {

        setupHeuristics();

        if(programMode == STATS) {

            doStats(c.statRuns());

        }

        else {

            if(c.fileInput()) {
                inFile = new ifstream(c.inputFile().data());
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

            int shortest = 0;
            for(int i = 0; i < heuristics.size(); i++) {
                int result = heuristics[i].func(mainGraph, listOfJourneys);
                if(i == 0)
                    shortest = result;
                output("Running heuristic: " + heuristics[i].name);
                output("\tHas total cost of: " + str(result));
                if(i > 0)
                    output("\tImprovement over shortest path: " + str(shortest - result));
                output("");
            }

            if(inFile != &cin)
                delete inFile;

        }

        return 0;
    }
}