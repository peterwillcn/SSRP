#include "rand.h"
#include <cstdlib>
#include <ctime>
#include "basicEdgeGroup.h"
#include "ioFunctions.h"

static bool seeded;

//randomGenerator()
// generates random number
//
//pre:
// -randMax is one more than maximum number desired
//
//post:
// -returns random number between 0 and randMax, including 0 but not randMax
int randomGenerator(int randMax)
{

    return randomWeight(0, randMax);

}

//randomWeight()
// generates random weight
//
//pre:
// -min contains lower bound of weight
// -max contains upper bound of weight
//
//post:
// -returns a number that meets given requirements
//
int randomWeight(int min, int max)
{

    if(not(seeded)) {
        srand(time(0));
        seeded = true;
    }
    return ((rand() % (max-min+1)) + min);

}

////
//// Graph Generation
////

//generateGraphs
// generates random graphs with user selected properties
//
//pre:
// -inputGroup is a basicEdgeGroup
//
//post:
// -inputGroup has been set randomly with user selected properties
void generateGraphs(vector< basicEdgeGroup > & randomGraphs) {
    for(unsigned i = 0; i < randomGraphs.size(); i++)
        generateGraph(randomGraphs[i]);
}

//generateGraph
// generates random graph with user selected properties
//
//pre:
// -inputGroup is a basicEdgeGroup
//
//post:
// -inputGroup has been set randomly with user selected properties
void generateGraph(basicEdgeGroup & randomGraph) {
    bool repeat;
    do {
        repeat = false;
        outputPrompt("Types:", "");
        outputPrompt("\t1 - finite weights");
        outputPrompt("\t2 - some random infinite weights");
        outputPrompt("\t3 - limited directional movement");
        outputPrompt("\t4 - highway system");
        outputPrompt("\t5 - threaded grid");
        outputPrompt("\t6 - sparse graph");
        int type = inputInt("Which type is the graph?");
        switch(type) {
            case 1:
                generateFiniteWeightedGraph(randomGraph);
                break;
            case 2:
                generateInfiniteWeigtedGraph(randomGraph);
                break;
            case 3:
                generateLimitedDirectionalGraph(randomGraph);
                break;
            case 4:
                generateHighwaySystem(randomGraph);
                break;
            case 5:
                generateThreadedGrid(randomGraph);
                break;
            case 6:
                generateSparseGraph(randomGraph);
                break;
            default:
                output("Invalid Choice.");
                repeat = true;
        }
    } while(repeat);
}

// These functions each generate one type of graph.

void generateFiniteWeightedGraph(basicEdgeGroup& randomGraph) {
    //finite weights

    unsigned numberVertices = inputUnsignedInt("How many vertices does the graph have?");
    randomGraph.setN(numberVertices);

    int numOfRanges;
    if(getChoice("Should the graph have multiple ranges?"))
        numOfRanges = inputInt("How many ranges?");
    else
        numOfRanges = 1;

    vector<vector<int> > ranges(numOfRanges);
    for(unsigned m = 0; m < ranges.size(); m++) {
        ranges[m].resize(2);
        //first is min, second is max
        ranges[m][0] = inputInt("What is min of range "+str(m)+"?");
        ranges[m][1] = inputInt("What is max of range "+str(m)+"?");
    }

    //begin work
    bool directed = getChoice("Is the graph directed?");
    bool undirected = not(directed);

    if(directed)
        randomGraph.setDirected();
    else
        randomGraph.setUndirected();

    for(unsigned k = 0; k < numberVertices; k++) {
        if(numOfRanges == 1) {
            //only one range
            for(unsigned l = 0; l < numberVertices; l++) {
                //select random weights
                if(k == l)
                    randomGraph.addEdge(k, l, 0);
                else {
                    int tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                    randomGraph.addEdge(k, l, tempValue);
                    if(undirected)
                        randomGraph.addEdge(l, k, tempValue);
                }
            }
        }
        else {
            //multiple ranges

            //select order for vertices
            vector<unsigned> vertexList(numberVertices);
            vector<unsigned> whichRange(numberVertices);

            // !! vertex list is backwards !!
            for(unsigned l = 0; l < numberVertices; l++)
                vertexList[l] = numberVertices - l - 1;

            //set random ranges (whichRange at the end of the loop has all vertices listed in a random order)
            for(unsigned l = 0; l < whichRange.size(); l++) {
                int tempValue = randomGenerator(vertexList.size()-1);
                whichRange[l] = vertexList[tempValue];
                vertexList[tempValue] = vertexList[vertexList.size() - 1];
                vertexList.resize(vertexList.size() - 1);
            }

            //select random weights
            //rangeIncrement of those edges that have not been weighted yet
            int rangeIncrement = (numberVertices - k - 1) / numOfRanges;
            if(rangeIncrement <= 0) // watch divide by zero
                rangeIncrement = 1;
            for(unsigned l = 0; l < numberVertices; l++) {
                if(k == whichRange[l])
                    randomGraph.addEdge(k, whichRange[l], 0);
                else {
                    int currentRange = l / rangeIncrement;
                    if(currentRange > numOfRanges)
                        currentRange = numOfRanges - 1;
                    int tempValue = randomWeight(ranges[currentRange][0], ranges[currentRange][1]);
                    randomGraph.addEdge(k, whichRange[l], tempValue);
                    if(undirected)
                        randomGraph.addEdge(whichRange[l], k, tempValue);
                }
            }
        }
    }
}

void generateInfiniteWeigtedGraph(basicEdgeGroup& randomGraph) {
    // some random infinite weights

    unsigned numberVertices = inputUnsignedInt("How many vertices does the graph have?");
    randomGraph.setN(numberVertices);

    int numOfRanges;
    if(getChoice("Should the graph have multiple ranges?"))
        numOfRanges = inputInt("How many ranges?");
    else
        numOfRanges = 1;

    vector<vector<int> > ranges(numOfRanges);
    for(unsigned m = 0; m < ranges.size(); m++) {
        ranges[m].resize(2);
        //first is min, second is max
        ranges[m][0] = inputInt("What is min of range "+str(m)+"?");
        ranges[m][1] = inputInt("What is max of range "+str(m)+"?");
    }

    //begin work
    bool directed = getChoice("Is the graph directed?");
    bool undirected = not(directed);

    if(directed)
        randomGraph.setDirected();
    else
        randomGraph.setUndirected();

    for(unsigned k = 0; k < numberVertices; k++) {
        if(numOfRanges == 1) {
            //only one range
            for(unsigned l = 0; l < numberVertices; l++) {
                //select random weights
                if(k == l)
                    randomGraph.addEdge(k, l, 0);
                else {
                    int tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                    randomGraph.addEdge(k, l, tempValue);
                    if(undirected)
                        randomGraph.addEdge(l, k, tempValue);
                }
            }
        }
        else {
            //multiple ranges

            //select order for vertices
            vector<unsigned> vertexList(numberVertices);
            vector<unsigned> whichRange(numberVertices);

            // !! vertex list is backwards !!
            for(unsigned l = 0; l < numberVertices; l++)
                vertexList[l] = numberVertices - l - 1;

            //set random ranges (whichRange at the end of the loop has all vertices listed in a random order)
            for(unsigned l = 0; l < whichRange.size(); l++) {
                int tempValue = randomGenerator(vertexList.size()-1);
                whichRange[l] = vertexList[tempValue];
                vertexList[tempValue] = vertexList[vertexList.size() - 1];
                vertexList.resize(vertexList.size() - 1);
            }

            //select random weights
            //rangeIncrement of those edges that have not been weighted yet
            int rangeIncrement = (numberVertices - k - 1) / numOfRanges;
            if(rangeIncrement <= 0) // watch divide by zero
                rangeIncrement = 1;
            for(unsigned l = 0; l < numberVertices; l++) {
                if(k == whichRange[l])
                    randomGraph.addEdge(k, whichRange[l], 0);
                else {
                    int currentRange = l / rangeIncrement;
                    if(currentRange > numOfRanges)
                        currentRange = numOfRanges - 1;
                    int tempValue = randomWeight(ranges[currentRange][0], ranges[currentRange][1]);
                    randomGraph.addEdge(k, whichRange[l], tempValue);
                    if(undirected)
                        randomGraph.addEdge(whichRange[l], k, tempValue);
                }
            }
        }
    }

    //add random infinite edges if needed

    int infinitePercent = 100 - inputInt("What percent of the graph should be connected? (1 - 100)");

    int numberInfiniteEdges = (numberVertices * (numberVertices-1) / 2) *  (infinitePercent/100.0);

    vector<pair<int, int> > notInfinity;
    for(unsigned i = 0; i < numberVertices; i++) {
        for(unsigned j = 0; j < numberVertices; j++) {
            if(i != j)
                notInfinity.push_back(pair<int,int>(i,j));
        }
    }

    //select random infinite edges
    for(unsigned numberOfEdgesLeft = numberInfiniteEdges; numberOfEdgesLeft > 0; numberOfEdgesLeft--) {
        int r = randomGenerator(notInfinity.size()-1);
        randomGraph.addEdge(notInfinity[r].first, notInfinity[r].second, infinity);
        if(undirected)
            randomGraph.addEdge(notInfinity[r].second, notInfinity[r].first, infinity);
        notInfinity.erase(notInfinity.begin()+r);
    }
}

void generateLimitedDirectionalGraph(basicEdgeGroup& randomGraph) {
    //limited directional movement

    unsigned numberVertices = inputUnsignedInt("How many vertices does the graph have?");
    randomGraph.setN(numberVertices);

    //read in information
    bool directed = getChoice("Is the graph directed?");
    bool undirected = not(directed);
    int limitedback, limitedforward;

    if(directed)
        randomGraph.setDirected();
    else
        randomGraph.setUndirected();

    if(directed)
        limitedback = inputInt("How far backward?");
    else
        limitedback = 0;

    limitedforward = inputInt("How far forward?");

    vector<vector<int> > ranges(1, vector<int>(2));
    ranges[0][0] = inputInt("What is Minimum weight?");
    ranges[0][1] = inputInt("What is Maximum weight?");

    //begin work
    for(unsigned k = 0; k < numberVertices; k++){
        if(directed == true) {
            //directed graph
            for(unsigned l = 0; l < numberVertices; l++) {
                //select random weights
                if(k == l)
                    randomGraph.addEdge(k, l, 0);
                else if((k - limitedback <= l) && (k + limitedforward >= l))
                    randomGraph.addEdge(limitedback, l, randomWeight(ranges[0][0], ranges[0][1]));
                else
                    randomGraph.addEdge(k, l, infinity);
            }
        }
        else {
            //undirected graph
            unsigned l = (directed ? 0 : k);
            for(; l < numberVertices; l++) {
                //select random weights
                if(k == l)
                    randomGraph.addEdge(k, l, 0);
                else if((k - limitedback <= l) && (k + limitedforward >= l)) {
                    //k and l are connected
                    int tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                    randomGraph.addEdge(k, l, tempValue);
                    if(undirected)
                        randomGraph.addEdge(l, k, tempValue);
                }
                else {
                    //k and l are not connected
                    randomGraph.addEdge(k, l, infinity);
                    if(undirected)
                        randomGraph.addEdge(l, k, infinity);
                }
            }
        }
    }
}

void generateHighwaySystem(basicEdgeGroup& randomGraph) {

    unsigned numberVertices = inputUnsignedInt("How many vertices does the graph have?");
    randomGraph.setN(numberVertices);

    //highway system

    //read in information
    cout << "All highways are undirected." << endl;
    unsigned highway = inputUnsignedInt("How many vertices are in the highway? ");
    randomGraph.setUndirected();

    vector<vector<int> > ranges(2, vector<int>(2));
    ranges[0][0] = inputInt("What is the minimum weight between two highway vertices? ");
    ranges[0][1] = inputInt("What is the maximum weight between two highway vertices? ");
    ranges[1][0] = inputInt("What is the minimum weight between a highway vertex and a non-highway vertex? ");
    ranges[1][1] = inputInt("What is the maximum weight between a highway vertex and a non-highway vertex? ");

    //begin work
    for(unsigned k = 0; k < highway; k++) {
        randomGraph.addEdge(k, k, 0);

        //select weights for edges along highway
        if(k < highway - 1) {
            //to keep intra-highway ranges within the highway only
            int tempValue = randomWeight(ranges[0][0], ranges[0][1]);
            randomGraph.addEdge(k, k + 1, tempValue);
            randomGraph.addEdge(k + 1, k, tempValue);
        }

        //select weights for edges not along highway
        for(unsigned l = highway; l < numberVertices; l++) {
            int tempValue = randomWeight(ranges[1][0], ranges[1][1]);
            randomGraph.addEdge(k, l, tempValue);
            randomGraph.addEdge(l, k, tempValue);
        }
    }
}

void generateThreadedGrid(basicEdgeGroup& randomGraph) {

    unsigned numberVertices = inputUnsignedInt("How many vertices does the graph have?");
    randomGraph.setN(numberVertices);

    //read in work
    output("All threaded grids are undirected.");
    unsigned levels = inputUnsignedInt("How many levels? (number per level is equal for all levels)");
    unsigned jumping = inputUnsignedInt("How many levels can a vertices connect to above or below? ");
    unsigned perLevel = numberVertices / levels;

    vector<vector<int> > ranges(jumping + 1, vector<int>(2));
    ranges[0][0] = inputInt("What is the minimum weight between vertices on the same level?");
    ranges[0][1] = inputInt("What is the maximum weight between vertices on the same level?");

    for(unsigned i = 1; i < jumping + 1; i++) {
        ranges[i][0] = inputInt("What is the minimum weight between vertices "+str(i)+" level(s) distant?");
        ranges[i][1] = inputInt("What is the maximum weight between vertices "+str(i)+" level(s) distant?");
    }

    //begin work
    for(unsigned k = 0; k < numberVertices; k++) {
        for(unsigned l = k; l < numberVertices; l++) {
            //select random weights for:
            if(k == l)  //same vertex
                randomGraph.addEdge(k, l, 0);
            else if(k / perLevel == l / perLevel) {
                //same level
                int tempValue = randomWeight(ranges[0][0], ranges[0][1]);
                randomGraph.addEdge(k, l, tempValue);
                randomGraph.addEdge(l, k, tempValue);
            }
            else {
                //different levels
                unsigned currentLevel1 = k / perLevel;
                unsigned currentLevel2 = l / perLevel;
                if(currentLevel1 >= levels)
                    currentLevel1--;
                if(currentLevel2 >= levels)
                    currentLevel2--;

                unsigned levelDifference = abs(int(currentLevel1) - int(currentLevel2));
                if(levelDifference <= jumping) {
                    int tempValue = randomWeight(ranges[levelDifference][0], ranges[levelDifference][1]);
                    randomGraph.addEdge(k, l, tempValue);
                    randomGraph.addEdge(l, k, tempValue);
                }
            }
        }
    }
}

void generateSparseGraph(basicEdgeGroup& graph) {

    unsigned numberVertices = inputUnsignedInt("How many vertices are there?");
    bool directed = getChoice("Is the graph directed?");
    unsigned minWeight = inputUnsignedInt("What is the minimum weight?");
    unsigned maxWeight = inputUnsignedInt("what is the maximum weight?");
    bool undirected = not(directed);

    if(directed)
        graph.setDirected();
    else
        graph.setUndirected();

    graph.setN(numberVertices);

    for(unsigned i = 0; i < numberVertices; i++)
         graph.addEdge(i, i, 0);

    if(directed) {
        vector<int> copy(0);
        for(unsigned i = 0; i < numberVertices; i++)
            copy.push_back(i);

        const vector<int> vertices = copy;

        vector<int> randomVertices;
        for(unsigned i = 0; i < vertices.size(); i++) {
            //int rand = randomGenerator(copy.size()-1);
            randomVertices.push_back(copy[i]);
            //copy.erase(copy.begin()+rand);
        }

        for(unsigned i = 1; i < vertices.size(); i++) {
            int j = randomGenerator(i-1);
            int k = randomGenerator(i-1);

            graph.addEdge(randomVertices[j], randomVertices[i], randomWeight(minWeight, maxWeight));
            graph.addEdge(randomVertices[i], randomVertices[k], randomWeight(minWeight, maxWeight));
        }
    }
    else {
        vector<int> copy(0);
        for(unsigned i = 0; i < numberVertices; i++)
            copy.push_back(i);

        const vector<int> vertices = copy;

        vector<int> randomVertices;
        for(unsigned i = 0; i < vertices.size(); i++) {
            int rand = randomGenerator(copy.size()-1);
            randomVertices.push_back(copy[rand]);
            copy.erase(copy.begin()+rand);
        }

        for(unsigned i = 1; i < vertices.size(); i++) {
            int j = randomGenerator(i-1);
            int weight = randomWeight(minWeight, maxWeight);

            graph.addEdge(randomVertices[j], randomVertices[i], weight);
            if(undirected)
                graph.addEdge(randomVertices[i], randomVertices[j], weight);
        }

        int numberEdges = numberVertices*0.2;
        for(; numberEdges > 0; numberEdges--) {
            int i, j;
            i = j = 0;
            while(i == j || not(graph.cost(i,j).isInfinity())) {
                i = randomGenerator(numberVertices-1);
                j = randomGenerator(numberVertices-1);
            }
            int weight = randomWeight(minWeight, maxWeight);

            graph.addEdge(i, j, weight);
            if(undirected)
                graph.addEdge(j, i, weight);
        }
    }
}

void generateSparseGraph(basicEdgeGroup& graph, unsigned numberVertices, bool directed, int minWeight, int maxWeight) {
    bool undirected = not(directed);

    if(directed)
        graph.setDirected();
    else
        graph.setUndirected();

    graph.setN(numberVertices);

    for(unsigned i = 0; i < numberVertices; i++)
         graph.addEdge(i, i, 0);

    if(directed) {
        vector<int> copy(0);
        for(unsigned i = 0; i < numberVertices; i++)
            copy.push_back(i);

        const vector<int> vertices = copy;

        vector<int> randomVertices;
        for(unsigned i = 0; i < vertices.size(); i++) {
            //int rand = randomGenerator(copy.size()-1);
            randomVertices.push_back(copy[i]);
            //copy.erase(copy.begin()+rand);
        }

        for(unsigned i = 1; i < vertices.size(); i++) {
            int j = randomGenerator(i-1);
            int k = randomGenerator(i-1);

            graph.addEdge(randomVertices[j], randomVertices[i], randomWeight(minWeight, maxWeight));
            graph.addEdge(randomVertices[i], randomVertices[k], randomWeight(minWeight, maxWeight));
        }
    }
    else {
        vector<int> copy(0);
        for(unsigned i = 0; i < numberVertices; i++)
            copy.push_back(i);

        const vector<int> vertices = copy;

        vector<int> randomVertices;
        for(unsigned i = 0; i < vertices.size(); i++) {
            int rand = randomGenerator(copy.size()-1);
            randomVertices.push_back(copy[rand]);
            copy.erase(copy.begin()+rand);
        }

        for(unsigned i = 1; i < vertices.size(); i++) {
            int j = randomGenerator(i-1);
            int weight = randomWeight(minWeight, maxWeight);

            graph.addEdge(randomVertices[j], randomVertices[i], weight);
            if(undirected)
                graph.addEdge(randomVertices[i], randomVertices[j], weight);
        }

        int numberEdges = numberVertices*0.2;
        for(; numberEdges > 0; numberEdges--) {
            int i, j;
            i = j = 0;
            while(i == j || not(graph.cost(i,j).isInfinity())) {
                i = randomGenerator(numberVertices-1);
                j = randomGenerator(numberVertices-1);
            }
            int weight = randomWeight(minWeight, maxWeight);

            graph.addEdge(i, j, weight);
            if(undirected)
                graph.addEdge(j, i, weight);
        }
    }
}

////
//// Journey Generation
////

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
void generateJourneys(vector< journeyInfo > & journeysInformation, unsigned numVertices)
{

    vector<pair<int,int> > pairs;
    for(unsigned i = 0; i < numVertices; i++) {
        for(unsigned j = 0; j < numVertices; j++) {
            if(i != j) {
                pairs.push_back(pair<int,int>(i, j));
            }
        }
    }

    for(unsigned i = 0; i < journeysInformation.size(); i++) {
        int r = randomGenerator(pairs.size()-1);
        journeysInformation[i].setSource(pairs[r].first);
        journeysInformation[i].setDestination(pairs[r].second);
        pairs.erase(pairs.begin()+r);
    }
}
