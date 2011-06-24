//Christopher Earl
//edgeGroup.cpp
// contains edge and edgeGroup member functions

#include <vector>

using namespace std;

#include "basicStructures.h"
#include "vertex.h"
#include "path.h"
#include "edge.h"
#include "basicEdgeGroup.h"
#include "journeyInfo.h"
#include "edgeGroup.h"
#include "options.h"

//edgeGroup::edgeGroup()
// c'tor
//
//pre:
// -none
//
//post:
// -edgeGroup constructed without values
//
//O(1)
edgeGroup::edgeGroup()
:internalNumJourneys(), edges()
{

}

//edgeGroup::edgeGroup()
// c'tor
//
//pre:
// -numVertices is a valid number of vertices
// -numJourneys is a valid number of journeys
//
//post:
// -edgeGroup constructed without numVertices and numJourneys
//
//O(numVertices)
edgeGroup::edgeGroup(int numVertices, int numJourneys)
:internalNumJourneys(numJourneys)
{

    edges.resize(numVertices);

    for(unsigned i = 0; i < returnN(); i++)
        edges[i].resize(returnN());

}

edgeGroup::edgeGroup(const edgeGroup& other)
    : internalNumJourneys(other.internalNumJourneys), edges(other.edges) {

}

//edgeGroup::edgeGroup()
// c'tor
//
//pre:
// -inputGroup is a valid basicEdgeGroup
// -numJourneys is a valid number of journeys
//
//post:
// -edgeGroup constructed with inputGroup and numJourneys
//
//O(inputGroup.returnN() ^2 * numJourneys)
edgeGroup::edgeGroup(basicEdgeGroup const & inputGroup, int numJourneys)
{

    set(inputGroup, numJourneys);

}

//edgeGroup::isEdgeUsable()
// returns true if edge is usable (single edge)
//
//pre:
// -edgeGroup has been set with a basicEdgeGroup
// -i and j are valid vertex numbers
//
//post:
// -returns true if edge is usable (single edge)
//          false otherwise
//
//O(1)
bool edgeGroup::isEdgeUsable(int i, int j) const
{

    return edges[i][j].isUsable();

}

//edgeGroup::isSectionUsable()
// returns true if section is usable (made of single edge)
//
//pre:
// -edgeGroup has been set with a basicEdgeGroup
// -section contains numbers that are valid vertex numbers
//
//post:
// -returns true if section is usable (made of single edge)
//          false otherwise
//
//O(length of section)
bool edgeGroup::isSectionUsable(vector< int > section) const
{
    bool answer = true;

    for(unsigned i = 0; i < section.size() - 1 && answer; i++) {
        answer = isEdgeUsable(section[i], section[i + 1]);
    }

    return answer;

}

//edgeGroup::totalEdgeCost()
// returns total cost of given edge
//
//pre:
// -edgeGroup has been set with a basicEdgeGroup
// -i and j are valid vertex numbers
//
//post:
// -returns total cost of given edge
//
//O(1)
floatWInf edgeGroup::totalEdgeCost(int i, int j) const
{

    return edges[i][j].totalCost();

}

//edgeGroup::totalSectionCost()
// returns total cost of given edge
//
//pre:
// -edgeGroup has been set with a basicEdgeGroup
// -section is a vector of valid vertex numbers
//
//post:
// -returns total cost of given edge
//
//O(length of section)
floatWInf edgeGroup::totalSectionCost(vector< int > section) const
{
    floatWInf answer;

    if(isSectionUsable(section) == true) {
        for(unsigned i = 0; i < section.size() - 1; i++)
            answer += totalEdgeCost(i, i + 1);
    }
    else
        answer.setValue();

        return answer;

}

//edgeGroup::currentEdgeCost()
// returns current cost for given journey to traverse given edge
//
//pre:
// -edgeGroup has been set with a basicEdgeGroup
// -i and j are valid vertex numbers
// -journeyNum is a valid journey number
//
//post:
// -returns current cost for given journey to traverse given edge
//
//O(1)
floatWInf edgeGroup::currentEdgeCost(int i, int j, int journeyNum) const
{

    return edges[i][j].currentCost(journeyNum);

}

//edgeGroup::currentSectionCost()
// returns current cost for given journey to traverse given section
//
//pre:
// -edgeGroup has been set with a basicEdgeGroup
// -section is a vector of valid vertex numbers
// -journeyNum is a valid journey number
//
//post:
// -returns current cost for given journey to traverse given section
//
//O(length of section)
floatWInf edgeGroup::currentSectionCost(vector< int > section, int journeyNum) const
{

    floatWInf answer(0);

    if(isSectionUsable(section) == true)
    {
        for(unsigned i = 0; i < section.size() - 1; i++)
            answer += currentEdgeCost(section[i], section[i + 1], journeyNum);
    }
    else
        answer.setValue();

    return answer;

}

//edgeGroup::currentEdgeCosts()
// returns current cost for given journeys to traverse given edge
//
//pre:
// -edgeGroup has been set with a basicEdgeGroup
// -i and j are valid vertex numbers
// -journeysNum is a vector of valid journey numbers
//
//post:
// -returns current cost for given journeys to traverse given edge
//
//O(length of journeysNum)
/*
floatWInf edgeGroup::currentEdgeCosts(int i, int j, vector< int > journeysNum) const
{

    return edges[i][j].currentCosts(journeysNum);

}
*/

//edgeGroup::currentSectionCosts()
// returns current cost for given journeys to traverse given section
//
//pre:
// -edgeGroup has been set with a basicEdgeGroup
// -section is a vector of valid vertex numbers
// -journeysNum is a vector of valid journey numbers
//
//post:
// -returns current cost for given journeys to traverse given section
//
//O((length of section) * (length of journeysNum))

/*
floatWInf edgeGroup::currentSectionCosts(vector< int > section, vector< int > journeysNum) const
{

    floatWInf answer;

    if(isSectionUsable(section) == true)
        for(unsigned i = 0; i < section.size() - 1; i++)
            answer += currentEdgeCosts(i, i + 1, journeysNum);
        else
            answer.setValue();

        return answer;

}
*/

//edgeGroup::isJourneyIn()
// returns true if given journey is in given edge
//
//pre:
// -edgeGrouph has been set with a basicEdgeGroup
// -i and j are valid vertex numbers
// -journeyNum is a valid journey number
//
//post:
// -returns true if given journey is in given edge
//          false otherwise
//
//O(1)
bool edgeGroup::isJourneyIn(int i, int j, int journeyNum) const
{

    return edges[i][j].isJourneyIn(journeyNum);

}

//edgeGroup::isJourneyInSection()
// returns true if given journey is in given section
//
//pre:
// -edgeGrouph has been set with a basicEdgeGroup
// -section is a vector of valid vertex numbers
// -journeyNum is a valid journey number
//
//post:
// -returns true if given journey is in given section
//          false otherwise
//
//O(length of section)
bool  edgeGroup::isJourneyInSection(vector< int > section, int journeyNum) const
{

    bool answer = true;

    if(isSectionUsable(section) == true) {
        for(unsigned i = 0; answer && i < section.size() - 1; i++)
        {
            answer = isJourneyIn(i, i + 1, journeyNum);
        }
    }
    else
        answer = false;

        return answer;

}

//edgeGroup::numJourneysUsing()
// returns number of journeys using given edge
//
//pre:
// -edgeGrouph has been set with a basicEdgeGroup
// -i and j are valid vertex numbers
//
//post:
// -returns number of journeys using given edge
//
//O(1)
int edgeGroup::numJourneysUsing(int i, int j) const
{

    return edges[i][j].numJourneysUsing();

}

//edgeGroup::findSP()
// returns shortest path for journeyNum given the current shared paths
//
//pre:
// -edgeGroup as been set with a basicEdgeGroup
// -information contains information about journey to find
//
//post:
// returns shortest path for journeyNum given the current shared paths
//
//O(returnN() ^2)
path edgeGroup::findSP(journeyInfo information) const
{

    return Dijkstra(information);

}

//edgeGroup::returnN()
// returns number of vertices in the graph
//
//pre:
// -edgeGroup as been set with a basicEdgeGroup
//
//post:
// -returns number of vertices in the graph
//
//O(1)
unsigned edgeGroup::returnN() const
{

    return edges.size();

}

//edgeGroup::numJourneys()
// returns total number of journeys
//
//pre:
// -edgeGroup as been set with a basicEdgeGroup and a number of journeys
//
//post:
// -returns total number of journeys
//
//O(1)
int edgeGroup::numJourneys() const
{

    return internalNumJourneys;

}

//edgeGroup::addJourneySP()
// sets given journey to shorest path with current shared weights
//
//pre:
// -edgeGroup as been set with a basicEdgeGroup
// -information contains information about journey to find
//
//post:
// given journey set to shorest path with current shared weights
//
//O(returnN() ^2)
void edgeGroup::addJourneySP(journeyInfo information)
{

    addJourney(information.journeyNum(), findSP(information));

}

//edgeGroup::addJourney()
// sets given journey to given path
//
//pre:
// -edgeGroup as been set with a basicEdgeGroup
// -information contains information about journey to find
//
//post:
// -given journey set to given path
//
//O(length of newPath)
void edgeGroup::addJourney(int journeyNum, path const & newPath)
{

    removeJourney(journeyNum);

    for(unsigned i = 0; i < newPath.length() - 1; i++)
    {
        edges[newPath.returnVertex(i)][newPath.returnVertex(i + 1)].addJourney(journeyNum);
        if(biSharing)
          edges[newPath.returnVertex(i + 1)][newPath.returnVertex(i)].addJourney(journeyNum);
    }
        

}

//edgeGroup::removeJourney()
// removes given journey from graph
//
//pre:
// -edgeGroup as been set with a basicEdgeGroup
// -information contains information about journey to find
//
//post:
// -given journey is not in graph
//
//O(returnN() ^2)
void edgeGroup::removeJourney(int journeyNum)
{

    for(unsigned i = 0; i < returnN(); i++)
        for(unsigned j = 0; j < returnN(); j++)
            edges[i][j].removeJourney(journeyNum);

}

//edgeGroup::removeAllJourneys()
// removes all journeys from graph
//
//pre:
// -edgeGroup as been set with a basicEdgeGroup
// -information contains information about journey to find
//
//post:
// -all journeys are not in graph
//
//O(returnN() ^2 * numJourneys())
void edgeGroup::removeAllJourneys()
{

    for(unsigned i = 0; i < returnN(); i++)
        for(unsigned j = 0; j < returnN(); j++)
            edges[i][j].removeAllJourneys();

}

//edgeGroup::set()
// sets edges to given graph and journeys to given journeys
//
//pre:
// -newGraph is a valid basicEdgeGroup
// -newNumJourneys is a valid number of journeys
//
//post:
// -edges set to given graph
//
//O(returnN() ^2 * numJourneys())
void edgeGroup::set(basicEdgeGroup const & newGraph, unsigned newNumJourneys)
{

    internalNumJourneys = newNumJourneys;
    edges.resize(newGraph.returnN());

    for(unsigned i = 0; i < returnN(); i++)
    {
        edges[i].resize(returnN());
        for(unsigned j = 0; j < returnN(); j++)
        {
            edges[i][j].setTotalCost(newGraph.cost(i, j));
            edges[i][j].setTotalNumJourneys(numJourneys());
            edges[i][j].removeAllJourneys();
        }
    }

}

//edgeGroup::update_edge_cost()
//updates the cost of edge (i,j) to "new_cost" and removes all journeys from it
// pre: i and j are valid vertices.
// post: edge (i,j) now costs "new_cost"
//       all journeys on (i,j) are removed.
void edgeGroup::update_edge_cost(int i, int j, floatWInf new_cost){
    edges[i][j].setTotalCost(new_cost);
    edges[i][j].setTotalNumJourneys(numJourneys());
    edges[i][j].removeAllJourneys();
}
//edgeGroup::Dijkstra()
// returns shortest path given current costs of edges using Dijkstra's algorithm
//
//pre:
// -edgeGroup as been set with a basicEdgeGroup
// -information contains information about journey to find
//
//post:
// -returns shortest path given current costs of edges
//
//O(returnN() ^2)
path edgeGroup::Dijkstra(journeyInfo information) const
{

    vector< vertex > vertices;
    floatWInf infiniteFloat;
    floatWInf zeroFloat;
    intWInf infiniteInt;
    vector< int > actualPath;
    path answer;
    zeroFloat.setValue(0);

    //prepare vertices for Dijkstra
    vertices.resize(returnN());

    for(unsigned i = 0; i < returnN(); i++)
    {
        vertices[i].setCost(infiniteFloat);  //set cost to infinity
        vertices[i].setPredecessor(infiniteInt);  //set predecessor to null
    }

    vertices[information.source()].setCost(zeroFloat);  //set cost of source to be 0

    //if Q[i] == true, then vertex i has not yet been extracted
    bool Q[returnN()];
    for(unsigned i = 0; i < returnN(); i++)
        Q[i] = true;
    int u; //current vertex being looked at
    intWInf tempU;

    //Dijkstra's algorithm:
    for(unsigned j = 0; j < returnN(); j++)
    {
        u = information.source();

        for(unsigned i = 0; i < returnN(); i++)
            if((Q[i] == true)                                    //if ( (Q[i] is true)
        &&((Q[u] == false)                                 //and ( (Q[u] is false)
        ||(vertices[i].cost() < vertices[u].cost())))      //or (i < u)))
        {
            u = i;                                //replace u with i
        }

        Q[u] = false;

        for(unsigned v = 0; v < returnN(); v++)
            if(vertices[v].cost() > (vertices[u].cost() + currentEdgeCost(u, v, information.journeyNum())))  //(v > u + w(u, v))
        {
            vertices[v].setCost(vertices[u].cost() + currentEdgeCost(u, v, information.journeyNum()));
            tempU.setValue(u);
            vertices[v].setPredecessor(tempU);
        }
    }

    //find and return path:
    findPath(information, vertices, actualPath);
    actualPath.push_back(information.destination());
    answer.setPath(actualPath, vertices[information.destination()].cost());

    return answer;

}

//findPath()
// recursively finds path of given information
//
//pre:
// -edgeGroup as been set with a basicEdgeGroup
// -information contains information about journey to find
// -vertices is a vector of vertex's that have a full predecessor tree
//
//post:
// -returns path containing the path from source to destination, including source but NOT including destination
//
//O(returnN())
void edgeGroup::findPath(journeyInfo information, vector< vertex > const & vertices, vector< int > & foundPath) const
{

    if(vertices[information.destination()].cost().isInfinity() == false) {
        if(information.source() != information.destination()) {
            if((vertices[information.destination()].predecessor().isInfinity() == false)
                &&(information.source() == vertices[information.destination()].predecessor().value()))
                foundPath.push_back(information.source());
            else
            {
                journeyInfo newInformation(information.journeyNum(), information.source(), vertices[information.destination()].predecessor().value());

                findPath(newInformation, vertices, foundPath);
                foundPath.push_back(vertices[information.destination()].predecessor().value());
            }
        }
    }
}
