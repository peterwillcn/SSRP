#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <limits.h>
#include <utility>
#include <FlexLexer.h>
#include <time.h>

using namespace std;

#include "colorString.h"
#include "options.h"
#include "basicEdgeGroup.h"
#include "graphGroup.h"
#include "ioFunctions.h"
#include "heuristics.h"
#include "rand.h"
#include "nashTest.hpp"

#include "messages.h"

#define ONE_BILLION 1000000000.0

int yyparse();

template <typename T1, typename T2, typename T3>
struct triple {
    T1 first;
    T2 second;
    T3 third;
    triple(T1 initFirst, T2 initSecond, T3 initThird)
        : first(initFirst), second(initSecond), third(initThird) {
        // Do Nothing
    }
};

void doStats() {

    cout << "Using stat mode.\n";
    cout << "Vertices:   " << STATvertices << endl;
    cout << "Journeys:   " << STATjourneys << endl;
    cout << "Min Weight: " << STATminWeight << endl;
    cout << "Max Weight: " << STATmaxWeight << endl;
    cout << "Count:      " << STATcount << endl;
    cout << "Directed:   " << boolalpha << STATdirected << endl;

    // Turn off graph dumping
    //dumpGraphToFile = false;

    // Output formatting
    pad(" ", 10); output("|", "");
    for(int i = 0; i < heuristics.size(); i++){
        outputCenter(heuristics[i].name, heuristics[i].name.size()+2);
        output("|", "");
    }
    output(" Time (s)");

    vector<triple<int,double,double> > numberCorrect(heuristics.size(),
                                                     triple<int,double,double>(0,
                                                                               0.0,
                                                                               0.0));

    //Run through each case(newly generated graph)
    for(int caseNumber = 0; caseNumber < STATcount; caseNumber++) {
        //print case #
        int graphNum = getGraphNumber();
        output("Case:", "");
        outputRight(str(graphNum),5);
        output("|", "");

        basicEdgeGroup g;
        graphGroup mainGraph;
        vector<journeyInfo> listOfJourneys;

        //generate the graph
        generateSparseGraph(g,
                            STATvertices,
                            STATdirected,
                            STATminWeight,
                            STATmaxWeight);

        //generate random journeys
        listOfJourneys.resize(STATjourneys);
        for(int i = 0; i < STATjourneys; i++)
            listOfJourneys[i].setJourneyNum(i);
        generateJourneys(listOfJourneys, STATvertices);
        mainGraph.set(g, listOfJourneys);

        //create a vector to store score results
        vector<floatWInf> results(heuristics.size());

        //create a vector to store time information
        vector<double> times(heuristics.size(), 0.0);

        //run each "heuristic"
        for(int i = 0; i < heuristics.size(); i++) {
            //timer start
            timespec sTime;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &sTime);

            //run heuristic
            graphGroup g = heuristics[i].func(mainGraph,
                                              listOfJourneys);

            if(heuristics[i].useNashAlgorithm)
                nashEquilibrium(mainGraph);

            //timer end
            timespec eTime;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &eTime);

            //convert time
            double startTime = sTime.tv_sec + ((double)sTime.tv_nsec/ ONE_BILLION);
            double endTime = eTime.tv_sec + ((double)eTime.tv_nsec/ ONE_BILLION);

            //print graph PDF
            dumpGraph(g,heuristics[i].name);

            //calculate total cost of shared path
            results[i] = g.totalSharedCost();

            //calculate and store time taken for "heuristic"
            times[i] = endTime - startTime;
            numberCorrect[i].third += times[i];
        }

        //find best(lowest total cost) "heuristic"(s)
        floatWInf best = floatWInf(true, 0);
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

        //calculate the total time taken for the heuristics on case,
        //print results and time
        double totalTime = 0;
        for(int i = 0; i < heuristics.size(); i++) {
            totalTime += times[i];
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
        
        output(string(" ") + str(totalTime));

        //increment case number for file consitency
        incrementGraphNumber();
    }

    //output heuristic names for totals data
    outputLeft("Totals:", 10);
    output("|", "");
    for(int i = 0; i < heuristics.size(); i++) {
        outputCenter(heuristics[i].name, heuristics[i].name.size()+2);
        output("|", "");
    }
    output("");

    //output total wins for each heuristic
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

    //output total time for each heuristic
    outputLeft("Time (s):", 10);
    output("|", "");
    double totalTime = 0;
    for(int i = 0; i < heuristics.size(); i++) {
        outputRight(str(double(numberCorrect[i].third)),
                    heuristics[i].name.size()+2);
        output("|", "");
        totalTime += double(numberCorrect[i].third);
    }
    output(" " + str(totalTime, 3));

    //output time percentage for each heuristic
    outputLeft("Time (%):", 10);
    output("|", "");
    for(int i = 0; i < heuristics.size(); i++) {
        outputRight(str(((double(numberCorrect[i].third)) * 100.0)  / totalTime),
                    heuristics[i].name.size()+2);
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
        output("");
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

            if(readFromFile) {
                inFile = new ifstream(inFileName.data());
            }
            else inFile = &cin;

            if(printHeuristicsInfo) {
                output(heuristicsInfo);
                return 0;
            }

            graphGroup mainGraph;
            basicEdgeGroup basicGraph;
            vector<journeyInfo> listOfJourneys;

            // Generate the graph and journeys
            readGraph(basicGraph);
            readJourneys(listOfJourneys, basicGraph);

            for(int i = 0; i < listOfJourneys.size(); i++) {
                output("Journey " +str(i)+ ": ", "");
                output(str(listOfJourneys[i].source()) + " -> " +
                       str(listOfJourneys[i].destination()));
            }

            // Set the journey numbers for each journey:
            // Journey i's journey number is i
            for(int i = 0; i < listOfJourneys.size(); i++)
                listOfJourneys[i].setJourneyNum(i);
            mainGraph.set(basicGraph, listOfJourneys);

            int shortestPathCost = 0;
            for(int i = 0; i < heuristics.size(); i++) {
                graphGroup g = heuristics[i].func(mainGraph, listOfJourneys);
                dumpGraph(g,heuristics[i].name);
                int result = 0;
                for(int n = 0; n < listOfJourneys.size(); n++)
                    result += g.returnSharedCost(n).value();
                if(i == 0)
                    shortestPathCost = result;
                output("Running heuristic: " + heuristics[i].name);
                output("\tHas total cost of: " + str(result));
                if(i > 0)
                    output("\tImprovement over shortest path: " +
                           str(shortestPathCost - result));
                output("");
            }

            if(inFile != &cin)
                delete inFile;

        }

        return 0;
    }
}