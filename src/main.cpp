/* main.cpp
 *
 * This is the main file for the project.
 * Any control-based things (like a new way to evaluate graphs or examples)
 * should go here.
 */

// Include all the C library headers.
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

// Include the user-written headers.

// The color library. (TODO This isn't the proper file)
#include "colorString.h"

// The options header.
#include "options.h"

// graph stuff
#include "basicEdgeGroup.h"
#include "graphGroup.h"

// Input Output function header
#include "ioFunctions.h"

// Heuristics header
#include "heuristics.h"

// The random generation header
// (This is the file that contains the generate* functions.)
#include "rand.h"

// The nash equilibrium finder header
#include "nashTest.hpp"

// The messages header.
// (Contains long strings so that they're not lingering at the top of this file.)
#include "messages.h"

// Used for the timer.
const long ONE_BILLION = 1000000000;

// We have to do this explicitly
// since bison doesn't add this declaration to it's header.
int yyparse();

// Used in the doStats function to keep track of statistics
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

// This is the master function for the statistics mode.
// It generates graphs and uses the heuristics to approximate solutions to them,
// and keeps track of results for statistics information.
void doStats() {

    // Some helpful information.
    // Can be moved into the debug output level by uncommenting the if-statement.
    //if(debug) {
        cout << "Using stat mode.\n";
        cout << "Vertices:   " << STATvertices << endl;
        cout << "Journeys:   " << STATjourneys << endl;
        cout << "Min Weight: " << STATminWeight << endl;
        cout << "Max Weight: " << STATmaxWeight << endl;
        cout << "Count:      " << STATcount << endl;
        cout << "Directed:   " << boolalpha << STATdirected << endl;
    //}

    // This prints the top row with the spacers and the heuristic names.
    pad(" ", 10); output("|", "");
    for(unsigned i = 0; i < heuristics.size(); i++){
        outputCenter(heuristics[i].name, heuristics[i].name.size()+2);
        output("|", "");
    }
    output(" Time (s)");

    // This is the vector to keep track of the heuristic information.
    vector<triple<int,double,double> > numberCorrect(heuristics.size(),
                                                     triple<int,double,double>(0,
                                                                               0.0,
                                                                               0.0));
    // There is one entry in the vector for each heuristic.
    // The first entry is an integer containing the number of times the heuristic has done best (or tied for best).
    // The second entry is a double for keeping track of how many times it won as a weighted number.
    //          (e.g. Each tie adds 0.5 pts to the winning players.)
    // The third entry is a double for keeping the time used by each heuristic.

    // Run through each case (newly generated graph)
    for(unsigned caseNumber = 0; caseNumber < STATcount; caseNumber++) {

        // This prints the stuff on the left with the case number
        // And the spacer
        int graphNum = getGraphNumber();
        output("Case:", "");
        outputRight(str(graphNum),5);
        output("|", "");

        basicEdgeGroup g;
        graphGroup mainGraph;
        vector<journeyInfo> listOfJourneys;

        // Generate a new graph to use.
        generateSparseGraph(g,
                            STATvertices,
                            STATdirected,
                            STATminWeight,
                            STATmaxWeight);

        // Generate new journeys to use.
        listOfJourneys.resize(STATjourneys);
        for(unsigned i = 0; i < STATjourneys; i++)
            listOfJourneys[i].setJourneyNum(i);
        generateJourneys(listOfJourneys, STATvertices);
        mainGraph.set(g, listOfJourneys);

        // Create a vector to store the results.
        vector<floatWInf> results(heuristics.size());

        // Create a vector to store time information.
        vector<double> times(heuristics.size(), 0.0);

        // Run each heuristic
        for(unsigned i = 0; i < heuristics.size(); i++) {
            // Start the timer.
            timespec sTime;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &sTime);

            // Actually run the heuristic
            graphGroup g = heuristics[i].func(mainGraph,
                                              listOfJourneys);

            // If the heuristic uses the Nash Finder, the run it here.
            if(heuristics[i].useNashAlgorithm)
                nashEquilibrium(g);

            // Stop the timer.
            timespec eTime;
            clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &eTime);

            // Convert the time to seconds.
            double startTime = sTime.tv_sec + (double(sTime.tv_nsec)/ ONE_BILLION);
            double endTime = eTime.tv_sec + (double(eTime.tv_nsec)/ ONE_BILLION);

            // Print the graph to a PDF file. (For alternative filetypes, see options.h)
            dumpGraph(g,heuristics[i].name);

            // Calculate the total shared cost for the graph.
            results[i] = g.totalSharedCost();

            // Calculate and store the time taken for the heuristic.
            times[i] = endTime - startTime;
            numberCorrect[i].third += times[i];
        }

        // Find the heuristic(s) that had the minimum cost.
        floatWInf best = floatWInf(true, 0);
        int numBest = 0;
        for(unsigned i = 0; i < heuristics.size(); i++) {
            if(results[i] < best) {
                best = results[i];
                numBest = 1;
            }
            else if(results[i] == best) {
                numBest++;
            }
        }

        // Calculate the total time taken for the heuristics while we print
        // the results from running the heuristics.

        // Store the total time for all the heuristics on the current graph.
        double totalTime = 0;
        for(unsigned i = 0; i < heuristics.size(); i++) {

            // Add up the total time
            totalTime += times[i];

            // If the heuristic did the best (or tied for best),
            // The print the text in green. (And add some stuff up)
            if(results[i] == best) {
                numberCorrect[i].first++;
                numberCorrect[i].second += 1.0 / double(numBest);
                outputGreenRight(str(results[i]), heuristics[i].name.size()+2);
                output("|", "");
            }
            // If it didn't do the best, then print it in standard color.
            else {
                outputRight(str(results[i]), heuristics[i].name.size()+2);
                output("|", "");
            }
        }

        // Output the total time it took to run all the heuristcs on the graph.
        output(string(" ") + str(totalTime));

        // Increment the graph number for file consistency.
        incrementGraphNumber();
    }

    // After we're done running all the heuristics on each graph,
    // We can print the totals

    // This prints the top row of the results.
    // Including the left "Totals:" and the heuristic names.
    outputLeft("Totals:", 10);
    output("|", "");
    for(unsigned i = 0; i < heuristics.size(); i++) {
        outputCenter(heuristics[i].name, heuristics[i].name.size()+2);
        output("|", "");
    }
    output("");

    // Output the total number of wins for each heuristic.
    pad(" ", 10);
    output("|", "");
    for(unsigned i = 0; i < heuristics.size(); i++) {
        output(str(numberCorrect[i].first), "");
        outputRight(str(numberCorrect[i].second, 4),
                    heuristics[i].name.size()+2
                    -str(numberCorrect[i].first).size());
        output("|", "");
    }
    output("");

    // Output the total time for each heuristic.
    outputLeft("Time (s):", 10);
    output("|", "");
    double totalTime = 0;
    for(unsigned i = 0; i < heuristics.size(); i++) {
        outputRight(str(double(numberCorrect[i].third)),
                    heuristics[i].name.size()+2);
        output("|", "");
        totalTime += double(numberCorrect[i].third);
    }
    output(" " + str(totalTime, 3));

    // Output the time percentage for each heuristic.
    outputLeft("Time (%):", 10);
    output("|", "");
    for(unsigned i = 0; i < heuristics.size(); i++) {
        outputRight(str(((double(numberCorrect[i].third)) * 100.0)  / totalTime),
                    heuristics[i].name.size()+2);
        output("|", "");
    }
    output("");
}

// The main function.
// Parses command line arguments using bison,
// And either calls doStats() or runs the demo program.
int main(int argc, char* argv[]) {

    // Output the welcome banner.
    output(welcomeHeader);

    // This just moves the command line arguments into a string stream.
    ostringstream temp;
    for(unsigned i = 1; i < unsigned(argc); i++) {
        temp << argv[i] << " ";
    }

    // Setup the string stream yyin as the input file for bison:

    // Create the istringstream.
    istringstream* yyin = new istringstream(temp.str());

    // Setup the scanner with that input file.
    scanner = new yyFlexLexer(yyin);

    // Call the parser's main function.
    yyparse();

    // Delete the scanner object, since we're not using it anymore.
    delete scanner;

    if(numErrors > 0) {
        output("");
        output(usage);
        return 1;
    }

    // If we are supposed to print heuristics information,
    // Print the heuristics info and quit.
    if(printHeuristicsInfo) {
        output(heuristicsInfo);
        return 0;
    }

    else {

        // This sets up the heuristics. (heuristics.h)
        setupHeuristics();

        // If we're in Stat Mode:
        // Call the stat function.
        if(programMode == STAT) {

            doStats();

        }


        // If we're in Demo Mode:
        // The run the demo program.
        else {

            // If we are supposed to get input from a file, then setup the input stream.
            if(readFromFile) {
                inFile = new ifstream(inFileName.data());
            }
            else
                // If not, use cin
                inFile = &cin;

            // Create the graph data structures.
            graphGroup mainGraph;
            basicEdgeGroup basicGraph;
            vector<journeyInfo> listOfJourneys;

            // Generate the graph and journeys
            // These functions are in ioFunctions.h
            readGraph(basicGraph);
            readJourneys(listOfJourneys, basicGraph);

            // Print out the journeys.
            for(unsigned i = 0; i < listOfJourneys.size(); i++) {
                output("Journey " +str(i)+ ": ", "");
                output(str(listOfJourneys[i].source()) + " -> " +
                       str(listOfJourneys[i].destination()));
            }

            // Set the journey numbers for each journey:
            // Journey i's journey number is i
            for(unsigned i = 0; i < listOfJourneys.size(); i++)
                listOfJourneys[i].setJourneyNum(i);
            // Associate the journeys to the graph.
            mainGraph.set(basicGraph, listOfJourneys);

            // Run the heuristics.
            int shortestPathCost = 0;
            for(unsigned i = 0; i < heuristics.size(); i++) {
                // Output the message here to tell us we're starting a heuristic.
                output("Running heuristic: " + heuristics[i].name);

                // Run the heuristic and store the resulting graph
                graphGroup g = heuristics[i].func(mainGraph, listOfJourneys);

                // If the algorithm uses the Nash Finder, the run it.
                if(heuristics[i].useNashAlgorithm)
                    nashEquilibrium(g);

                // Dump the resulting graph into a file.
                dumpGraph(g,heuristics[i].name);

                // Computer the total shared cost of the graph.
                int result = g.totalSharedCost().value();

                // If this is the shortest path, store it in shortest path cost.
                if(i == 0)
                    shortestPathCost = result;

                // Output the cost information.
                output("\tHas total cost of: " + str(result));
                if(i > 0)
                    // Output the comparison information with shortest path.
                    output("\tImprovement over shortest path: " +
                           str(shortestPathCost - result));
                output("");
            }

            // If we used another file other than cin for input, delete the pointer.
            if(inFile != &cin)
                delete inFile;

        }

        // Return success
        return 0;
    }
}
