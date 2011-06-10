//Christopher Earl
//graphGroup.cpp
// contains graphGroup member functions

#include <cstdlib>
#include <vector>
//#include <iostream>
//#include <fstream>
#include <string>

using namespace std;

#include "basicStructures.h"
#include "vertex.h"
#include "path.h"
#include "basicEdgeGroup.h"
#include "journeyInfo.h"
#include "journeyGroup.h"
#include "edgeGroup.h"
#include "graphGroup.h"
//#include "match.h"
#include "rand.h"
#include "ioFunctions.h"

///
///graphGroup member functions
///

//graphGroup::graphGroup()
// c'tor
//
//pre:
// -none
//
//post:
// -graphGroup constructed without values
//
//O(1)
graphGroup::graphGroup()
:edges(), journeys(), graph()
{

}

//graphGroup::graphGroup()
// c'tor
//
//pre:
// -inputGroup is a valid basicEdgeGroup
// -journeysInformation is a vector of valid journeyInfo's
//
//post:
// -graphGroup constructed with inputGroup and journeysInformation
//
//O(inputGroup.returnN() ^2 * journeysInformation)
graphGroup::graphGroup(basicEdgeGroup const & inputGroup, vector< journeyInfo > const & journeysInformation)
{

    set(inputGroup, journeysInformation);

}

// Copy Constructor
graphGroup::graphGroup(const graphGroup& other)
: journeys(other.journeys), edges(other.edges), graph(other.graph) {
}

//graphGroup::returnN()
// returns number of vertices
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -returns number of vertices
//
//O(1)
int graphGroup::returnN() const
{

    return edges.returnN();

}

//graphGroup::numJourneys()
// returns number of journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -returns number of journeys
//
//O(1)
int graphGroup::numJourneys() const
{

    return journeys.numJourneys();

}

const journey& graphGroup::getJourney(const int i) const {
    return journeys[i];
}

const journeyGroup& graphGroup::getJourneys() const {
    return journeys;
}

//graphGroup::returnGraph()
// returns the graph
//
//pre:
// -the graph has been set
//
//post:
// -returns the graph
//
//O(1)
basicEdgeGroup graphGroup::returnGraph() const
{
    return graph;
}


//graphGroup::isEdgeUsable()
// returns true if given edge is usable
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -i and j are valid vertex numbers
//
//post:
// -returns true if given edge is usable
//          false otherwise
//
//O(1)
bool graphGroup::isEdgeUsable(int i, int j) const
{

    return edges.isEdgeUsable(i, j);

}

//graphGroup::isSectionUsable()
// returns true if given section is usable
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -section is a vector of valid vertex numbers
//
//post:
// -returns true if given section is usable
//          false otherwise
//
//O(1)
bool graphGroup::isSectionUsable(vector< int > section) const
{

    return edges.isSectionUsable(section);

}

//graphGroup::totalEdgeCost()
// returns total cost of traversing given edge
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -i and j are valid vertex numbers
//
//post:
// -returns total cost of traversing given edge
//
//O(1)
floatWInf graphGroup::totalEdgeCost(int i, int j) const
{

    return edges.totalEdgeCost(i, j);

}

//graphGroup::totalSectionCost()
// returns toal cost of traversing given section
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -section is a vector of valid vertex numbers
//
//post:
// -returns total cost of traversing given section
//
//O(length of section)
floatWInf graphGroup::totalSectionCost(vector< int > section) const
{

    return edges.totalSectionCost(section);

}

//graphGroup::currentEdgeCost()
// returns current cost of traversing given edge for given journeyNum
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -i and j are valid vertex numbers
// -journeyNum is a valid journey number
//
//post:
// -returns current cost of traversing given edge for given journeyNum
//
//O(1)
floatWInf graphGroup::currentEdgeCost(int i, int j, int journeyNum) const
{

    return edges.currentEdgeCost(i, j, journeyNum);

}

//graphGroup::currentSectionCost()
// returns current cost of traversing given section for given journeyNum
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -section is a vector of valid vertex numbers
// -journeyNum is a valid journey number
//
//post:
// -returns current cost of traversing given section for given journeyNum
//
//O(length of section)
floatWInf graphGroup::currentSectionCost(vector< int > section, int journeyNum) const
{

    return edges.currentSectionCost(section, journeyNum);

}

//graphGroup::currentEdgeCosts()
// returns current cost of traversing given edge for given journeysNum
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -i and j are valid vertex numbers
// -journeysNum is a vector of valid journey numbers
//
//post:
// -returns current cost of traversing given edge for given journeysNum
//
/*/O(1)
/floatWInf graphGroup::currentEdgeCosts(int i, int j, vector< int > journeysNum) const
{

    return edges.currentEdgeCosts(i, j, journeysNum);

}
*/

//graphGroup::currentSectionCosts()
// returns current cost of traversing given section for given journeysNum
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -section is a vector of valid vertex numbers
// -journeysNum is a vector of valid journey numbers
//
//post:
// -returns current cost of traversing given section for given journeysNum
//
//O(length of section)
/*
floatWInf graphGroup::currentSectionCosts(vector< int > section, vector< int > journeysNum) const
{

    return edges.currentSectionCosts(section, journeysNum);

}
*/

//graphGroup::isJourneyIn()
// returns true if given edge has given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -i and j are valid vertex numbers
// -journeyNum is a valid journey number
//
//post:
// -returns true if given edge has given journey
//          false otherwise
//
//O(1)
bool graphGroup::isJourneyIn(int i, int j, int journeyNum) const
{

    return edges.isJourneyIn(i, j, journeyNum);

}

//graphGroup::isJourneyInSection()
// returns true if given section has given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -section is a vector of valid vertex numbers
// -journeyNum is a valid journey number
//
//post:
// -returns true if given section has given journey
//          false otherwise
//
//O(1)
bool graphGroup::isJourneyInSection(vector< int > section, int journeyNum) const
{

    return edges.isJourneyInSection(section, journeyNum);

}

//graphGroup::numJourneysUsing()
// returns number of journeys currently using
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -i and j are valid vertex numbers
//
//post:
// -returns number of journeys currently using
//
int graphGroup::numJourneysUsing(int i, int j) const
{

    return edges.numJourneysUsing(i, j);

}


//graphGroup::Dijkstra()
// returns a vector of the shortest paths from given vertex for a given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -ii is a valid vertex number
// -journeyNum is a valid number of a journey
//
//post:
// -returns a vector of the shortest paths from given vertex for a given journey
//
vector< vector< path > > graphGroup::Dijkstra(int ii, int journeyNum)
{
    vector< vertex > vertices;
    floatWInf infiniteFloat;
    floatWInf zeroFloat;
    intWInf infiniteInt;
    vector< int > actualPath;
    vector< vector< path > > answers;
    zeroFloat.setValue(0);
    bool greater;

    //prepare vertices for Dijkstra
    vertices.resize(returnN());

    for(int i = 0; i < returnN(); i++)
    {
        greater=false;
        vertices[i].setCost(infiniteFloat);  //set cost to infinity
        vertices[i].setPredecessors(infiniteInt, greater);  //set predecessor to null
    }

    vertices[ii].setCost(zeroFloat);  //set cost of source to be 0

    //if Q[i] == true, then vertex i has not yet been extracted
    bool Q[returnN()];
    for(int i = 0; i < returnN(); i++)
        Q[i] = true;
    int u; //current vertex being looked at
    intWInf tempU;

    //Dijkstra's algorithm:
    for(int j = 0; j < returnN(); j++)
    {
        u = ii;

        //select lowest cost vertex to reach
        for(int i = 0; i < returnN(); i++)
            if((Q[i] == true)                                    //if ( (Q[i] is true)
        &&((Q[u] == false)                                 //and ( (Q[u] is false)
        ||(vertices[i].cost() < vertices[u].cost())))      //or (i < u)))
        {
            u = i;                                //replace u with i
        }

        Q[u] = false;

        //relax other vertices
        for(int v = 0; v < returnN(); v++)
        {
            if(vertices[v].cost() > (vertices[u].cost() + graph.cost(u, v)))  //(v > u + w(u, v))
        {
            greater=true;
            vertices[v].setCost(vertices[u].cost() + graph.cost(u, v));
            tempU.setValue(u);
            vertices[v].setPredecessors(tempU, greater);
        }
        else if(vertices[v].cost() == (vertices[u].cost() + graph.cost(u, v)))
            if(!((vertices[u].cost() + graph.cost(u, v))==infiniteFloat))
                if(u!=v)
                {
                    greater=false;
                    vertices[v].setCost(vertices[u].cost() + graph.cost(u, v));
                    tempU.setValue(u);
                    vertices[v].setPredecessors(tempU, greater);
                }
        }
    }

    //costs = vertices;

    answers.resize(returnN());
    for(int i(0); i < returnN(); i++)
        answers[i].resize(1);

    //find and return paths:
        for(int v = 0; v < returnN(); v++)
        {
            actualPath.resize(0);

            actualPath.push_back(v);
            findPath(ii, v, vertices, actualPath, answers, v);
            if(answers[v][0].isNull())
                answers[v][0].setPath(actualPath, vertices[v].cost());
        }

        /*cout << "\n\nANSWERS IN DIJKSTRA***: \n";
         *    for(int i(0); i<answers.size(); i++)
         *    {
         *    for(int j(0); j<answers[i].size(); j++)
         *    {
         *        for( int k(0); k< answers[i][j].length(); k++)
         *            cout << answers[i][j].returnVertex(k) << "  ";
         *        cout << endl;
         }
         cout << endl;
         }
         cout << "\n\nEND ANSWERS***\n\n";*/

        return answers;
}

//graphGroup::dijkstraCost()
// finds the cost of the shortest paths from given vertex for a given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -ii is a valid vertex number
// -journeyNum is a valid number of a journey
// -vertices has been created and resized
//
//post:
// -vertices is set to the cost of the shortest paths from given vertex for a given journey
//
void graphGroup::dijkstraCost(int ii, int journeyNum, vector< vertex > & vertices)
{
    floatWInf infiniteFloat;
    floatWInf zeroFloat;
    intWInf infiniteInt;
    zeroFloat.setValue(0);
    bool greater;

    //prepare vertices for Dijkstra
    vertices.resize(returnN());

    for(int i = 0; i < returnN(); i++)
    {
        greater=false;
        vertices[i].setCost(infiniteFloat);  //set cost to infinity
        vertices[i].setPredecessors(infiniteInt, greater);  //set predecessor to null
    }

    vertices[ii].setCost(zeroFloat);  //set cost of source to be 0

    //if Q[i] == true, then vertex i has not yet been extracted
    bool Q[returnN()];
    for(int i = 0; i < returnN(); i++)
        Q[i] = true;
    int u; //current vertex being looked at
    intWInf tempU;

    //Dijkstra's algorithm:
    for(int j = 0; j < returnN(); j++)
    {
        u = ii;

        //select lowest cost vertex to reach
        for(int i = 0; i < returnN(); i++)
            if((Q[i] == true)                                    //if ( (Q[i] is true)
        &&((Q[u] == false)                                 //and ( (Q[u] is false)
        ||(vertices[i].cost() < vertices[u].cost())))      //or (i < u)))
        {
            u = i;                                //replace u with i
        }

        Q[u] = false;

        //relax other vertices
        for(int v = 0; v < returnN(); v++)
        {
            if(vertices[v].cost() > (vertices[u].cost() + graph.cost(u, v)))  //(v > u + w(u, v))
        {
            greater=true;
            vertices[v].setCost(vertices[u].cost() + graph.cost(u, v));
            tempU.setValue(u);
            vertices[v].setPredecessors(tempU, greater);
        }
        else if(vertices[v].cost() == (vertices[u].cost() + graph.cost(u, v)))
            if(!((vertices[u].cost() + graph.cost(u, v))==infiniteFloat))
                if(u!=v)
                {
                    greater=false;
                    vertices[v].setCost(vertices[u].cost() + graph.cost(u, v));
                    tempU.setValue(u);
                    vertices[v].setPredecessors(tempU, greater);
                }
        }
    }
}


//graphGroup::groupDijkstras()
//groups the dijkstra paths of each journey to provide optimal pairings along common paths
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeysInformation has been properly initialized with real values
//
//post:
// -groups the dijkstra paths of each journey to provide optimal pairings along common paths
/*
vector< vector< path > > graphGroup::groupDijkstras(vector< journeyInfo > & journeysInformation)
{
    vector< vector< path > > groupings;
    vector< vector< path > > newGroupings;
    vector< vector< path > > temp;
    vector< vector< path > > dijkstraJourneys;
    groupings.resize(0);
    newGroupings.resize(0);
    dijkstraJourneys.resize(0);

    //sets 2D vector with dijkstra paths
    for(int i(0); i<journeysInformation.size(); i++)
    {
        temp = (Dijkstra(journeysInformation[i].source(), journeysInformation[i].journeyNum()));
        dijkstraJourneys.push_back(temp[journeysInformation[i].destination()]);
    }

    //finds shared vertices between dijkstra paths of journeys
    for(int i(0); i<dijkstraJourneys.size(); i++)
        for(int j(i+1); j<dijkstraJourneys.size(); j++)
        {
            match commonPaths(dijkstraJourneys[i], dijkstraJourneys[j]);

            //initializes the respective 2D vector to hold the newest groupings
            if(groupings.size()==0)
                groupings = commonPaths.findMatch(i, j);
            else
                newGroupings = commonPaths.findMatch(i, j);

            //Compares newGroupings with Groupings and determines whether or not a group should collaborate with another already
                //created group, or if it should be added as a completely new group
                for(int u(0); u<newGroupings.size(); u++)
                {
                    int ngIndex;
                    path subset;

                    ngIndex=u;
                    checkOverlap(groupings, newGroupings, subset, ngIndex);
                }
        }

        //Tests what is recorded in groupings, during the process of collaborating newGroupings with groupings
        cout << "\n\nTHIS IS WHAT'S IN GROUPINGS:\n\n";

        for(int i(0); i<groupings.size(); i++)
        {
            for(int j(0); j<groupings[i].size(); j++)
            {
                for(int k(0); k<groupings[i][j].length(); k++)
                    cout << groupings[i][j].returnVertex(k) << " ";
                cout << endl;
            }
            cout << endl << endl;
        }

        return groupings;
}
*/

//checkOverlap(vector< vector< path > > const & groupings, vector< vector< path > > const & newGroupings, path & subset, int ngIndex, vector< int > & gIndex)
//sets a flag to keep track of what kind of overlap, if any, occurs between groups from newGroupings and groupings
//
//pre:
// -groupings and newGroupings have been properly set
//
//post:
// -returns flag for what type of collaboration between groups to perform
//
void checkOverlap(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, path & subset, int ngIndex)
{

    for(int v(0); v<groupings.size(); v++)
    {
        path textpath, patternpath;
        vector< int > text, pattern;

        //sets textpath and patternpath respectively
        if(newGroupings[ngIndex][0].length()>groupings[v][0].length())
        {
            textpath=newGroupings[ngIndex][0];
            patternpath=groupings[v][0];
        }
        else
        {
            textpath=groupings[v][0];
            patternpath=newGroupings[ngIndex][0];
        }

        //puts paths into vector to be used in KMP
        for(int k(0); k<patternpath.length(); k++)
            pattern.push_back(patternpath.returnVertex(k));

        //puts paths into vector to be used in KMP
            for(int k(0); k<textpath.length(); k++)
                text.push_back(textpath.returnVertex(k));

            //sets subset to hold the overlapping vertices between two already formed groups
                subset = KMP(text, pattern);

                //This part of the code figures out any overlap between groups, and then determines what groups should
                //be created or added on to.
                if((subset.length()==textpath.length())&&(subset.length()==patternpath.length()))
                {
                    //If subset holds the overlapping vertices between the two groups, and its length
                    //is equal to the lengths of the other two groups, then these two groups must be equal.
                    //Therefore, this exact group from newGroupings already exists in groupings.

                    repeatedGroup(groupings, newGroupings, ngIndex, v);
                }
                else if(subset.length()==patternpath.length())
                {
                    //If subset holds the overlapping vertices between the two groups, and its length
                    //is only equal to one of the groups, then that group must be a subset of the other group.
                    //Therefore, either the group in newGroupings is a subset of the group it's being compared to in groupings,
                    //or the group in groupings is a subset of the group it's being compared to in newGroupings.

                    //Check to see if we've already found that this group exists in groupings, because if it does then that
                    //trumps any discovery that it's a subset of another group in groupings.

                    subsetGroup(groupings, newGroupings, ngIndex, v);
                }
                else if(subset.length()>1)
                {
                    //If subset holds the overlapping vertices between the two groups, and its length is not equal
                    //to either of the other groups lengths, but it is greater than 1, then there is an overlap between
                    //these two groups, however one is not a subset of the other.
                    //Therefore, the group in newGroupings should exist, the group in groupings should exist, and
                    //a new group of the overlap should be created.

                    bool createOverlap=true;

                    for(int k(0); k<groupings.size(); k++)
                        if(groupings[k][0]==subset)
                            createOverlap=false;

                        if(createOverlap)
                        {
                            groupings.resize(groupings.size()+1);
                            groupings[groupings.size()-1].push_back(subset);
                            intersectionGroup(groupings, newGroupings, ngIndex, v);
                        }
                }

                bool createGroup=true;

                for(int k(0); k<groupings.size(); k++)
                    if(groupings[k][0]==newGroupings[ngIndex][0])
                        createGroup=false;

                    if(createGroup)
                        originalGroup(groupings, newGroupings, ngIndex);

    }
}


//void originalGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex)
//Creates an original group in groupings
//
//pre:
// -groupings and newGroupings have been properly set
//
//post:
// -groupings holds a new group of overlapping Dijkstra paths
//
void originalGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex)
{
    groupings.resize(groupings.size()+1);
    for(int k(0); k<newGroupings[ngIndex].size(); k++)
        groupings[groupings.size()-1].push_back(newGroupings[ngIndex][k]);
}


//void repeatedGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex, int gIndex)
//Adds journey information to an overlapping group already created
//
//pre:
// -groupings and newGroupings have been properly set
//
//post:
// -a group in groupings has been updated with all relevant journey information
//
void repeatedGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex, int gIndex)
{
    //Adds information to a group already created in groupings

    //Copies unrecorded journeys into the journey registry (the second element of the second dimension) of groupings
    for(int i(0); i<newGroupings[ngIndex][1].length(); i++)
    {
        bool repeatedJourney=false;

        for(int j(0); j<groupings[gIndex][1].length(); j++)
            if(newGroupings[ngIndex][1].returnVertex(i)==groupings[gIndex][1].returnVertex(j))
                repeatedJourney=true;

            if(!repeatedJourney)
                groupings[gIndex][1] = groupings[gIndex][1]+newGroupings[ngIndex][1].returnVertex(i);
    }

    //Copies unrecorded journeys paths into the group
    for(int i(2); i<newGroupings[ngIndex].size(); i++)
    {
        bool repeatedPath=false;

        for(int j(2); j<groupings[gIndex].size(); j++)
            if(newGroupings[ngIndex][i]==groupings[gIndex][j])
                repeatedPath=true;

            if(!repeatedPath)
                groupings[gIndex].push_back(newGroupings[ngIndex][i]);
    }
}


//void subsetGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex)
//Adds journey information to a group which is a subset of another group
//
//pre:
// -groupings and newGroupings have been properly set
//
//post:
// -a group in groupings has been updated with all relevant journey information
//
void subsetGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex, int gIndex)
{
    //Adds the new group to the end of groupings and copies journey information from the overlapping group to the one
    //that is the subset of the other.

    bool createGroup=true;

    for(int k(0); k<groupings.size(); k++)
        if(groupings[k][0]==newGroupings[ngIndex][0])
            createGroup=false;

        //The group that is a subset of the other exists in newGroupings.
            if((newGroupings[ngIndex][0].length()<groupings[gIndex][0].length())&&createGroup)
            {
                groupings.resize(groupings.size()+1);
                groupings[groupings.size()-1]=newGroupings[ngIndex];

                //Copies unrecorded journeys into the journey registry (the second element of the second dimension) of groupings
                for(int i(0); i<groupings[gIndex][1].length(); i++)
                {
                    bool repeatedJourney=false;

                    for(int j(0); j<groupings[groupings.size()-1][1].length(); j++)
                        if(groupings[gIndex][1].returnVertex(i)==groupings[groupings.size()-1][1].returnVertex(j))
                            repeatedJourney=true;

                        if(!repeatedJourney)
                            groupings[groupings.size()-1][1] = groupings[groupings.size()-1][1]+groupings[gIndex][1].returnVertex(i);
                }

                //pushes unrecorded paths onto the new group
                for(int i(2); i<groupings[gIndex].size(); i++)
                {
                    bool originalPath=true;

                    for(int j(2); j<newGroupings[ngIndex].size(); j++)
                        if(groupings[gIndex][i]==newGroupings[ngIndex][j])
                        {
                            originalPath=false;
                            break;
                        }

                        if(originalPath)
                            groupings[groupings.size()-1].push_back(groupings[gIndex][i]);
                }
            }
            else if(newGroupings[ngIndex][0].length()>groupings[gIndex][0].length())//The group that is a subset of the other already exists in groupings.
    {

        //Copies unrecorded journeys into the journey registry (the second element of the second dimension) of groupings
        for(int i(0); i<newGroupings[ngIndex][1].length(); i++)
        {
            bool repeatedJourney=false;

            for(int j(0); j<groupings[gIndex][1].length(); j++)
                if(newGroupings[ngIndex][1].returnVertex(i)==groupings[gIndex][1].returnVertex(j))
                    repeatedJourney=true;

                if(!repeatedJourney)
                    groupings[gIndex][1] = groupings[gIndex][1]+newGroupings[ngIndex][1].returnVertex(i);
        }

        //pushes unrecorded paths onto the pre-existing group
        for(int i(2); i<newGroupings[ngIndex].size(); i++)
        {
            bool originalPath=true;

            for(int j(2); j<groupings[gIndex].size(); j++)
                if(newGroupings[ngIndex][i]==groupings[gIndex][j])
                {
                    originalPath=false;
                    break;
                }

                if(originalPath)
                    groupings[gIndex].push_back(newGroupings[ngIndex][i]);
        }
    }
}

//void intersectionGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex)
//Adds journey information to a group which is a subset of another group
//
//pre:
// -groupings and newGroupings have been properly set
//
//post:
// -a group in groupings has been updated with all relevant journey information
//
void intersectionGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex, int gIndex)
{

    //Adds the information from one group to this new overlap group
    for(int i(1); i<groupings[gIndex].size(); i++)
        groupings[groupings.size()-1].push_back(groupings[gIndex][i]);

    //Copies unrecorded journeys into the journey registry (the second element of the second dimension) of groupings
        for(int i(0); i<newGroupings[ngIndex][1].length(); i++)
        {
            bool repeatedJourney=false;

            for(int j(0); j<groupings[gIndex][1].length(); j++)
                if(newGroupings[ngIndex][1].returnVertex(i)==groupings[groupings.size()-1][1].returnVertex(j))
                    repeatedJourney=true;

                if(!repeatedJourney)
                    groupings[groupings.size()-1][1] = groupings[groupings.size()-1][1]+newGroupings[ngIndex][1].returnVertex(i);
        }

        //Copies unrecorded journeys paths into the group
        for(int i(2); i<newGroupings[ngIndex].size(); i++)
        {
            bool repeatedPath=false;

            for(int j(2); j<groupings[groupings.size()-1].size(); j++)
                if(newGroupings[ngIndex][i]==groupings[groupings.size()-1][j])
                    repeatedPath=true;

                if(!repeatedPath)
                    groupings[groupings.size()-1].push_back(newGroupings[ngIndex][i]);
        }

}


//graphGroup::backtrackPaths()
//Uses overlapping dijkstra path groups to take a shared group of vertices and
//move backward & forward from that group to find optimal paths for journeys
//
//pre:
// -multiple journeys exist
//
//post:
// -void right now, not sure how i want to compare results yet
//
void graphGroup::backtrackPaths(vector< journeyInfo > & journeysInformation, vector< path > dijkstraGroup, vector< vertex > vertices)
{

    cout << "\n\nENTERED BACKTRACK PATHS\n\n";

    int startVertex=dijkstraGroup[0].returnVertex(0);//the first vertex in the shared path
    int endVertex=dijkstraGroup[0].returnVertex(dijkstraGroup[0].length()-1);//the last vertex in the shared path

    vector< int > vertexShared;//keeps track of if a journey wants to backtrack to the current vertex
    vertexShared.resize(dijkstraGroup[1].length());
    for(int i(0); i<vertexShared.size(); i++)
        vertexShared[i]=-1;
    floatWInf infiniteFloat;

    path commonGroup;
    commonGroup=dijkstraGroup[0];
    int numSharing(dijkstraGroup[1].length());//number of journeys sharing the next edge


    //goes through each vertex to find the most beneficial one to move a group of journeys to
    for(int i(0); i<returnN(); i++)
        //picks a vertex that is actually connected, and can be backtracked to
    {
        bool inGroup=false;
        for(int k(0); k<commonGroup.length(); k++)
            if(i==commonGroup.returnVertex(k))
                inGroup=true;
            if((!(returnGraph().cost(startVertex, i)==infiniteFloat))&&(!inGroup))
                //if i is an adjacent vertex
            {
                cout << "start vertex: " << startVertex;
                cout << "\n\nCHECKING ADJACENT VERTEX " << i << "\n\n";

                vector< vertex > backtrackVertices;//helps find the cost of backtracking with a group
                vector< vertex > dijkstraVertices;//holds the cost of an individual journey's dijkstra path
                vector< double > backtrackCost;
                backtrackCost.resize(numSharing);
                double sharedGroupCost(0);//keeps track of cost of common group for each journey sharing it

                vector< int > journeysSharing;//keeps track of which journeys want to backtrack
                journeysSharing.resize(0);
                for(int k(0); k<numSharing; k++)
                    journeysSharing.push_back(dijkstraGroup[1].returnVertex(k));

                for(int k(0); k<(commonGroup.length()-1); k++)
                {
                    sharedGroupCost += graph.cost(commonGroup.returnVertex(k), commonGroup.returnVertex(k+1)).value();
                }

                sharedGroupCost/=numSharing;
                //now sharedGroupCost contains the cost of one journey to cross the shared path

                for(int k(0); k<numSharing; k++)
                    backtrackCost[k]=sharedGroupCost;

                //This gives me the cost of their dijkstra split between the journeys
                    for(int k(0); k<numSharing; k++)
                    {
                        //adds the cost of extending the common path to this vertex
                        backtrackCost[k]+=(returnGraph().returnEdgeCost(startVertex, i).value()/numSharing);

                        //adding cost of their paths before the shared portion
                        backtrackVertices.resize(0);
                        dijkstraCost(journeysInformation[journeysSharing[k]].source(), journeysSharing[k], backtrackVertices);
                        backtrackCost[k]+=backtrackVertices[i].cost().value();

                        //adding cost of their paths after the shared portion
                        backtrackVertices.resize(0);
                        dijkstraCost(endVertex, journeysSharing[k], backtrackVertices);
                        backtrackCost[k]+=backtrackVertices[journeysInformation[journeysSharing[k]].destination()].cost().value();
                    }

                    bool journeysDefect=true;//notifies when no one else wants to defect

                    while(numSharing>1&&journeysDefect)
                    {
                        for(int k(0); k<journeysSharing.size(); k++)
                        {

                            //gets dijkstra cost to compare new backtracked cost to
                            dijkstraCost(journeysInformation[journeysSharing[k]].source(), journeysSharing[k], dijkstraVertices);

                            //comparing costs
                            if(backtrackCost[k]<dijkstraVertices[journeysInformation[journeysSharing[k]].destination()].cost().value())
                            {
                                //if the backtracked cost is better then we reset the backtracked vertex of this journey to this vertex
                                vertexShared[journeysSharing[k]]=i;
                                cout << "\n\nJourney "<< journeysSharing[k] << " backtrack cost better on vertex "<< i << "\n\n";
                            }
                            else
                                vertexShared[journeysSharing[k]]=-1;
                        }

                        //counts how many journeys still want to share this group
                        int newNumSharing(0);
                        for(int k(0); k<vertexShared.size(); k++)
                            if(vertexShared[k]==i)
                                newNumSharing++;

                            if(newNumSharing>0)
                            {

                                vector< int > temp;
                                temp.resize(0);
                                int prevJournSharing=journeysSharing.size();
                                //update journeysSharing
                                for(int k(0); k<prevJournSharing; k++)
                                {
                                    if(vertexShared[journeysSharing[k]]==-1)
                                        //remove this journey from journeySharing
                                    {
                                        cout << "\n\nJourney "<< journeysSharing[k] << " has defected from vertex "<< i << "\n\n";
                                        for(int j(0); j<journeysSharing.size(); j++)
                                            if(journeysSharing[k]!=journeysSharing[j])
                                                temp.push_back(journeysSharing[j]);
                                            journeysSharing=temp;
                                    }
                                    if(k>journeysSharing.size())
                                        break;
                                }

                                //update backtrackCost according to the number of journeys that still want to backtrack
                                for(int k(0); k<vertexShared.size(); k++)
                                    if(vertexShared[k]==i)
                                    {
                                        backtrackCost[k]-=returnGraph().returnEdgeCost(startVertex, i).value()/numSharing;
                                        backtrackCost[k]+=returnGraph().returnEdgeCost(startVertex, i).value()/newNumSharing;
                                    }

                                    //No journeys defected
                                    if(numSharing==newNumSharing)
                                        journeysDefect=false;
                            }

                            numSharing==newNumSharing;
                    }
            }
    }

}


//graphGroup::reversedDijkstra()
//   turns a vector of the shortest paths to given vertex for a given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -jj is a valid vertex number
// -journeyNum is a valid number of a journey
//
//post:
// -returns a vector of the shortest paths to given vertex for a given journey
//
vector< vector< path > > graphGroup::reversedDijkstra(int jj, int journeyNum) const
{

    vector< vertex > vertices;
    floatWInf infiniteFloat;
    floatWInf zeroFloat;
    intWInf infiniteInt;
    vector< int > actualPath;
    vector< vector< path > > answers;
    zeroFloat.setValue(0);

    //prepare vertices for Dijkstra
    vertices.resize(returnN());

    for(int i = 0; i < returnN(); i++)
    {
        vertices[i].setCost(infiniteFloat);  //set cost to infinity
        vertices[i].setPredecessor(infiniteInt);  //set predecessor to null
    }

    vertices[jj].setCost(zeroFloat);  //set cost of destination to be 0

    //if Q[i] == true, then vertex i has not yet been extracted
    bool Q[returnN()];
    for(int i = 0; i < returnN(); i++)
        Q[i] = true;
    int v; //current vertex being looked at
    intWInf tempU;

    //Dijkstra's algorithm:
    for(int j = 0; j < returnN(); j++)
    {
        v = jj;

        //select lowest cost vertex to reach
        for(int i = 0; i < returnN(); i++)
            if((Q[i] == true)                                    //if ( (Q[i] is true)
        &&((Q[v] == false)                                 //and ( (Q[v] is false)
        ||(vertices[i].cost() < vertices[v].cost())))      //or (i < v)))
        {
            v = i;                                //replace v with i
        }

        Q[v] = false;

        //relax other vertices
        for(int u = 0; u < returnN(); u++)
            if(vertices[u].cost() > (vertices[v].cost() + currentEdgeCost(u, v, journeyNum)))  //(u > v + w(u, v))
        {
            vertices[u].setCost(vertices[v].cost() + currentEdgeCost(u, v, journeyNum));
            tempU.setValue(v);
            vertices[u].setPredecessor(tempU);
        }
    }

    answers.resize(returnN());
    for(int i(0); i < returnN(); i++)
        answers[i].resize(1);

    //find and return paths:
        for(int u = 0; u < returnN(); u++)
        {
            actualPath.resize(0);
            findReversedPath(u, jj, vertices, actualPath, answers, u);
            //add source
            actualPath.resize(actualPath.size() + 1);
            for(int v = actualPath.size() - 1; v > 0; v--)
                actualPath[v] = actualPath[v - 1];
            actualPath[0] = u;
            answers[u][0].setPath(actualPath, vertices[u].cost());
        }

        return answers;

}

bool graphGroup::directed() const {
    return graph.directed();
}

//graphGroup::hasSharedPath()
// returns true if given journey has a shared path
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -returns true if given journey has a shared path
//          false otherwise
//
//O(1)
bool graphGroup::hasSharedPath(int journeyNum) const
{

    return journeys.hasSharedPath(journeyNum);

}

//graphGroup::returnSharedCosts()
// returns shared path costs of all journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -returns shared path costs of all journeys
//
//O(numJourneys())
vector< floatWInf > graphGroup::returnSharedCosts() const
{

    vector< floatWInf > answers;

    answers.resize(numJourneys());

    for(int i = 0; i < numJourneys(); i++)
        answers[i] = returnSharedCost(i);

    return answers;

}

//graphGroup::returnSharedCost()
// returns shared path cost of given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -returns shared path cost of given journey
//
//O(1)
floatWInf graphGroup::returnSharedCost(int journeyNum) const
{

    return journeys.sharedCost(journeyNum);

}

//graphGroup::returnSharedPaths()
// returns shared paths of all journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -returns shared paths of all journeys
//
//O(numJourneys() * returnN())
vector< path > graphGroup::returnSharedPaths() const
{

    vector< path > answers;

    answers.resize(numJourneys());

    for(int i = 0; i < numJourneys(); i++)
        answers[i] = returnSharedPath(i);

    return answers;

}

//graphGroup::returnSharedPath()
// returns shared path of given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -returns shared path of given journey
//
//O(returnN())
path const & graphGroup::returnSharedPath(int journeyNum) const
{

    return journeys.sharedPath(journeyNum);

}

//graphGroup::hasSinglePath()
// returns true if given journey has a single path
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -returns true if given journey has a single path
//          false otherwise
//
//O(1)
bool graphGroup::hasSinglePath(int journeyNum) const
{

    return journeys.hasSinglePath(journeyNum);

}

//graphGroup::returnSingleCosts()
// returns single path costs of all journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -returns single path costs of all journeys
//
//O(numJourneys())
vector< floatWInf > graphGroup::returnSingleCosts() const
{

    vector< floatWInf > answers;

    answers.resize(numJourneys());

    for(int i = 0; i < numJourneys(); i++)
        answers[i] = returnSingleCost(i);

    return answers;

}

//graphGroup::returnSingleCost()
// returns single path cost of given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -returns single path cost of given journey
//
//O(1)
floatWInf graphGroup::returnSingleCost(int journeyNum) const
{

    return journeys.singleCost(journeyNum);

}

//graphGroup::returnSinglePaths()
// returns single paths of all journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -returns single paths of all journeys
//
//O(numJourneys() * returnN())
vector< path > graphGroup::returnSinglePaths() const
{

    vector< path > answers;

    answers.resize(numJourneys());

    for(int i = 0; i < numJourneys(); i++)
        answers[i] = returnSinglePath(i);

    return answers;

}

//graphGroup::returnSinglePath()
// returns single path of given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -returns single path of given journey
//
//O(returnN())
path const & graphGroup::returnSinglePath(int journeyNum) const
{

    return journeys.singlePath(journeyNum);

}

//graphGroup::returnSavings()
// returns savings of all journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -returns savings of all journeys
//
//O(numJourneys())
vector< floatWInf > graphGroup::returnSavings() const
{

    vector< floatWInf > answers;

    answers.resize(numJourneys());

    for(int i = 0; i < numJourneys(); i++)
        answers[i] = returnSaving(i);

    return answers;

}

//graphGroup::returnSaving()
// returns saving of given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -returns saving of given journey
//
//O(1)
floatWInf graphGroup::returnSaving(int journeyNum) const
{

    return journeys.saving(journeyNum);

}

//graphGroup::findSP()
// finds shortest path for given journey with current costs
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -returns shortest path for given journey with current costs
//
//O(returnN() ^2)
path graphGroup::findSP(int journeyNum) const
{

    return edges.findSP(journeys.returnInfo(journeyNum));

}

path graphGroup::findSP(int source, int destination) const {
    return edges.findSP(journeyInfo(0, source, destination));
}

//graphGroup::refindSharedCosts()
// refinds shared path costs for all journeys that have shared paths
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -shared path costs for all journeys that have shared paths are reset
//
//O(numJourneys() * returnN())
void graphGroup::refindSharedCosts()
{

    for(int i = 0; i < numJourneys(); i++)
        refindSharedCost(i);

}

//graphGroup::refindSharedCost()
// refinds shared path cost for given journey, if it has a shared path
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -shared path cost for given journey is reset, if it has a shared path
//
//O(returnN())
void graphGroup::refindSharedCost(int journeyNum)
{

    if(hasSharedPath(journeyNum) == true)
        journeys.setSharedCost(journeyNum, currentSectionCost(returnSharedPath(journeyNum).actualPath(), journeyNum));

}

//graphGroup::addJourneysSP()
// adds given journeys by shortest path possible in order
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeysNum is a vector of valid journey number
//
//post:
// -given journeys added by shortest path possible in order
//
//O(journeysNum * max(returnN() ^2, numJourneys() * returnN()))
void graphGroup::addJourneysSP(vector< int > journeysNum)
{

    for(int i = 0; i < journeysNum.size(); i++)
        addJourneySP(journeysNum[i]);

}

//graphGroup::addJourneySP()
// adds given journey by shortest path possible
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -given journey added by shortest path possible
//
//O(max(returnN() ^2, numJourneys() * returnN()))
void graphGroup::addJourneySP(int journeyNum)
{

    addJourney(journeyNum, findSP(journeyNum));

}

//graphGroup::addJourneys()
// adds given journeys on given paths
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeysNum is a vector of valid journey numbers
// -newPaths is vecor or a valid paths
// -journeysNum and newPaths have the same number of elements
//
//post:
// -given journeys added on given paths
//
//O(numJourneys() ^2 * returnN())
void graphGroup::addJourneys(vector< int > journeysNum, vector< path > const & newPaths)
{

    for(int i = 0; i < journeysNum.size(); i++)
        addJourney(journeysNum[i], newPaths[i]);

}

//same as above but adds all journeys
void graphGroup::addJourneys(vector<path> const& newPaths){
    for(int i = 0; i < newPaths.size(); i++)
        addJourney(i, newPaths[i]);
}

//graphGroup::addJourney()
// adds given journey on given path
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
// -newPath is a valid path
//
//post:
// -given journey added on given path
//
//O(numJourneys() * returnN())
void graphGroup::addJourney(int journeyNum, path const & newPath)
{

    journeys.setSharedPath(journeyNum, newPath);

    edges.addJourney(journeyNum, newPath);

    refindSharedCosts();

}

//graphGroup::removeJourney()
// removes shared path for given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -shared path of given journey is removed
//
//O(max(returnN() ^2, numJourneys() * returnN()))
void graphGroup::removeJourney(int journeyNum)
{

    if(hasSharedPath(journeyNum) == true)
    {
        journeys.reset(journeyNum);
        edges.removeJourney(journeyNum);
        refindSharedCosts();
    }

}

//graphGroup::removeAllJourneys();
// removes shared paths for all journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -shared paths of all journeys have been removed
//
//O(numJourneys() * max(returnN() ^2, numJourneys * returN()))
void graphGroup::removeAllJourneys()
{

    for(int i = 0; i < numJourneys(); i++)
        removeJourney(i);

}

//graphGroup::set()
// sets this to inputGroup and journeysInformation
//
//pre:
// -inputGroup is a valid basicEdgeGroup
// -journeysInformation is a vector of journeyInfo
//
//post:
// -this is set to inputGroup and journeysInformation
//
//O(inputGroup.returnN() ^2 * length of journeysInformation)
void graphGroup::set(basicEdgeGroup const & inputGroup, vector< journeyInfo > const & journeysInformation)
{

    graph = inputGroup;

    set(journeysInformation);

}

//graphGroup::set()
// sets this to journeysInformation with same basicEdgeGroup
//
//pre:
// -journeysInformation is a vector of journeyInfo
//
//post:
// -this is set to journeysInformation with same basicEdgeGroup
//
//O(returnN() ^2 * length of journeysInformation)
void graphGroup::set(vector< journeyInfo > const & journeysInformation)
{

    edges.set(graph, journeysInformation.size());

    journeys.set(journeysInformation);

    for(int i = 0; i < numJourneys(); i++)
        journeys.setSinglePath(i, findSP(i));

}

//graphGroup::update_journeys
//updates the journeys denoted by "changed_journey_numbers" to their positions
// in "listOfJourneys"
//pre:
// - listOfJourneys is a list of ALL journeys
// - changed_journey_numbers is a list of indices into listOfJourneys of the
//   journeys to change
//post:
// - the internal journeys of this object have been updated with the new journeys
//   for the journeys listed by "changed_journey_numbers"
// O(returnN()^2 * length of "changed_journey_numbers"
void graphGroup::update_journeys(vector<journeyInfo> const& listOfJourneys,
                                 vector<int> const& changed_journey_numbers){
    for(int i = 0; i < changed_journey_numbers.size(); i++){
        journeys.setSAD(listOfJourneys[changed_journey_numbers[i]]);
    }
}



    //graphGroup::update_edge_cost()
//changes the cost of the edge from i to j into "new_cost"
// pre: i and j are vertices in the graph.
//      There are no journes along the (i,j) edge currently.
// post: the cost of edge (i,j) is now "new_cost"
void graphGroup::update_edge_cost(int i, int j, floatWInf new_cost){
    graph.addEdge(i,j,new_cost);
    edges.update_edge_cost(i,j,new_cost);
}

//graphGroup::tryJourneys()
// finds shortest shared paths for given journeys if each journey is added in order given
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeysNum is a vector of valid journey numbers
//
//post:
// -returns a vector of paths of shortest shared paths of given journeys in the same order as they were given
// -everything is changed back to the way it was before function was called
//
//O(numJourneys() * max(returnN() ^2, numJourneys() * returnN()))
vector< path > graphGroup::tryJourneys(vector< int > journeysNum)
{

    vector< path > answers;
    vector< path > needToReplace;
    vector<int> numToReplace;
    answers.resize(0);
    needToReplace.resize(0);

    //save current paths
    for(int i = 0; i < numJourneys(); i++){
        needToReplace.push_back(returnSharedPath(i));
        numToReplace.push_back(i);
    }

    //remove current paths
    removeAllJourneys();

    //make new paths
    addJourneysSP(journeysNum);

    /*cout << "journey" << journeysNum[0] << endl;
        *    printJourney(journeysNum[0]);*/
    //save new paths
    for(int i = 0; i < journeysNum.size(); i++)
        answers.push_back(returnSharedPath(journeysNum[i]));

    //write over new paths with previous (current) paths
        addJourneys(numToReplace, needToReplace);

        return answers;

}

//findPath()
// recursively finds path of given information
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -source is the source of the path to find
// -destination is the destination of the path to find
// -vertices is a vector of vertex's that have a full predecessor tree
//
//post:
// -actualPath contains the path from source to destination, including source but NOT including destination
//
void graphGroup::findPath(int source, int destination, vector< vertex > const & vertices, vector< int > & actualPath, vector< vector< path > > & answers, int const v) const
{
    if(vertices[destination].cost().isInfinity() == false)
    {
        if(source != destination)
        {
            int size;
            size = vertices[destination].predecessors().size();
            if(size==1)
            {
                if((vertices[destination].predecessors(0).isInfinity() == false)
                    &&(source == vertices[destination].predecessors(0).value()))
                {
                    actualPath.push_back(source);
                    vector< int > temp;
                    temp.resize(0);
                    for(int i(actualPath.size()); i>0; i--)
                        temp.push_back(actualPath[i-1]);
                    actualPath=temp;
                    if(!(answers[v][answers[v].size()-1].isNull()))
                        answers[v].resize(answers[v].size()+1);
                    answers[v][answers[v].size()-1].setPath(actualPath, vertices[v].cost());
                }
                else
                {
                    actualPath.push_back(vertices[destination].predecessors(0).value());//switch
                    findPath(source, vertices[destination].predecessors(0).value(), vertices, actualPath, answers, v);
                }
            }
            else if(size!=0)
                //tiedDijkstra(source, destination, vertices, actualPath, answers, v);
            {
                for(int i(0); i<size; i++)
                {
                    //cout << "\nNumber of Predecessors for vertex " << destination << ": " << size << "\n";
                    for(int j(0); j<answers[vertices[destination].predecessors(i).value()].size(); j++)//
                    {
                        //cout << "\nNumber of Predecessors for vertex " << vertices[destination].predecessors(i).value() << ": " << answers[vertices[destination].predecessors(i).value()].size() << "\n";
                        int index;
                        index=vertices[destination].predecessors(i).value();
                        vector< int > temp;
                        temp=answers[index][answers[index].size()-(j+1)].actualPath();
                        for(int k(0); k<actualPath.size(); k++)
                            temp.push_back(actualPath[actualPath.size()-(k+1)]);
                        if(!(answers[v][answers[v].size()-1].isNull()))
                            answers[v].resize(answers[v].size()+1);
                        answers[v][answers[v].size()-1].setPath(temp, vertices[v].cost());
                    }
                }
            }
        }
    }
}


//findReversedPath()
// recursively finds path of given information
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -source is the source of the path to find
// -destination is the destination of the path to find
// -vertices is a vector of vertex's that have a full predecessor tree
//
//post:
// -actualPath contains the path from source to destination, including destination but NOT including source
//
void graphGroup::findReversedPath(int source, int destination, vector< vertex > const & vertices, vector< int > & actualPath, vector< vector< path > > & answers, int const u) const
{

    if(vertices[source].cost().isInfinity() == false) {
        if(source != destination) {
            if((vertices[source].predecessor().isInfinity() == false)
                &&(destination == vertices[source].predecessor().value()))
                actualPath.push_back(destination);
            else
            {
                actualPath.push_back(vertices[source].predecessor().value());
                findPath(vertices[source].predecessor().value(), destination, vertices, actualPath, answers, u);
            }
        }
    }
}

//KMP(vector< int > const & text, vector< int > const & pattern) const
// member function
//
//pre:
// -text and pattern have been properly set
//
//post:
// -returns any subset of the two given vectors
//
path KMP(vector< int > const & text, vector< int > const & pattern)
{

     path intersection;
	vector< int > newPattern;
	newPattern=pattern;
     //finds consecutively matched vertices
     while(newPattern.size()>1)
     {
     //creates shift table
     vector< int > T(newPattern.size() + 1, -1);
     for(int i = 1; i <= newPattern.size(); i++)
     {
          int pos = T[i - 1];
          while(pos != -1 && newPattern[pos] != newPattern[i - 1])
               pos = T[pos];
          T[i] = pos + 1;
     }

     //finds consecutively matched vertices
     path matches;
     path temp;
     int textp = 0;
     int patternp = 0;
     while(textp < text.size())
     {
          while(patternp != -1 && (patternp == newPattern.size() || newPattern[patternp] != text[textp]))
               patternp = T[patternp];
          if((newPattern[patternp] == text[textp]) && (patternp != -1))
               matches = matches+newPattern[patternp];

          if(patternp == newPattern.size())
               break;

          patternp++;
          textp++;
     }

     if(matches.length()>intersection.length())
          intersection = matches;

     vector< int > tempPattern;
     tempPattern.resize(0);
     for(int i(1); i<newPattern.size(); i++)
          tempPattern.push_back(newPattern[i]);
     newPattern = tempPattern;
     }

     return intersection;
}