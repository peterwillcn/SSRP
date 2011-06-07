#include "ioFunctions.h"
#include "rand.h"
#include "graphGroup.h"
#include "options.h"
#include "color.h"
#include <limits.h>
#include <signal.h>
#include <fstream>
#include <sstream>
#include <iomanip>
using namespace std;

const bool YES = true;
const bool NO = false;

////
//// Main I/O Functions:
////

// Reads in an integer from cin
int inputInt(const string& prompt) {
    if(not(readFromFile))
        cout << prompt << " ";
    int item;
    (*inFile) >> item;
    return item;
}

// Reads in an integer in the range [low, high) from cin
int inputBoundedInt(const string& prompt, int low, int high) {
    while(true) {
        if(not(readFromFile))
            cout << prompt << " [ " << low << " , " << high << " ) ";
        int item;
        (*inFile) >> item;
        if(item < low || item >= high || cin.fail() || cin.eof()) {
            cin.clear();
            if(not(readFromFile))
                cout << "Illegal value.\n";
        }
        else
            return item;
    }
}

// Reads in a string from cin
string inputString(const string& prompt) {
    while(true) {
        if(not(readFromFile))
            cout << prompt << " ";
        string item;
        (*inFile) >> item;
        if(cin.fail() || cin.eof()) {
            cin.clear();
            if(not(readFromFile))
                cout << "Illegal value.\n";
        }
        else
            return item;
    }
}

// Returns the string form of an integer
string str(int i) {
    ostringstream s;
    s << i;
    return s.str();
}

// Returns the string form of a float
string str(float f, int precision) {
    ostringstream s;
    s << setprecision(precision) << f << fixed;
    return s.str();
}

// Returns the string form of a double
string str(double d, int precision) {
    ostringstream s;
    s << setprecision(precision) << d << fixed;
    return s.str();
}

// Returns the string form of an unsigned
string str(unsigned u) {
    ostringstream s;
    s << u;
    return s.str();
}

// Returns the string form of a floatWInf
string str(floatWInf f) {
    ostringstream s;
    s << f;
    return s.str();
}

// Outputs a string to cout. Appends suffix to the end
void output(const string& s, const string& suffix) {
    cout << s << suffix;
}
// Like output, but doesn't print when reading from a file.
void outputPrompt(const string& s, const string& suffix) {
    if(not(readFromFile))
        cout << s << suffix;
}

void outputRed(const string& s, const string& suffix) {
    cout << FGRED << s << ENDC << suffix;
}

void outputGreen(const string& s, const string& suffix) {
    cout << FGGREEN << s << ENDC << suffix;
}

// Outputs a string to cout with a particular alignment and width
void outputLeft(const string& s, int w) {
    if(w <= s.size())
        cout << s;
    else {
        outputLeft(s, w-1);
        cout << " ";
    }
}
void outputRight(const string& s, int w) {
    if(w <= s.size())
        cout << s;
    else {
        cout << " ";
        outputRight(s, w-1);
    }
}
void outputCenter(const string& s, int w) {
    if(w <= s.size())
        cout << s;
    else if(w == s.size()+1)
        cout << s << " ";
    else {
        cout << " ";
        outputCenter(s, w-2);
        cout << " ";
    }
}

void outputGreenLeft(const string& s, int w) {
    if(w <= s.size())
        cout << FGGREEN << s << ENDC;
    else {
        outputGreenLeft(s, w-1);
        cout << " ";
    }
}

void outputGreenRight(const string& s, int w) {
    if(w <= s.size())
        cout << FGGREEN << s << ENDC;
    else {
        cout << " ";
        outputGreenRight(s, w-1);
    }
}

void outputGreenCenter(const string& s, int w) {
    if(w <= s.size())
        cout << FGGREEN << s << ENDC;
    else if(w == s.size()+1)
        cout << s << " ";
    else {
        cout << " ";
        outputGreenCenter(s, w-2);
        cout << " ";
    }
}

void outputRedLeft(const string& s, int w) {
    if(w <= s.size())
        cout << FGRED << s << ENDC;
    else {
        outputRedLeft(s, w-1);
        cout << " ";
    }
}

void outputRedRight(const string& s, int w) {
    if(w <= s.size())
        cout << FGRED << s << ENDC;
    else {
        cout << " ";
        outputRedRight(s, w-1);
    }
}

void outputRedCenter(const string& s, int w) {
    if(w <= s.size())
        cout << FGRED << s << ENDC;
    else if(w == s.size()+1)
        cout << s << " ";
    else {
        cout << " ";
        outputRedCenter(s, w-2);
        cout << " ";
    }
}

void pad(const string& s, int w) {
    if(w <= 0)
        return;
    else {
        cout << s;
        pad(s, w-1);
    }
}

// Reads in a boolean answer from cin.
// Yes/No answer
bool getChoice(string prompt) {
    while(true) {
        if(not(readFromFile))
            cout << prompt << " ";
        string temp;
        (*inFile) >> temp;
        switch(temp[0]) {
            case 'Y':
            case 'y':
            case '1':
                return YES;
                break;
            case 'N':
            case 'n':
            case '0':
                return NO;
                break;
            default:
                if(cin.fail())
                    cin.clear();
                if(not(readFromFile)) {
                   cout << "Illegal choice.\n";
                }
                else {
                    cout << '"' << temp << "\"\n";
                    throw SIGSEGV;
                }
        }
    }
}

static bool graphNumberFound = false;
static int graphNumber = -1;
int getGraphNumber() {
    if(not(graphNumberFound)) {
        graphNumberFound = true;
        {
            ifstream config(configFile.data());
            if(config.fail())
                graphNumber = 0;
            else {
                config >> graphNumber;
                config.close();
            }
        }
        {
            ofstream config(configFile.data());
            config << graphNumber+1;
            config.close();
        }
    }
    return graphNumber;
}

void incrementGraphNumber() {
    graphNumber++;
    {
        ofstream config(configFile.data());
        config << graphNumber;
        config.close();
    }
}

////
//// Graph I/O Functions:
////

//readGraph()
// reads in graph from user
//
//pre:
// -inputGroup is a basicEdgeGroup
//
//post:
// -inputGroup has been set by user
//
void readGraph(basicEdgeGroup & inputGroup)
{
    if(getChoice("Generate a random graph?")) {
        generateGraph(inputGroup);
    }
    else
        readGraphFromFile(inputGroup);

}

//readGraphs()
// reads in graphs from user
//
//pre:
// -inputGroups is vector of a basicEdgeGroups
//
//post:
// -inputGroups has been set by user
//
// void readGraphs(vector< basicEdgeGroup > & inputGroups) {
//     int numGraphs = inputInt("How many graphs are there?");
//     inputGroups.resize(numGraphs);
//     for(int i = 0; i < inputGroups.size(); i++)
//         readGraph(inputGroups[i]);
// }

//readGraphFromFile()
// reads graph from a user selected file
//
//pre:
// -inputGroup is a basicEdgeGroup
//
//post:
// -inputGroup has been set from file
void readGraphFromFile(basicEdgeGroup & inputGroup)
{

    /*
    * Style of file:
    *   n
    *   infinitySymbol
    *   00 01 02 03 ... 0(n-2) 0(n-1)  [edge weights for ij ]
    *   10 11 12 13 ... 1(n-2) 1(n-1)    .
    *   .  .  .  .  ... .  .   .   .     .
    *   .  .  .  .  ... .  .   .   .     .
    *   .  .  .  .  ... .  .   .   .     .
    *   (n-1)0 (n-1)1  ... (n-1)(n-1)    .
    */

    string fileName = "aa.txt";  //holds file name of file for input
    int n;  //number of vertices
    int type;  //type of graph
    int style;  //style of graph
    floatWInf infiniteWeight(true, 0);  //float used to hold infinity
    string infinitySymbol; //holds symbol of infinity in file
    fstream fin;

    fileName = inputString("Input file name:");

    //read in header info
    fin.open(fileName.data());
    fin >> n;
    inputGroup.setN(n);
    fin >> infinitySymbol;
    inputGroup.setType(0);
    inputGroup.setStyle(0);

    //read in graph info
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            string temp;
            fin >> temp;
            if(temp == infinitySymbol)
                inputGroup.addEdge(i, j, infiniteWeight);
            else {
                float f;
                istringstream in(temp);
                in >> f;
                inputGroup.addEdge(i, j, f);
            }
        }
    }

    fin.close();
}

//            exportGraph()
// - pre: The graph has been created
// - post: The graph data has been exported to a specified file, in the format
//          expected from "readGraphFromFile"
//         Uses -1 for the infinity symbol
void exportGraph(basicEdgeGroup& outputGroup){
    cout << "Enter the filename to export to:";
    string filename;
    cin >> filename;
    ofstream fout;
    fout.open(filename.data());
    //output size and infinity symbol
    fout << outputGroup.returnN() << endl;
    fout << -1 << " ";
    //now the graph info

    for(int i = 0; i < outputGroup.returnN(); i++){
        for(int j = 0; j < outputGroup.returnN(); j++){
            floatWInf edge_cost = outputGroup.cost(i,j);
            if(edge_cost.isInfinity())
                fout << -1 << " ";
            else
                fout << edge_cost.value() << " ";
        }
        fout << endl;
    }
}

// Dumps a graph to a file named "graph.dot"
// Then runs graphviz on the file to produce an output file.
void dumpGraph(const graphGroup& g, const string& fileLabel) {
    if(dumpGraphToFile) {
        int graphNum = getGraphNumber();
        ofstream fout(".graph.dot");

        vector<string> colors;
        vector<path> paths = g.returnSharedPaths();

        colors.push_back("red");
        colors.push_back("blue");
        colors.push_back("green");
        colors.push_back("orange");
        colors.push_back("purple");
        colors.push_back("yellow");

        if(g.directed())
            fout << "di";
        fout << "graph G {\n\tgraph [ bgcolor=\""+background+"\" ];\n";

        if(useDoubleEndpoints) {
            fout << "\tnode [shape=doublecircle] ";
            for(int i =0 ; i < paths.size(); i++) {\
                fout << paths[i].actualPath()[0] << " " << paths[i].actualPath()[paths[i].actualPath().size()-1] << " ";
            }
        }
        fout << "\n\tnode [shape=circle];\n";

        if(g.directed()) {
            for(int i = 0; i < g.returnN(); i++) {
                for(int j = 0; j < g.returnN(); j++) {
                    if(not(g.totalEdgeCost(i, j).isInfinity())) {
                        if(i != j) {
                            fout << "\t" << i << " -> " << j << " ";
                            fout << " [ ";
                            fout << "label = \"" << g.totalEdgeCost(i, j).value() << "\" ";
                            fout << "len = " << g.totalEdgeCost(i, j).value() << ".0 ";
                            bool edgeUsed = false;
                            vector<string> edgeColors;
                            for(int pathNum = 0; pathNum < paths.size(); pathNum++) {
                                for(int pathPart = 1; pathPart < paths[pathNum].actualPath().size(); pathPart++) {
                                    if((paths[pathNum].actualPath()[pathPart] == j &&
                                        paths[pathNum].actualPath()[pathPart-1] == i)) {
                                        edgeColors.push_back(colors[pathNum%colors.size()]);
                                        edgeUsed = true;
                                    }
                                }
                            }
                            if(edgeUsed) {
                                fout << "color=\"";
                                for(int i = 0; i < edgeColors.size(); i++) {
                                    fout << edgeColors[i];
                                    if(i < edgeColors.size()-1)
                                        fout << ":";
                                }
                                fout << "\" ";
                            }
                            fout << "];\n";
                        }
                    }
                }
            }
        }
        else {
            for(int i = 0; i < g.returnN(); i++) {
                for(int j = i+1; j < g.returnN(); j++) {
                    if(not(g.totalEdgeCost(i, j).isInfinity())) {
                        fout << "\t" << i << " -- " << j << " ";
                        fout << " [ ";
                        fout << "label = \"" << g.totalEdgeCost(i, j).value() << "\" ";
                        bool edgeUsed = false;
                        vector<string> edgeColors;
                        for(int pathNum = 0; pathNum < paths.size(); pathNum++) {
                            for(int pathPart = 1; pathPart < paths[pathNum].actualPath().size(); pathPart++) {
                                if((paths[pathNum].actualPath()[pathPart] == j &&
                                    paths[pathNum].actualPath()[pathPart-1] == i) ||
                                    (paths[pathNum].actualPath()[pathPart] == i &&
                                    paths[pathNum].actualPath()[pathPart-1] == j)) {
                                    edgeColors.push_back(colors[pathNum%colors.size()]);
                                    edgeUsed = true;
                                }
                            }
                        }
                        if(edgeUsed) {
                            fout << "color=\"";
                            for(int i = 0; i < edgeColors.size(); i++) {
                                fout << edgeColors[i];
                                if(i < edgeColors.size()-1)
                                    fout << ":";
                            }
                            fout << "\" ";
                        }
                        fout << "];\n";
                    }
                }
            }
        }

        if(printLabelNodes) {
            for(int i = 0; i < paths.size(); i++) {
                fout << "node [shape=circle ";
                fout << "label=\"Journey " << i << "\\n";
                fout << paths[i].actualPath()[0] << " -> " << paths[i].actualPath()[paths[i].actualPath().size()-1];
                fout << "\" ";
                fout << "color=\"" << colors[i%colors.size()] << "\"]; j" << i << ";\n";
            }
        }

        fout << "}\n";

        fout.close();

        string cmd;
        cmd = graphvizCmd  + " -T" + graphFormat +
            " -o graph" + str(graphNum) + "_" + fileLabel + "." +
            graphFormat + " .graph.dot";
        system(cmd.data());
        //system("rm .graph.dot");

    }
}

// print a graph
void printGraph(const graphGroup& g) {

    output("Printing graph with current costs:");
    //output(str(g.returnN()) + " vertices");

    for(int i = 0; i < g.returnN(); i++)
    {
        for(int j = 0; j < g.returnN(); j++)
        {
            if(g.totalEdgeCost(i, j).isInfinity() == true) {

                outputLeft(InfinitySymbol, 5);
            }
            else {
                outputLeft(str(g.totalEdgeCost(i, j).value()), 5);
            }
        }
        cout << endl;
    }
    cout << endl;

}

////
//// Journey I/O Functions:
////

//readJourneys()
// reads journeys from user
//
//pre:
// -journeysInformation is a vector of valid journeyInfo's
//
//post:
// -journeysInformation has journey information given by user
//
void readJourneys(vector< journeyInfo > & journeysInformation, const basicEdgeGroup& g)
{
    const int numberVertices = g.returnN();

    if(getChoice("Read journeys from file?"))
        readJourneysFromFile(journeysInformation);
    else
    {
        int numJourneys = inputInt("How many journeys to create?");
        if(getChoice("Create random journeys?"))
        {
            journeysInformation.resize(numJourneys);
            for(int i = 0; i < numJourneys; i++)
                journeysInformation[i].setJourneyNum(i);
            generateJourneys(journeysInformation, numberVertices);
        }
        else
        {
            journeysInformation.resize(numJourneys);
            for(int i = 0; i < numJourneys; i++)
            {
                journeysInformation[i].setJourneyNum(i);
                journeysInformation[i].setSource(inputInt("Source of journey "+str(i)+":"));
                journeysInformation[i].setDestination(inputInt("Destination of journey "+str(i)+":"));
            }
        }
    }
}

//readJourneysFromFile()
// reads journey info from user selected file
//
//pre:
// -journeysInformation is a vector of valid journeysInfo's
//
//post:
// -journeysInformation has journey info from user selected file
//
void readJourneysFromFile(vector< journeyInfo > & journeysInformation) {
    /*
    * Format of file:
    *   numJourneys
    *   source0 destination0
    *   source1 destination1
    *   .           .
    *   .           .
    *   .           .
    *   source(n-1) destination(n-1)
    */
    char usersAnswer;   //holds user's answer
    string fileName;    // holds the filename of the input file
    int testNumber;     //holds file/test number
    int tempVertex = 0; //holds vertex number while reading from file
    int numJourneys;    //number of journeys
    fstream fin;

    fileName = inputString("Input filename to read from: ");

    fin.open(fileName.data());
    fin >> numJourneys;
    journeysInformation.resize(numJourneys);

    //read in journeys
    for(int i = 0; i < numJourneys; i++) {
        fin >> tempVertex;
        journeysInformation[i].setSource(tempVertex);
        fin >> tempVertex;
        journeysInformation[i].setDestination(tempVertex);
    }
    fin.close();
}

// print all info on journeys
void printJourneys(const journeyGroup& jgroup) {
    for(int i = 0; i < jgroup.numJourneys(); i++) {
        output("Journey " + str(i) + ":");
        printJourney(jgroup[i]);
    }
}

// print all info on a journey
void printJourney(const journey& j) {
    printJourneyCost(j);
    printJourneyPath(j);
}

// print actual paths of a journey
void printJourneyPaths(const journeyGroup& jgroup) {

    cout << "Paths for journeys: " << endl;
    for(int i = 0; i < jgroup.numJourneys(); i++)
        printJourneyPath(jgroup[i]);

}

// print actual paths of a journey
void printJourneyPath(const journey& j) {

    cout << "\tSingle Path: ";
    if(j.hasSinglePath() == true) {
        for(int i = 0; i < j.singleActualPath().size(); i++)
            cout << j.singleActualPath()[i] << " ";
    }
    else {
        cout << "Journey not found between " <<
        j.getSource() << " and " << j.getDestination() << ".";
    }
    cout << endl;

    cout << "\tShared Path: ";
    if(j.hasSharedPath() == true) {
        for(int i = 0; i < j.sharedActualPath().size(); i++)
            cout << j.sharedActualPath()[i] << " ";
    }
    else {
        cout << "Journey not found between " <<
        j.getSource() << " and " << j.getDestination() << ".";
    }
    cout << endl;

}

// print shared & single costs && savings of a journey
void printJourneyCosts(const journeyGroup& jgroup) {

    cout << "Costs for journeys: " << endl;
    for(int i = 0; i < jgroup.numJourneys(); i++)
        printJourneyCost(jgroup[i]);

}

// print shared & single costs && saving of a journey
void printJourneyCost(const journey& j) {
    cout << "\tSingle Path Cost: ";
    if(j.hasSinglePath() == true)
        cout << j.singleCost().value() << "." << endl;
    else {
        cout << "Journey not found between " <<
        j.getSource() << " and " << j.getDestination() << ".\n";
    }

    cout << "\tShared Path Cost: ";
    if(j.hasSharedPath() == true)
        cout << j.sharedCost().value() << "." << endl;
    else {
        cout << "Journey not found between " <<
        j.getSource() << " and " << j.getDestination() << ".\n";
    }

}