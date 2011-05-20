#include "ioFunctions.h"
#include "rand.h"
#include "graphGroup.h"
#include <fstream>
#include <sstream>
using namespace std;

const bool YES = true;
const bool NO = false;

///
///read functions
///

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

    bool usersAnswer;  //holds user's answer
    int n;  //number of vertices
    int type;  //type of graph
    int style;  //style of graph
    int numberOfInfiniteEdges;  //holds number of infinite edges
    int numberOfJourneys;  //holds number of journeys

    usersAnswer = getChoice("Generate a random graph? ");
    if(usersAnswer)
    {
        cout << endl << "Types: " << endl
        << "0 - finite weights" << endl
        << "1 - some random infinite weights - Style: # of infinite weights < (n - 2)" << endl
        << "2 - limited directional movement" << endl
        << "3 - highway system" << endl
        << "4 - threaded grid" << endl;
        cout << endl;
        type = inputInt("What is the type of the graph? ");
        n = inputInt("How many vertices? ");
        if(type == 1)
        {
            style = inputInt("What is the style of the graph? ");
            while(type == 1 && style > n)
            {
                cout << endl;
                ostringstream s;
                s << "Too many edges. Use less than " << n - 2 << "edges. Style: ";
                style = inputInt(s.str());
            }
        }
        else
            style = 0;
        cout << endl;
        generateGraph(inputGroup, n, type, style);
    }
    else
        readGraphFromFile(inputGroup);

}

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
    float tempWeight;  //float used to hold weight while reading from input file
    floatWInf infiniteWeight(true, 0);  //float used to hold infinity
    float infinitySymbol; //holds symbol of infinity in file
    fstream fin;

    fileName = inputString("Input file name: ");

    //read in header info
    fin.open(fileName.data());
    fin >> n;
    inputGroup.setN(n);
    fin >> infinitySymbol;
    inputGroup.setType(0);
    inputGroup.setStyle(0);

    //read in graph info
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            fin >> tempWeight;
            if(tempWeight == infinitySymbol)
                inputGroup.addEdge(i, j, infiniteWeight);
            else
                inputGroup.addEdge(i, j, tempWeight);
        }

        fin.close();

}

//generateGraph
// generates random graph with user selected properties
//
//pre:
// -inputGroup is a basicEdgeGroup
//
//post:
// -inputGroup has been set randomly with user selected properties
void generateGraph(basicEdgeGroup & randomGraph, int n, int type, int style)
{

    char usersAnswer;
    bool directed;  //true if graph is directed
    int numOfRanges;  //number Of ranges
    vector< vector< int > > ranges;  //holds ranges
    vector< int > vertexList;  //holds list of unused vertices
    vector< int > whichRange;  //holds which vertex goes in which range
    whichRange.resize(n);
    int tempValue;  //temporarily holds value for different jobs
    int rangeIncrement;  //how many vertices are in each range
    int currentRange;  //which range is being used currently
    int limitedback;  //how far backward
    int limitedforward;  //how far forward
    int highway; //how many vertices in highway
    int levels; //how many levels there are
    int jumping; //how many levels a vertex can jump
    int perLevel; //how many vertices on each level
    int currentLevel1; //which level is currently being looked at
    int currentLevel2; //which level is currently being looked at
    int levelDifference; //difference between currentLevels
    int i;  //i and j used for infinite edge finding and checking
    int j;
    int numberOfEdgesLeft;  //holds countdown for adding infinite edges
    floatWInf infiniteWeight(true, 0);  //float used to hold infinity

    randomGraph.setN(n);

    if((type == 0) || (type == 1))  //finite weights or some random infinite weights
    {
        //read in information
        cout << "Directed or Undirected? (d/u) ";
        cin >> usersAnswer;
        if(usersAnswer == 'd')
            directed = true;
        else
            directed = false;

        cout << "Multiple ranges? (y/n) ";
        cin >> usersAnswer;
        if(usersAnswer == 'y')
        {
            cout << "How many ranges? (>0) ";
            cin >> numOfRanges;
        }
        else
            numOfRanges = 1;

        ranges.resize(numOfRanges);
        for(int m = 0; m < numOfRanges; m++)
        {
            ranges[m].resize(2); //first is min, second is max
            cout << "What is min of range " << m << "? ";
            cin >> tempValue;
            ranges[m][0] = tempValue;
            cout << "What is max of range " << m << "? ";
            cin >> tempValue;
            ranges[m][1] = tempValue;
        }

        //begin work
        if(directed == true)  //directed graph
        for(int k = 0; k < n; k++)
            if(numOfRanges == 1) //only one range
            for(int l = 0; l < n; l++)
                //select random weights
            if(k == l)
                randomGraph.addEdge(k, l, 0);
            else
                randomGraph.addEdge(k, l, randomWeight(ranges[0][0], ranges[0][1]));
            else  //multiple ranges
            {
                //select order for vertices
                vertexList.resize(n);
                for(int l = 0; l < n; l++)
                    vertexList[l] = l;

                //set random ranges (whichRange at the end of the loop has all vertices listed in a random order)
                    for(int l = 0; l < n; l++)
                    {
                        tempValue = randomWeight(0, vertexList.size());
                        whichRange[l] = vertexList[tempValue];
                        vertexList[tempValue] = vertexList[vertexList.size() - 1];
                        vertexList.resize(vertexList.size() - 1);
                    }

                    //select random weights
                    rangeIncrement = n / numOfRanges;
                    for(int l = 0; l < n; l++)
                    {
                        if(k == whichRange[l])
                            randomGraph.addEdge(k, whichRange[l], 0);
                        else
                        {
                            currentRange = l / rangeIncrement;
                            if(currentRange > numOfRanges)
                                currentRange = numOfRanges;

                            randomGraph.addEdge(k, whichRange[l], randomWeight(ranges[currentRange][0], ranges[currentRange][1]));
                        }
                    }
            }
            else //undirected graph
        for(int k = 0; k < n; k++)
            if(numOfRanges == 1) //only one range
            for(int l = k; l < n; l++)
                //select random weights
            if(k == l)
                randomGraph.addEdge(k, l, 0);
            else
            {
                tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                randomGraph.addEdge(k, l, tempValue);
                randomGraph.addEdge(l, k, tempValue);
            }
            else  //multiple ranges
            {
                //select order for vertices
                vertexList.resize(n - k);
                whichRange.resize(n - k);
                for(int l = 0; l < vertexList.size(); l++)
                    vertexList[l] = n - l - 1;

                //set random ranges (whichRange at the end of the loop has all vertices listed in a random order)
                    for(int l = 0; l < whichRange.size(); l++)
                    {
                        tempValue = randomWeight(0, vertexList.size());
                        whichRange[l] = vertexList[tempValue];
                        vertexList[tempValue] = vertexList[vertexList.size() - 1];
                        vertexList.resize(vertexList.size() - 1);
                    }

                    //select random weights
                    rangeIncrement = (n - k - 1) / numOfRanges; //rangeIncrement of those edges that have not been weighted yet
                    if(rangeIncrement <= 0)  //watch that divide by zero
                rangeIncrement = 1;
                for(int l = 0; l < whichRange.size(); l++)
                {
                    if(k == whichRange[l])
                        randomGraph.addEdge(k, whichRange[l], 0);
                    else
                    {
                        currentRange = l / rangeIncrement;
                        if(currentRange >= numOfRanges)
                            currentRange = numOfRanges - 1;

                        tempValue = randomWeight(ranges[currentRange][0], ranges[currentRange][1]);
                        randomGraph.addEdge(k, whichRange[l], tempValue);
                        randomGraph.addEdge(whichRange[l], k, tempValue);
                    }
                }
            }

            if(type == 1)  //add random infinite edges if needed
        {
            numberOfEdgesLeft = style;

            //select random infinite edges
            while(numberOfEdgesLeft > 0)
            {
                i = randomWeight(0, n);
                j = randomWeight(0, n);
                if((i != j)
                    &&(randomGraph.cost(i, j).isInfinity() == false))
                {
                    if(directed == true)  //directed graph
                    randomGraph.addEdge(i, j, infiniteWeight);
                    else  //undirected graph
                {
                    randomGraph.addEdge(i, j, infiniteWeight);
                    randomGraph.addEdge(j, i, infiniteWeight);
                }

                numberOfEdgesLeft--;
                }
            }
        }
    }
    else if(type == 2)  //limited directional movement
    {
        //read in information
        cout << "Directed or Undirected? (d/u) ";
        cin >> usersAnswer;
        if(usersAnswer == 'd')
            directed = true;
        else
            directed = false;

        if(directed == true)
        {
            cout << "How far backward? (> -1) ";
            cin >> limitedback;
        }
        else
            limitedback = 0;
        cout << "How far forward? (> 0) ";
        cin >> limitedforward;

        ranges.resize(1);
        ranges[0].resize(2);
        cout << "What is minimum weight? ";
        cin >> tempValue;
        ranges[0][0] = tempValue;
        cout << "What is maximum weight? ";
        cin >> tempValue;
        ranges[0][1] = tempValue;

        //begin work
        for(int k = 0; k < n; k++)
            if(directed == true) //directed graph
        for(int l = 0; l < n; l++)
            //select random weights
        if(k == l)
            randomGraph.addEdge(k, l, 0);
        else if((k - limitedback <= l) && (k + limitedforward >= l))
            randomGraph.addEdge(k, l, randomWeight(ranges[0][0], ranges[0][1]));
        else
            randomGraph.addEdge(k, l, infiniteWeight);
        else //undirected graph
        for(int l = k; l < n; l++)
            //select random weights
        if(k == l)
            randomGraph.addEdge(k, l, 0);
        else if((k - limitedback <= l) && (k + limitedforward >= l)) //k and l are connected
            {
                tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                randomGraph.addEdge(k, l, tempValue);
                randomGraph.addEdge(l, k, tempValue);
            }
            else  //k and l are not connected
            {
                randomGraph.addEdge(k, l, infiniteWeight);
                randomGraph.addEdge(l, k, infiniteWeight);
            }
    }
    else if(type == 3)  //highway system
    {
        //read in information
        cout << "All highways are undirected." << endl;
        cout << "How many vertices are in the highway? (They will be vertices 0 through (the number given - 1) ";
        cin >> highway;

        ranges.resize(2);
        ranges[0].resize(2);
        ranges[1].resize(2);
        cout << "What is the minimum weight between two highway vertices? ";
        cin >> tempValue;
        ranges[0][0] = tempValue;
        cout << "What is the maximum weight between two highway vertices? ";
        cin >> tempValue;
        ranges[0][1] = tempValue;
        cout << "What is the minimum weight between a highway vertex and a non-highway vertex? ";
        cin >> tempValue;
        ranges[1][0] = tempValue;
        cout << "What is the maximum weight between a highway vertex and a non-highway vertex? ";
        cin >> tempValue;
        ranges[1][1] = tempValue;

        //begin work
        for(int k = 0; k < highway; k++)
        {
            randomGraph.addEdge(k, k, 0);

            //select weights for edges along highway
            if(k < highway - 1) //to keep intra-highway ranges within the highway only
            {
                tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                randomGraph.addEdge(k, k + 1, tempValue);
                randomGraph.addEdge(k + 1, k, tempValue);
            }

            //select weights for edges not along highway
            for(int l = highway; l < n; l++)
            {
                tempValue = randomWeight(ranges[1][0], ranges[1][1]);
                randomGraph.addEdge(k, l, tempValue);
                randomGraph.addEdge(l, k, tempValue);
            }
        }
    }
    else if(type == 4)  //threaded grid
    {
        //read in work
        cout << "All threaded grids are undirected." << endl;
        cout << "How many levels? (number per level is equal for all levels) ";
        cin >> levels;
        cout << "How many levels can a vertices connect to above or below? (>0) ";
        cin >> jumping;
        perLevel = n / levels;

        ranges.resize(jumping + 1);
        ranges[0].resize(2);
        cout << "What is the minimum weight between vertices on the same level? ";
        cin >> tempValue;
        ranges[0][0] = tempValue;
        cout << "What is the maximum weight between vertices on the same level? ";
        cin >> tempValue;
        ranges[0][1] = tempValue;

        for(int i = 1; i < jumping + 1; i++)
        {
            cout << "What is the minimum weight between vertices " << i << " level(s) distant? ";
            cin >> tempValue;
            ranges[i][0] = tempValue;
            cout << "What is the maximum weight between vertices " << i << " level(s) distant? ";
            cin >> tempValue;
            ranges[i][1] = tempValue;
        }

        //begin work
        for(int k = 0; k < n; k++)
            for(int l = k; l < n; l++)
            {
                //select random weights for:
                if(k == l)  //same vertex
            randomGraph.addEdge(k, l, 0);
        else if(k / perLevel == l / perLevel) //same level
            {
                tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                randomGraph.addEdge(k, l, tempValue);
                randomGraph.addEdge(l, k, tempValue);
            }
            else //different levels
            {
                currentLevel1 = k / perLevel;
                currentLevel2 = l / perLevel;
                if(currentLevel1 >= levels)
                    currentLevel1--;
                if(currentLevel2 >= levels)
                    currentLevel2--;

                levelDifference = abs(currentLevel1 - currentLevel2);
                if(levelDifference <= jumping)
                {
                    tempValue = randomWeight(ranges[levelDifference][0], ranges[levelDifference][1]);
                    randomGraph.addEdge(k, l, tempValue);
                    randomGraph.addEdge(l, k, tempValue);
                }
            }
            }
    }

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

//readGraphs()
// reads in graphs from user
//
//pre:
// -inputGroups is vector of a basicEdgeGroups
//
//post:
// -inputGroups has been set by user
//
void readGraphs(vector< basicEdgeGroup > & inputGroups)
{

    //char usersAnswer;  //holds user's answer
    int numVertices;  //number of vertices
    int type;  //type of graph
    int infiniteWeights;  // Infinite Weights in graph
    int numberOfInfiniteEdges;  //holds number of infinite edges
    int numberOfJourneys;  //holds number of journeys

    int numGraphs = inputInt("How many graphs?");
    inputGroups.resize(numGraphs);

    if(getChoice("Generate graphs randomly?")) {
        output("Types:", "");
        output("\t0 - finite weights");
        output("\t1 - some random infinite weights");
        output("\t2 - limited directional movement");
        output("\t3 - highway system");
        output("\t4 - threaded grid");
        type = inputInt("What is the type of the graph?");
        numVertices = inputInt("How many vertices?");
        if(type == 1) {
            do {
                infiniteWeights = inputInt("How many infinite weights are there?");
                if(infiniteWeights >= numVertices-2)
                    output("Too many infinite weights. Use less than " + str(numVertices-2) + " weights.");
            } while(infiniteWeights >= numVertices-2);
        }
        else
            infiniteWeights = 0;


        generateGraphs(inputGroups, numVertices, type, infiniteWeights);
    }
    else
        for(int i = 0; i < numGraphs; i++)
            readGraphFromFile(inputGroups[i]);

}

//generateGraphs
// generates random graphs with user selected properties
//
//pre:
// -inputGroup is a basicEdgeGroup
//
//post:
// -inputGroup has been set randomly with user selected properties
void generateGraphs(vector< basicEdgeGroup > & randomGraphs,
                    int numberVertices,
                    int type,
                    int infiniteWeights) {

    //char usersAnswer;
    bool directed;  //true if graph is directed
    int numOfRanges;  //number of ranges
    vector< vector< int > > ranges;  //holds ranges
    vector< int > vertexList;  //holds list of unused vertices
    vector< int > whichRange;  //holds which vertex goes in which range
    whichRange.resize(numberVertices);
    int tempValue;  //temporarily holds value for different jobs
    int rangeIncrement;  //how many vertices are in each range
    int currentRange;  //which range is being used currently
    int limitedback;  //how far backward
    int limitedforward;  //how far forward
    int highway; //how many vertices in highway
    int levels; //how many levels there are
    int jumping; //how many levels a vertex can jump
    int perLevel; //how many vertices on each level
    int currentLevel1; //which level is currently being looked at
    int currentLevel2; //which level is currently being looked at
    int levelDifference; //difference between currentLevels
    int i;  //i and j used for infinite edge finding and checking
    int j;
    int numberOfEdgesLeft;  //holds countdown for adding infinite edges
    const floatWInf infinity(true, 0);  //float used to hold infinity

    srand(time(0));

    if((type == 0) || (type == 1)) {
        //finite weights or some random infinite weights

        // read in information
        directed = getChoice("Is the graph directed?");

        if(getChoice("Should the graph use multiple ranges?")) {
            numOfRanges = inputInt("How many ranges?");
        }
        else
            numOfRanges = 1;

        ranges.resize(numOfRanges);
        for(int m = 0; m < numOfRanges; m++)
        {
            ranges[m].resize(2); //first is min, second is max
            ranges[m][0] = inputInt("What is min of range "+str(m)+"?");
            ranges[m][1] = inputInt("What is max of range "+str(m)+"?");
        }
    }
    else if(type == 2) {
        //limited directional movement

        //read in information
        directed = getChoice("Is the graph directed?");

        if(directed)
            limitedback = inputInt("How far backward?");
        else
            limitedback = 0;

        limitedforward = inputInt("How far forward?");

        ranges.resize(1);
        ranges[0].resize(2);
        ranges[0][0] = inputInt("What is Minimum weight?");
        ranges[0][1] = inputInt("What is Maximum weight?");
    }
    else if(type == 3)  //highway system
    {
        //read in information
        output("All highways are undirected.");
        highway = inputInt("How many vertices are in the highway?");
        output("The highway vertices will be those labelled starting with 0.");

        ranges.resize(2);
        ranges[0].resize(2);
        ranges[1].resize(2);
        ranges[0][0] = inputInt("What is the Minimum weight between two highway vertices?");
        ranges[0][1] = inputInt("What is the Maximum weight between two highway vertices?");
        ranges[1][0] = inputInt("What is the Minimum weight between a highway vertex and a non-highway vertex?");
        ranges[1][1] = inputInt("What is the Maximum weight between a highway vertex and a non-highway vertex?");
    }
    else if(type == 4)  //threaded grid
    {
        //read in work
        output("All threaded grids are undirected.");
        levels = inputInt("How many levels?");
        jumping = inputInt("How many levels can a vertices jump to above or below?");

        perLevel = numberVertices / levels;

        ranges.resize(jumping + 1);
        ranges[0].resize(2);
        ranges[0][0] = inputInt("What is the Minimum weight between vertices on the same level?");
        ranges[0][1] = inputInt("What is the Maximum weight between vertices on the same level?");

        for(int i = 1; i < jumping + 1; i++) {
            ranges[i][0] =
                inputInt("What is the minimum weight between vertices "+str(i)+" level(s) distant?");
            ranges[i][1] =
                inputInt("What is the maximum weight between vertices "+str(i)+" level(s) distant?");
        }
    }

    for(int g = 0; g < randomGraphs.size(); g++) {
        randomGraphs[g].setN(numberVertices);

        if((type == 0) || (type == 1)) {
            //finite weights or some random infinite weights

            //begin work
            if(directed == true) {
                //directed graph
                for(int k = 0; k < numberVertices; k++) {
                    if(numOfRanges == 1) {
                        //only one range
                        for(int l = 0; l < numberVertices; l++) {
                            //select random weights
                            if(k == l) {
                                randomGraphs[g].addEdge(k, l, 0);
                            }
                            else {
                                randomGraphs[g].addEdge(k, l, randomWeight(ranges[0][0], ranges[0][1]));
                            }
                        }
                    }
                    else {
                        //multiple ranges
                        //select order for vertices
                        vertexList.resize(numberVertices);
                        for(int l = 0; l < numberVertices; l++) {
                            vertexList[l] = l;
                        }

                        //set random ranges (whichRange at the end of the loop has all vertices listed in a random order)
                        for(int l = 0; l < numberVertices; l++) {
                            tempValue = randomWeight(0, vertexList.size());
                            whichRange[l] = vertexList[tempValue];
                            vertexList[tempValue] = vertexList[vertexList.size() - 1];
                            vertexList.resize(vertexList.size() - 1);
                        }

                        //select random weights
                        rangeIncrement = numberVertices / numOfRanges;
                        for(int l = 0; l < numberVertices; l++) {
                            if(k == whichRange[l]) {
                                randomGraphs[g].addEdge(k, whichRange[l], 0);
                            }
                            else {
                                currentRange = l / rangeIncrement;
                                if(currentRange > numOfRanges) {
                                    currentRange = numOfRanges;
                                }
                                randomGraphs[g].addEdge(k, whichRange[l], randomWeight(ranges[currentRange][0], ranges[currentRange][1]));
                            }
                        }
                    }
                }
            }
            else {
                //undirected graph
                for(int k = 0; k < numberVertices; k++) {
                    if(numOfRanges == 1) {
                        //only one range
                        for(int l = k; l < numberVertices; l++) {
                            //select random weights
                            if(k == l) {
                                randomGraphs[g].addEdge(k, l, 0);
                            }
                            else {
                                tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                                randomGraphs[g].addEdge(k, l, tempValue);
                                randomGraphs[g].addEdge(l, k, tempValue);
                            }
                        }
                    }
                    else {
                        //multiple ranges
                        //select order for vertices
                        vertexList.resize(numberVertices - k);
                        whichRange.resize(numberVertices - k);
                        for(int l = 0; l < vertexList.size(); l++) {
                            vertexList[l] = numberVertices - l - 1;
                        }

                        //set random ranges
                        for(int l = 0; l < whichRange.size(); l++) {
                            tempValue = randomWeight(0, vertexList.size());
                            whichRange[l] = vertexList[tempValue];
                            vertexList[tempValue] = vertexList[vertexList.size() - 1];
                            vertexList.resize(vertexList.size() - 1);
                        }
                        // whichRange has all vertices listed in a random order

                        //select random weights
                        //rangeIncrement of those edges that have not been weighted yet
                        rangeIncrement = (numberVertices - k - 1) / numOfRanges;
                        if(rangeIncrement <= 0) {
                            //watch that divide by zero
                            rangeIncrement = 1;
                        }

                        for(int l = 0; l < whichRange.size(); l++) {
                            if(k == whichRange[l]) {
                                randomGraphs[g].addEdge(k, whichRange[l], 0);
                            }
                            else {
                                currentRange = l / rangeIncrement;
                                if(currentRange >= numOfRanges) {
                                    currentRange = numOfRanges - 1;
                                }
                                tempValue = randomWeight(ranges[currentRange][0], ranges[currentRange][1]);
                                randomGraphs[g].addEdge(k, whichRange[l], tempValue);
                                randomGraphs[g].addEdge(whichRange[l], k, tempValue);
                            }
                        }
                    }
                }

                if(type == 1) {
                    //add random infinite edges if needed

                    //select random infinite edges
                    for(numberOfEdgesLeft = infiniteWeights;
                        numberOfEdgesLeft > 0;
                        numberOfEdgesLeft--) {
                        i = j = 0;
                        while(i == j || randomGraphs[g].cost(i, j).isInfinity()) {
                            i = randomGenerator(numberVertices-1);
                            j = randomGenerator(numberVertices-1);
                        }
                        if(directed == true) {
                            //directed graph
                            randomGraphs[g].addEdge(i, j, infinity);
                        }
                        else {
                            //undirected graph
                            randomGraphs[g].addEdge(i, j, infinity);
                            randomGraphs[g].addEdge(j, i, infinity);
                        }
                    }
                }
            }
        }
        else if(type == 2) {
            //limited directional movement

            //begin work
            for(int k = 0; k < numberVertices; k++) {
                if(directed == true) {
                    //directed graph
                    for(int l = 0; l < numberVertices; l++) {
                        //select random weights
                        if(k == l) {
                            randomGraphs[g].addEdge(k, l, 0);
                        }
                        else if((k - limitedback <= l) && (k + limitedforward >= l)) {
                            randomGraphs[g].addEdge(k, l, randomWeight(ranges[0][0], ranges[0][1]));
                        }
                        else {
                            randomGraphs[g].addEdge(k, l, infinity);
                        }
                    }
                }
                else {
                    //undirected graph
                    for(int l = k; l < numberVertices; l++) {
                        //select random weights
                        if(k == l) {
                            randomGraphs[g].addEdge(k, l, 0);
                        }
                        else if((k - limitedback <= l) && (k + limitedforward >= l)) {
                            //k and l are connected
                            tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                            randomGraphs[g].addEdge(k, l, tempValue);
                            randomGraphs[g].addEdge(l, k, tempValue);
                        }
                        else {
                            //k and l are not connected
                            randomGraphs[g].addEdge(k, l, infinity);
                            randomGraphs[g].addEdge(l, k, infinity);
                        }
                    }
                }
            }
        }
        else if(type == 3) {
            //highway system

            //begin work
            for(int k = 0; k < highway; k++) {
                randomGraphs[g].addEdge(k, k, 0);

                //select weights for edges along highway
                if(k < highway - 1) {
                    //to keep intra-highway ranges within the highway only
                    tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                    randomGraphs[g].addEdge(k, k + 1, tempValue);
                    randomGraphs[g].addEdge(k + 1, k, tempValue);
                }

                //select weights for edges not along highway
                for(int l = highway; l < numberVertices; l++) {
                    tempValue = randomWeight(ranges[1][0], ranges[1][1]);
                    randomGraphs[g].addEdge(k, l, tempValue);
                    randomGraphs[g].addEdge(l, k, tempValue);
                }
            }
        }
        else if(type == 4) {
            //threaded grid

            //begin work
            for(int k = 0; k < numberVertices; k++) {
                for(int l = k; l < numberVertices; l++) {
                    //select random weights for:
                    if(k == l) {
                        //same vertex
                        randomGraphs[g].addEdge(k, l, 0);
                    }
                    else if(k / perLevel == l / perLevel) {
                        //same level
                        tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                        randomGraphs[g].addEdge(k, l, tempValue);
                        randomGraphs[g].addEdge(l, k, tempValue);
                    }
                    else {
                        //different levels
                        currentLevel1 = k / perLevel;
                        currentLevel2 = l / perLevel;
                        if(currentLevel1 >= levels) {
                            currentLevel1--;
                        }
                        if(currentLevel2 >= levels) {
                            currentLevel2--;
                        }

                        levelDifference = abs(currentLevel1 - currentLevel2);
                        if(levelDifference <= jumping) {
                            tempValue = randomWeight(ranges[levelDifference][0], ranges[levelDifference][1]);
                            randomGraphs[g].addEdge(k, l, tempValue);
                            randomGraphs[g].addEdge(l, k, tempValue);
                        }
                    }
                }
            }
        }
    }
}

//readJourneys()
// reads journeys from user
//
//pre:
// -journeysInformation is a vector of valid journeyInfo's
//
//post:
// -journeysInformation has journey information given by user
//
void readJourneys(vector< journeyInfo > & journeysInformation)
{

    char usersAnswer;  //holds user's answer to questions
    int numJourneys;  //holds total number of journeys
    int n;  //number of vertices
    int tempVertex;  //holds vertex number while reading in info

    cout << "Read journeys from file? (y/n) ";
    cin >> usersAnswer;
    if(usersAnswer == 'y')
        readJourneysFromFile(journeysInformation);
    else
    {
        cout << "Create random journeys? (y/n) ";
        cin >> usersAnswer;
        if(usersAnswer == 'y')
        {
            cout << "How many journeys to create? ";
            cin >> numJourneys;
            cout << "How many vertices are in graph? ";
            cin >> n;
            journeysInformation.resize(numJourneys);
            for(int i = 0; i < numJourneys; i++)
                journeysInformation[i].setJourneyNum(i);
            generateJourneys(journeysInformation, n);
        }
        else
        {
            cout << "How many journeys to create? ";
            cin >> numJourneys;
            journeysInformation.resize(numJourneys);
            for(int i = 0; i < numJourneys; i++)
            {
                journeysInformation[i].setJourneyNum(i);
                cout << "Source of journey " << i << ": ";
                cin >> tempVertex;
                journeysInformation[i].setSource(tempVertex);
                cout << "Destination of journey " << i << ": ";
                cin >> tempVertex;
                journeysInformation[i].setDestination(tempVertex);
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
void readJourneysFromFile(vector< journeyInfo > & journeysInformation)
{

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
    for(int i = 0; i < numJourneys; i++)
    {
        fin >> tempVertex;
        journeysInformation[i].setSource(tempVertex);
        fin >> tempVertex;
        journeysInformation[i].setDestination(tempVertex);
    }

    fin.close();

}

//generateJourneys()
// generates random journeys with user selected properties
//
//pre:
// -journeysInformation is a vector of valid journeyInfo's
// -n is the number of vertices in the graph
//
//post:
// -journeysInformation has generated journeys
//
void generateJourneys(vector< journeyInfo > & journeysInformation, int n)
{

    int randomNumber;
    vector< int > vertices;
    vertices.resize(n - 1, 0);
    for(int i = 1; i < n; i++)
        vertices[i - 1] = i;

    for(int i = 0; i < journeysInformation.size(); i++)
    {
        journeysInformation[i].setSource(0);
        randomNumber = randomWeight(0, vertices.size());
        journeysInformation[i].setDestination(vertices[randomNumber]);
        vertices[randomNumber] = vertices[vertices.size() - 1];
        vertices.resize(vertices.size() - 1);
        if(vertices.size() == 0)
        {
            vertices.resize(n - 1, 0);
            for(int i = 1; i < n; i++)
                vertices[i - 1] = i;
        }
    }

}

// <- zfj

int inputInt(const string& prompt) {
    cout << prompt << " ";
    int item;
    cin >> item;
    return item;
}

string inputString(const string& prompt) {
    cout << prompt << " ";
    string item;
    cin >> item;
    return item;
}

string str(int i) {
    ostringstream s;
    s << i;
    return s.str();
}

string str(float f) {
    ostringstream s;
    s << f;
    return s.str();
}

string str(double d) {
    ostringstream s;
    s << d;
    return s.str();
}

string str(floatWInf f) {
    ostringstream s;
    s << f;
    return s.str();
}

void output(const string& s, const string& suffix) {
    cout << s << suffix;
}

bool getChoice(string prompt) {
    while(true) {
        cout << prompt << " ";
        string temp;
        cin >> temp;
        switch(temp[0]) {
            case 'Y':
            case 'y':
                return YES;
                break;
            case 'N':
            case 'n':
                return NO;
                break;
            default:
                cout << "Illegal choice.\n";
        }
    }
}

///
/// Can be one of:
///     bmp              Windows Bitmap Format
///     dot              Dot file
///     gif              GIF
///     gtk              GTK canvas
///     ico              Icon Image File Format
///     jpg              JPEG
///     jpeg             ...
///     jpe              ...
///     pdf              Portable Document Format (PDF)
///     plain            Simple text format
///     plain-ext        ...
///     png              Portable Network Graphics format
///     ps               PostScript
///     ps2              PostScript for PDF
///     svg              Scalable Vector Graphics
///     svgz             ...
///     wbmp             Wireless BitMap format
///
/// For a full list see:
///     http://www.graphviz.org/content/output-formats
///
const string graphFormat = "pdf";
const string graphvizCmd = "dot";

// Dumps a graph to a file named "graph.dot"
// Then runs graphviz on the file to produce an output file.
void dumpGraph(const graphGroup& g, int graphNum) {
    ofstream fout("graph.dot");
    fout << "graph G {\n\tgraph [ rankdir = \"LR\" bgcolor=\"#808080\" ];\n";

    vector<string> colors;
    vector<path> paths = g.returnSharedPaths();

    colors.push_back("red");
    colors.push_back("blue");
    colors.push_back("green");
    colors.push_back("yellow");
    colors.push_back("purple");
    colors.push_back("darkorange");
    colors.push_back("khaki");
    colors.push_back("magenta");
    colors.push_back("orange");
    colors.push_back("orange");
    colors.push_back("gold");
    colors.push_back("orchid");

    for(int i = 0; i < g.returnN(); i++)
    {
        for(int j = 0; j < g.returnN(); j++)
        {
            if(g.totalEdgeCost(i, j).isInfinity() != true) {
                if(i < j) {
                    fout << "\t" << i << " -- " << j << " ";
                    fout << " [ ";
                    fout << "label = \"" << g.totalEdgeCost(i, j).value() << "\" ";
                    bool edgeUsed = false;
                    vector<string> edgeColors;
                    for(int pathNum = 0; pathNum < paths.size(); pathNum++) {
                        for(int pathPart = 1; pathPart < paths[pathNum].actualPath().size(); pathPart++) {
                            if (paths[pathNum].actualPath()[pathPart] == j &&
                                paths[pathNum].actualPath()[pathPart-1] == i) {
                                edgeColors.push_back(colors[pathNum]);
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

    fout << "}\n";
    fout.close();

    string cmd = graphvizCmd  + " -T" + graphFormat +
        " -o graph" + str(graphNum) + "." + graphFormat + " graph.dot";
    system(cmd.data());
    //system("rm graph.dot");

}