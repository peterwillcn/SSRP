#ifndef _MESSAGES_H_
#define _MESSAGES_H_

const string usage =
String("") +
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
"            threshold, respectively, for the dease algorithm.\n";

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
| Mentor:  " + String("Sean McCulloch", Color::Red) + "                                                      |\n\
+------------------------------------------------------------------------------+\n";

#endif