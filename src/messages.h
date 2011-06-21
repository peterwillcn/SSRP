#ifndef _MESSAGES_H_
#define _MESSAGES_H_

/**
 * @file: messages.h
 *
 * Contains common messages for the user including the usage information,
 * the welcome banner, and the heuristic information.
 */

#include <string>

using namespace std;

#include "ioFunctions.h"

const string usage
= String("") +
String("Usage:\n", Color::White) +
"    " + String("graph mode modeOptions\n", Color::Green) +
"\n" +
String("Modes:\n", Color::White) +
"\n" +
"    " + String("graph stat\n", Color::Green) +
"    " + String("graph stats\n", Color::Green) +
"\n" +
"    " + String("Options:\n", Color::White) +
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
"    " + String("graph demo\n", Color::Green) +
"\n" +
"    " + String("Options:\n", Color::White) +
"        -f FILE\n" +
"            Specifies an input file to use. If none is given, uses stdin.\n" +
"\n" +
"    " + String("Options Common to Both Modes:\n", Color::White) +
"        -p\n" +
"            Prints all graphs to a file.\n" +
"        -np\n" +
"            Do not print graphs to files. (Default)\n" +
"        -h\n" +
"            Print this message and exit. (Should be used without a mode)\n" +
"        -b\n" +
"            Use bi-directional sharing.\n" +
"        --dease INT INT INT\n" +
"            Specify the weight thresdhold, number of passes, and journey\n" +
"            threshold, respectively, for the dease algorithm.\n" +
"        --pareto\n" +
"            Use pareto equilibriums in the nash equilibrium finder.\n" +
"\n" +
"    " + String("For information on heuristics, run ", Color::White) +
String("graph --heuristics-info", Color::Green) + "\n";

const string welcomeHeader = "\
+------------------------------------------------------------------------------+\n\
|                          Shared Shorest Path Project                         |\n\
| Authors: Christopher Earl (2006)                                             |\n\
|          Brooks Emerick (2008)                                               |\n\
|          Sean Quigley (2009)                                                 |\n\
|          Nicole Peterson (2010)                                              |\n\
|          Ronald Fenelus (2011)                                               |\n\
|          Zeal Jagannatha (2011)                                              |\n\
| Mentor:  " + String("Sean McCulloch", Color::Red) + "                                                      |\n\
+------------------------------------------------------------------------------+\n";


const string heuristicsInfo = string("") +
String("Heuristic Information:", Color::Green) + "\n" +
"\n"
"    " + String("Dease Algorithm:", Color::White) + " (Dease)\n" +
"        Finds edges that are commonly shared and deletes them. This is to\n" +
"        encourage sharing and try to find a nash equilibrium.\n" +
"\n"
"    " + String("Nash Equilibrium:", Color::White) + " (Nash-Equilib)\n" +
"        This is the vanilla version of the nash equilibrium algorithm.\n" +
"        Everything is routed by their shortest paths, and then the nash\n" +
"        equilibrium algorithm is run on them.\n" +
"\n"
"    " + String("Shortest Path:", Color::White) + " (Shortest)\n" +
"        This is the basis of comparison for our other algorithms. It routes\n" +
"        things by their shortest paths.\n" +
"\n"
"    " + String("Spanning Tree:", Color::White) + " (SpanTree)\n" +
"        This is the vanilla version of the spanning tree algorithm. It finds the\n" +
"        spanning tree for a graph, then routes journeys on the spanning tree.\n" +
"\n"
"    " + String("Spanning Tree / Nash Equilibrium:", Color::White) + " (SpanNash)\n" +
"        This algorithm finds the spanning tree for a graph and then routes\n" +
"        journeys on this spanning tree. It then transforms these routes back\n" +
"        into the original graph, and runs the nash equilibrium heuristic.\n" +
"\n"
"    " + String("Sub-Graph:", Color::White) + " (Sub-Graph)\n" +
"        This is a theoretical algorithm used to prove statistically that there\n" +
"        is always a nash equilibrium in certain types of graphs. This algorithm\n" +
"        does considerably worse than most other algorithms, and so is not in use.\n";

#endif