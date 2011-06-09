//Christopher Earl
//basicEdgeGroup.cpp
// contains basicEdgeGroup member functions

#include <vector>

using namespace std;

#include "basicStructures.h"
#include "basicEdgeGroup.h"

///
///basicEdgeGroup member functions
///

//basicEdgeGroup::basicEdgeGroup()
// c'tor
//
//pre:
// -none
//
//post:
// -basicEdgeGroup constructed with no vertices, type == 0, and style ==0
//
//O(1)
basicEdgeGroup::basicEdgeGroup()
  :group(), type(0), style(0)
{
  
}

//basicEdgeGroup::basicEdgeGroup()
// c'tor
//
//pre:
// -newGroup is a valid basicEdgeGroup
//
//post:
// -basicEdgeGroup constructed with newGroup's values
//
//O(newGroup.returnN() ^2)
basicEdgeGroup::basicEdgeGroup(const basicEdgeGroup& newGroup)
  :type(newGroup.returnType()), style(newGroup.returnStyle()), isDirected(newGroup.directed())
{
  
  setN(newGroup.returnN());
  
  for(int i = 0; i < returnN(); i++)
    for(int j = 0; j < returnN(); j++)
      addEdge(i, j, newGroup.cost(i, j));
  
}

//basicEdgeGroup::basicEdgeGroup()
// c'tor
//
//pre:
// -numVertices is a valid number of vertices
//
//post:
// -basicEdgeGroup constructed with numVertices, type == 0, and style ==0
//
//O(numVertices ^2)
basicEdgeGroup::basicEdgeGroup(int numVertices)
  :type(0), style(0)
{
  
  setN(numVertices);
  
}

//basicEdgeGroup::basicEdgeGroup()
// c'tor
//
//pre:
// -numVertices is a valid number of vertices
// -newType is a valid type
// -newStyle is a valid style
//
//post:
// -basicEdgeGroup constructed with numVertices, newType, and newStyle
//
//O(numVertices ^2)
basicEdgeGroup::basicEdgeGroup(int numVertices, int newType, int newStyle)
  :type(newType), style(newStyle)
{
  
  setN(numVertices);
  
}

//basicEdgeGroup::returnN()
// returns n
//
//pre:
// -none
//
//post:
// -returns n
//
//O(1)
int basicEdgeGroup::returnN() const
{
  
  return group.size();
  
}

//basicEdgeGroup::returnType()
// returns type of graph
//
//pre:
// -none
//
//post:
// -returns type of graph
//
//O(1)
int basicEdgeGroup::returnType() const
{
  
  return type;
  
}

//basicEdgeGroup::returnStyle()
// returns style of graph
//
//pre:
// -none
//
//post:
// -returns style of graph
//
//O(1)
int basicEdgeGroup::returnStyle() const
{
  
  return style;
  
}

//basicEdgeGroup::returnEdgeCost(int i, int j)
// returns a vertex of the graph
//
//pre:
// -the group has been set
//
//post:
// -returns a vertex of the graph
//
//O(1)
floatWInf basicEdgeGroup::returnEdgeCost(int i, int j) const
{
     return group[i][j].value();
}

//basicEdgeGroup::reverse()
// sets reversee to same graph with edges reversed
//
//pre:
// -reversee is a valid basicEdgeGraph
//
//post:
// -reversee is set to same graph with edges reversed
//
//O(1)
void basicEdgeGroup::reverse(basicEdgeGroup & reversee) const
{
  
  int n = returnN();
  reversee.setN(n);
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      reversee.addEdge(j, i, cost(i, j));

  
}

bool basicEdgeGroup::directed() const {
    return isDirected;
}

//basicEdgeGroup::setN()
// sets number of vertices in graph
//
//pre:
// -newN is a positive int
//
//post:
// -number of vertices in graph is equal to newN
//
//O(newN ^2)
void basicEdgeGroup::setN(int newN)
{
  
  group.resize(newN);
  for(int i = 0; i < newN; i++)
    group[i].resize(newN);
  
}

//basicEdgeGroup::setType()
// sets type to newType
//
//pre:
// -newType is a valid type
//
//post:
// -type equals newType
//
//O(1)
void basicEdgeGroup::setType(int newType)
{
  
  type = newType;
  
}

//basicEdgeGroup::setStyle()
// sets style to newStyle
//
//pre:
// -newStyle is a valid style for type
//
//post:
// -style equals newStyle
//
//O(1)
void basicEdgeGroup::setStyle(int newStyle)
{
  
  style = newStyle;
  
}

void basicEdgeGroup::setDirected() {
    isDirected = true;
}

void basicEdgeGroup::setUndirected() {
    isDirected = false;
}

//basicEdgeGroup::cost()
// returns cost of edge(i, j)
//
//pre:
// -i and j are valid vertices in graph
//
//post:
// -returns cost of edge(i, j)
//
//O(1)
floatWInf basicEdgeGroup::cost(int i, int j) const
{
  
  return group[i][j];
  
}

//basicEdgeGroup::addEdge()
// sets edge's cost to weight
//
//pre:
// -weight is a valid floatWInf
//
//post:
// -edge's cost equals weight
//
//O(1)
void basicEdgeGroup::addEdge(int i, int j, floatWInf weight)
{

  group[i][j] = weight;
  
}

