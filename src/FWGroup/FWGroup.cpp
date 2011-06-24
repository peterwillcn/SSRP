//Christopher Earl
//FWGroup.cpp
// contains FWGroup member functions

#include <vector>
#include <iostream>

using namespace std;

#include "basicStructures.h"
#include "vertex.h"
#include "path.h"
#include "graphGroup.h"
#include "FWGroup.h"

//FWGroup::FWGroup()
// c'tor
//
//pre:
// -none
//
//post:
// -FWGroup constructed without values
//
FWGroup::FWGroup()
  : numJ(0), sections()
{
  
}

//FWGroup::returnPath()
// returns path between i and j
//
//pre:
// -FWGroup has been set
// -i and j are valid vertex numbers
//
//post:
// returns path between i and j
//
path const & FWGroup::returnPath(int i, int j) const
{
  
  return sections[i][j];
  
}

//FWGroup::cost()
// returns cost of path between i and j
//
//pre:
// -FWGroup has been set
// -i and j are valid vertex numbers
//
//post:
// -returns cost of path between i and j
//
floatWInf FWGroup::cost(int i, int j) const
{
  
  return sections[i][j].cost();
  
}

//FWGroup::numJourneys()
// returns number of journeys in FWGroup
//
//pre:
// -FWGroup has been set
//
//post:
// -returns number of journeys in FWGroup
//
int FWGroup::numJourneys() const
{
  
  return numJ;
  
}

//FWGroup::returnN()
// returns number of vertices
//
//pre:
// -FWGroup has been set
//
//post:
// -returns number of vertices
//
int FWGroup::returnN() const
{
  
  return sections.size();
  
}

//FWGroup::set()
// sets numJ and sections to graph with costs based on journeys
//
//pre:
// -journeys is a vector of valid numbers of journeys
// -graph is a valid graphGroup
//
//post:
// -numJ and sections are set to graph with costs based on journeys
//
void FWGroup::set(vector< int > journeysNum, graphGroup const & graph)
{
  numJ = journeysNum.size();
  sections.resize(graph.returnN());
  for(int i = 0; i < returnN(); i++)
    sections[i].resize(returnN());

  FloydWarshall(journeysNum, graph);
  
}

//FWGroup::FloydWarshall()
// fins all-pairs shortest journey paths for given journeys in given graph
//
//pre:
// -sections has been resized
// -journeysNum is a vector of valid journey numbers
// -graph is a valid graphGroup
//
//post:
// -sections contains the single-journey shortest paths and costs of journeysNum in graph
//
void FWGroup::FloydWarshall(vector< int > journeysNum, graphGroup const & graph)
{
  
  intWInf tempValue;
  intWInf tempInf;
  tempInf.setValue();
  vector< int > foundPath;
  vector< int > emptyPath;
  emptyPath.resize(0);
  
  //vertices:
  vector< vector< vertex > > vertices;
  vertices.resize(returnN());
  for(int i = 0; i < returnN(); i++)
    {
      vertices[i].resize(returnN());
      for(int j = 0; j < returnN(); j++)
	{
	  //I changed this tot totalEdgeCosts from currentEdgecosts because
	  // this should show the _unshared_ shortest paths..
	  vertices[i][j].setCost(graph.totalEdgeCost(i, j));
	  // cout << vertices[i][j].cost();
	  if(vertices[i][j].cost().isInfinity() == false)
	    {
	      tempValue.setValue(i);
	      vertices[i][j].setPredecessor(tempValue);
	    }
	  else
	    vertices[i][j].setPredecessor(tempInf);  //infinity
	}
    }
  
  //Floyd-Warshall algorithm:
  for(int k = 0; k < returnN(); k++)
    for(int i = 0; i < returnN(); i++)
      for(int j = 0; j < returnN(); j++)
	if(vertices[i][j].cost() > (vertices[i][k].cost() + vertices[k][j].cost()))
	  {
	    vertices[i][j].setCost(vertices[i][k].cost() + vertices[k][j].cost());
	    vertices[i][j].setPredecessor(vertices[k][j].predecessor());
	  }
  
  //assign paths:
  for(int i = 0; i < returnN(); i++)
    for(int j = 0; j < returnN(); j++)
      {
	foundPath.resize(0);
        findPath(i, j, vertices, foundPath);
	if(foundPath.size() != 0)
	  foundPath.push_back(j);
	if(vertices[i][j].cost().isInfinity() == true)
	  sections[i][j].setPath(emptyPath, vertices[i][j].cost());
	else
	  sections[i][j].setPath(foundPath, vertices[i][j].cost());
      }
  
}

//FWGroup::findPath()
// finds actual path from predecessor graphs
//
//pre:
// -start and end are valid vertex numbers
// -vertices has complete predecessor graphs
//
//post:
// -foundPath contains actual path (without destination vertex) between start and end
//
void FWGroup::findPath(int start, int end, vector< vector< vertex > > const & vertices, vector< int > & foundPath)
{
  
  intWInf tempValue;
  int tempInt;
  
  if(start != end
     && vertices[start][end].predecessor().isInfinity() == false)
    {
      tempValue.setValue(start);
      if(tempValue == vertices[start][end].predecessor())
	foundPath.push_back(start);
      else
	{
	  tempInt = vertices[start][end].predecessor().value();
	  findPath(start, tempInt, vertices, foundPath);
	  foundPath.push_back(tempInt);
	}
    }
  
}

//FWGroup::print_cost_grid
// prints out a grid of shortest path costs between every two vertices
// assumes that the graph has been set (which calls the FW algorithm)
void FWGroup::print_cost_grid() const{
  for(int i = 0; i < returnN(); i++){
    for(int j = 0; j < returnN(); j++){
      cout << cost(i,j) << " ";
    }
    cout << endl;
  }
}
