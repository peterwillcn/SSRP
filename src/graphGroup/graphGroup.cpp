//Christopher Earl
//graphGroup.cpp
// contains graphGroup member functions

#include <cstdlib>
#include <vector>
#include <iostream>
#include <fstream>
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
#include "match.h"

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

//graphGroup::printGraph()
// prints graph with current costs
//
//pre:
// -this has been set with a basicEdgeGroup
// -number of vertices is less than 101
//
//post:
// -prints graph with current costs
//
//O(returnN() ^2)
void graphGroup::printGraph() const
{
  
  cout << "Printing graph with current costs: (-1 == infinity)" << endl;
  cout << returnN() << " vertices" << endl;
  
  for(int i = 0; i < returnN(); i++)
    {
      for(int j = 0; j < returnN(); j++)
	{
	  if(edges.totalEdgeCost(i, j).isInfinity() == true)
	    cout << InfinitySymbol << FourMinusIS;
	  else
	    if((edges.numJourneysUsing(i, j) < 10)
	       ||(edges.numJourneysUsing(i, j) > -1))
	      cout << edges.totalEdgeCost(i, j).value() << "   ";
	    else if((edges.numJourneysUsing(i, j) < 100)
		    ||(edges.numJourneysUsing(i, j) > -10))
	      cout << edges.totalEdgeCost(i, j).value() << "  ";
	    else
	      cout << edges.totalEdgeCost(i, j).value() << " ";
	}
      cout << endl;
    }
  cout << endl;
  
}



//graphGroup::printJourneys()
// prints all info on journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -prints all info on journeys
//
//O(numJourneys() * returnN())
void graphGroup::printJourneys() const
{
  
  cout << "* J = " << numJourneys() << endl;
  for(int i = 0; i < numJourneys(); i++)
    printJourney(i);
  
}

//graphGroup::printJourney()
// prints all info on given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -prints all info on given journey
//
//O(returnN())
void graphGroup::printJourney(int journeyNum) const
{
  
  cout << "j" << journeyNum << ": " << endl;
  printJourneyCost(journeyNum);
  printJourneyPath(journeyNum);
  cout << endl;
  
}

//graphGroup::printJourneyPaths()
// prints paths for all journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -prints paths for all journeys
//
//O(numJourneys() * returnN())
void graphGroup::printJourneyPaths() const
{
  
  cout << "Paths for journeys: " << endl;
  for(int i = 0; i < numJourneys(); i++)
    printJourneyPath(i);
  
}

//graphGroup::printJourneyPath()
// prints paths for given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -prints paths for given journey
//
//O(returnN())
void graphGroup::printJourneyPath(int journeyNum) const
{
  
  cout << "sP " << journeyNum;
  if(journeys.hasSinglePath(journeyNum) == true)
    {
      cout << ":" << endl;
      for(int i = 0; i < journeys.singleActualPath(journeyNum).size(); i++)
	cout << journeys.singleActualPath(journeyNum)[i] << " ";
      cout << endl;
    }
  else
    cout << " is N/A." << endl;
  
  cout << "SP " << journeyNum;
  if(journeys.hasSharedPath(journeyNum) == true)
    {
      cout << ":" << endl;
      for(int i = 0; i < journeys.sharedActualPath(journeyNum).size(); i++)
	cout << journeys.sharedActualPath(journeyNum)[i] << " ";
      cout << endl;
    }
  else
    cout << " is N/A." << endl;
  
}

//graphGroup::printJourneyCosts()
// prints costs and savings for all journeys
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
//
//post:
// -prints costs and savings for all journeys
//
//O(numJourneys())
void graphGroup::printJourneyCosts() const
{
  
  cout << "Costs for journeys: " << endl;
  for(int i = 0; i < numJourneys(); i++)
    printJourneyCost(i);
  
}

//graphGroup::printJourneyCost()
// prints costs and savings for given journey
//
//pre:
// -this has been set with a basicEdgeGroup and a vector of journeyInfos
// -journeyNum is a valid journey number
//
//post:
// -prints costs and savings for given journey
//
//O(1)
void graphGroup::printJourneyCost(int journeyNum) const
{
   
  cout << "sP " << journeyNum;
  if(journeys.hasSinglePath(journeyNum) == true)
      cout << " C: " << journeys.singleCost(journeyNum).value() << "." << endl;
  else
    cout << " C is N/A." << endl;
  
  cout << "SP " << journeyNum;
  if(journeys.hasSharedPath(journeyNum) == true)
      cout << " C: " << journeys.sharedCost(journeyNum).value() << "." << endl;
  else
    cout << " C is N/A." << endl;
  
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
//O(1)
floatWInf graphGroup::currentEdgeCosts(int i, int j, vector< int > journeysNum) const
{
  
  return edges.currentEdgeCosts(i, j, journeysNum);
  
}

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
floatWInf graphGroup::currentSectionCosts(vector< int > section, vector< int > journeysNum) const
{
  
  return edges.currentSectionCosts(section, journeysNum);
  
}

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
    for(int i(0); i<answers.size(); i++)
    {
      for(int j(0); j<answers[i].size(); j++)
      {
         for( int k(0); k< answers[i][j].length(); k++)
              cout << answers[i][j].returnVertex(k) << "  ";
         cout << endl;
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
//
vector< vector< path > > graphGroup::groupDijkstras(vector< journeyInfo > & journeysInformation/*, vector< vertex > & vertices*/)
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
    printJourney(journeysNum[0]);*/
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
    if(source != destination)
    {
      int size;
      size = vertices[destination].predecessors().size();
      if(size==1)
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
  
  if(vertices[source].cost().isInfinity() == false)
    if(source != destination)
      if((vertices[source].predecessor().isInfinity() == false)
	 &&(destination == vertices[source].predecessor().value()))
	actualPath.push_back(destination);
      else
	{
	  actualPath.push_back(vertices[source].predecessor().value());
	  findPath(vertices[source].predecessor().value(), destination, vertices, actualPath, answers, u);
	}
  
}

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
  
  char usersAnswer;  //holds user's answer
  int n;  //number of vertices
  int type;  //type of graph
  int style;  //style of graph
  int numberOfInfiniteEdges;  //holds number of infinite edges
  int numberOfJourneys;  //holds number of journeys
  
  cout << "Generate a random graph? (y/n) ";
  cin >> usersAnswer;
  if(usersAnswer == 'y')
    {
      cout << endl << "Types: " << endl 
	   << "0 - finite weights" << endl 
	   << "1 - some random infinite weights - Style: # of infinite weights < (n - 2)" << endl
	   << "2 - limited directional movement" << endl
	   << "3 - highway system" << endl
	   << "4 - threaded grid" << endl;
      cout << endl << "What is the type of the graph? ";
      cin >> type;
      cout << endl << "How many vertices? ";
      cin >> n;
      if(type == 1)
	{
	  cout << endl << "What is the style of the graph? ";
	  cin >> style;
	  while(type == 1 && style > n)
	    {
	      cout << endl << "Too many edges. Use less than " << n - 2 << "edges. Style: ";
	      cin >> style;
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
  Style of file:
    n
    infinitySymbol
    00 01 02 03 ... 0(n-2) 0(n-1)  [edge weights for ij ]
    10 11 12 13 ... 1(n-2) 1(n-1)    .
    .  .  .  .  ... .  .   .   .     .
    .  .  .  .  ... .  .   .   .     .
    .  .  .  .  ... .  .   .   .     .
    (n-1)0 (n-1)1  ... (n-1)(n-1)    .
  */  
  
  char answer;  //holds user's answer
  char fileName[40];  //holds file name of file for input
  int n;  //number of vertices
  int type;  //type of graph
  int style;  //style of graph
  float tempWeight;  //float used to hold weight while reading from input file
  floatWInf infiniteWeight(true, 0);  //float used to hold infinity
  float infinitySymbol; //holds symbol of infinity in file
  fstream fin;
  
  cout << "Use aa.txt? (y/n) ";
  cin >> answer;
  if(answer == 'y')
    {
      fileName[0] = 'a';
      fileName[1] = 'a';
      fileName[2] = '.';
      fileName[3] = 't';
      fileName[4] = 'x';
      fileName[5] = 't';
      fileName[6] = 0;
    }
  else
    {
      cout << "Input file name: ";
      cin >> fileName;
      cout << endl;
    }
  
  //read in header info
  fin.open(fileName);
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
  
  srand(time(0));
  
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
  
  char usersAnswer;  //holds user's answer
  int numGraphs;  //number of journeys
  int n;  //number of vertices 
  int type;  //type of graph
  int style;  //style of graph
  int numberOfInfiniteEdges;  //holds number of infinite edges
  int numberOfJourneys;  //holds number of journeys
  
  cout << "How many graphs? ";
  cin >> numGraphs;
  inputGroups.resize(numGraphs);
  
  cout << "Generate graphs randomly? (y/n) ";
  cin >> usersAnswer;
  if(usersAnswer == 'y')
    {
      cout << endl << "Types: " << endl 
	   << "0 - finite weights" << endl 
	   << "1 - some random infinite weights - Style: # of infinite weights < (n - 2)" << endl
	   << "2 - limited directional movement" << endl
	   << "3 - highway system" << endl
	   << "4 - threaded grid" << endl;
      cout << endl << "What is the type of the graph? ";
      cin >> type;
      cout << endl << "How many vertices? ";
      cin >> n;
      cout << endl;      
      if(type == 1)
	{
	  cout << endl << "What is the style of the graph? ";
	  cin >> style;
	  while(type == 1 && style > n)
	    {
	      cout << endl << "Too many edges. Use less than " << n - 2 << " edges. Style: ";
	      cin >> style;
	    }
	}
      else
	style = 0;

      
      generateGraphs(inputGroups, n, type, style);
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
void generateGraphs(vector< basicEdgeGroup > & randomGraphs, int n, int type, int style)
{
  
  char usersAnswer;
  bool directed;  //true if graph is directed
  int numOfRanges;  //number of ranges
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
  
  srand(time(0));
  
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
    }
  
  for(int g = 0; g < randomGraphs.size(); g++)
    {
      randomGraphs[g].setN(n);
      
      if((type == 0) || (type == 1))  //finite weights or some random infinite weights
	{
	  //begin work
	  if(directed == true)  //directed graph
	    for(int k = 0; k < n; k++)
	      if(numOfRanges == 1) //only one range
		for(int l = 0; l < n; l++)
		  //select random weights
		  if(k == l)
		    randomGraphs[g].addEdge(k, l, 0);
		  else
		    randomGraphs[g].addEdge(k, l, randomWeight(ranges[0][0], ranges[0][1]));
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
			randomGraphs[g].addEdge(k, whichRange[l], 0);
		      else
			{
			  currentRange = l / rangeIncrement;
			  if(currentRange > numOfRanges)
			    currentRange = numOfRanges;
			  
			  randomGraphs[g].addEdge(k, whichRange[l], randomWeight(ranges[currentRange][0], ranges[currentRange][1]));
			}
		    }
		}
	  else //undirected graph
	    for(int k = 0; k < n; k++)
	      if(numOfRanges == 1) //only one range
		for(int l = k; l < n; l++)
		  //select random weights
		  if(k == l)
		    randomGraphs[g].addEdge(k, l, 0);
		  else
		    {
		      tempValue = randomWeight(ranges[0][0], ranges[0][1]);
		      randomGraphs[g].addEdge(k, l, tempValue);
		      randomGraphs[g].addEdge(l, k, tempValue);
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
			randomGraphs[g].addEdge(k, whichRange[l], 0);
		      else
			{
			  currentRange = l / rangeIncrement;
			  if(currentRange >= numOfRanges)
			    currentRange = numOfRanges - 1;
			  
			  tempValue = randomWeight(ranges[currentRange][0], ranges[currentRange][1]);
			  randomGraphs[g].addEdge(k, whichRange[l], tempValue);
			  randomGraphs[g].addEdge(whichRange[l], k, tempValue);
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
		     &&(randomGraphs[g].cost(i, j).isInfinity() == false))
		    {
		      if(directed == true)  //directed graph
                    randomGraphs[g].addEdge(i, j, infiniteWeight);
		      else  //undirected graph
		      {
                    randomGraphs[g].addEdge(i, j, infiniteWeight);	
			        randomGraphs[g].addEdge(j, i, infiniteWeight);
              }
		      
		      numberOfEdgesLeft--;
		    }
		}
	    }
	}
      else if(type == 2)  //limited directional movement
	{
	  //begin work
	  for(int k = 0; k < n; k++)
	    if(directed == true) //directed graph
	      for(int l = 0; l < n; l++)
		//select random weights
		if(k == l)
		  randomGraphs[g].addEdge(k, l, 0);
		else if((k - limitedback <= l) && (k + limitedforward >= l))
		  randomGraphs[g].addEdge(k, l, randomWeight(ranges[0][0], ranges[0][1]));
		else
		  randomGraphs[g].addEdge(k, l, infiniteWeight);
	    else //undirected graph
	      for(int l = k; l < n; l++)
		//select random weights
		if(k == l)
		  randomGraphs[g].addEdge(k, l, 0);
		else if((k - limitedback <= l) && (k + limitedforward >= l)) //k and l are connected
		  {
		    tempValue = randomWeight(ranges[0][0], ranges[0][1]);
		    randomGraphs[g].addEdge(k, l, tempValue);
		    randomGraphs[g].addEdge(l, k, tempValue);
		  }
		else  //k and l are not connected
		  {	     
		    randomGraphs[g].addEdge(k, l, infiniteWeight);
		    randomGraphs[g].addEdge(l, k, infiniteWeight);
		  }
	}
      else if(type == 3)  //highway system
	{
	  //begin work
	  for(int k = 0; k < highway; k++)
	    {
	      randomGraphs[g].addEdge(k, k, 0);
	      
	      //select weights for edges along highway
	      if(k < highway - 1) //to keep intra-highway ranges within the highway only
		{
		  tempValue = randomWeight(ranges[0][0], ranges[0][1]);
		  randomGraphs[g].addEdge(k, k + 1, tempValue);
		  randomGraphs[g].addEdge(k + 1, k, tempValue);
		}
	      
	      //select weights for edges not along highway
	      for(int l = highway; l < n; l++)
		{
		  tempValue = randomWeight(ranges[1][0], ranges[1][1]);
		  randomGraphs[g].addEdge(k, l, tempValue);
		  randomGraphs[g].addEdge(l, k, tempValue);
		}
	    }
	}
      else if(type == 4)  //threaded grid
	{
	  //begin work
	  for(int k = 0; k < n; k++)
	    for(int l = k; l < n; l++)
	      {
		//select random weights for:
		if(k == l)  //same vertex
		  randomGraphs[g].addEdge(k, l, 0);
		else if(k / perLevel == l / perLevel) //same level
		  {
		    tempValue = randomWeight(ranges[0][0], ranges[0][1]);
		    randomGraphs[g].addEdge(k, l, tempValue);
		    randomGraphs[g].addEdge(l, k, tempValue);
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
			randomGraphs[g].addEdge(k, l, tempValue);
			randomGraphs[g].addEdge(l, k, tempValue);
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
  Format of file:
    numJourneys
    source0 destination0
    source1 destination1
    .           .
    .           .
    .           .
    source(n-1) destination(n-1)
  */
  char usersAnswer;  //holds user's answer
  char fileName[40];  //holds file name of file for input
  int testNumber;  //holds file/test number
  int tempVertex = 0;  //holds vertex number while reading from file
  int numJourneys;  //number of journeys
  fstream fin;
  
  cout << "What is number in file name 'j###.txt'? ";
  cin >> testNumber;
  
  fileName[0] = 'j';
  if(testNumber < 10)
    {
      fileName[1] = '0';
      fileName[2] = '0';
      fileName[3] = testNumber + '0';
    }
  else if(testNumber < 100)
    {
      fileName[1] = '0';
      fileName[2] = (testNumber / 10) + '0';
      fileName[3] = (testNumber % 10) + '0';
    }
  else
    {
      fileName[1] = (testNumber / 100) + '0';
      fileName[2] = (testNumber / 10) + '0';
      fileName[3] = (testNumber % 10) + '0';
    }
  fileName[4] = '.';
  fileName[5] = 't';
  fileName[6] = 'x';
  fileName[7] = 't';
  fileName[8] = 0;

  fin.open(fileName);
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
  
  double precent;  //random number between 0 and 1, including 0 but not 1
  
  precent = ( (double)rand() / ((double)(RAND_MAX)+(double)(1)) );  //precent is between 0 and 1 not including 1
  
  return (int)(precent * randMax);
  
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
  
  int range = (max - min);  //range that number to generate can be within
  
  int randomNumber = randomGenerator(range);  //generate number in range
  
  return (min + randomNumber);  //shift number into proper range and return it
  
}

