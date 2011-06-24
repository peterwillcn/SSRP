//Christopher Earl
//path.cpp
// contains path member functions

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#include "basicStructures.h"
#include "path.h"

//path::path()
// c'tor
//
//pre:
// -none
//
//post:
// -path constructed to empty path and infinite cost
//
//O(1)
path::path()
  :internalCost(), internalActualPath()
{
 
}

//path::path()
// c'tor
//
//pre:
// -newPath is a valid path
//
//post:
// -path constructed to newPath's values
//
//O(length of actualPath)
path::path(const path& newPath)
  :internalCost(newPath.internalCost), internalActualPath(newPath.internalActualPath)
{
  
}

//path::path()
// c'tor
//
//pre:
// -actualPath is a vector of valid vertex numbers
// -cost is a valid floatWInf
//
//post:
// -path constructed to actualPath and cost
//
//O(length of actualPath)
path::path(vector< int > const & actualPath, floatWInf cost)
  :internalCost(cost), internalActualPath(actualPath)
{
  
}


//path::path()
// c'tor
//
//pre:
// -pathA and PathB are valid paths
// 
//
//post:
// -constructs a path which consists of concatenating path B at the end of
//  path A.
// - if the last element of pathA == the first element of path B, then the 
//   vertex is seen once in the new path
// - cost of the new path is the sum of the costs of the old paths
//
//O(length of actualPath)
path::path(path const& pathA, path const& pathB){
  internalActualPath = pathA.actualPath();

  if(internalActualPath.size() == 0){ // path A is empty
    internalActualPath = pathB.actualPath();
  }
  else{
    int start_position = 0;  //where we start copying from pathB
    if(pathB.actualPath()[0] == internalActualPath[internalActualPath.size()-1])
      start_position = 1;
    for(int i = start_position; i < pathB.actualPath().size(); i++){
      internalActualPath.push_back(pathB.actualPath()[i]);
    }
    setCost(pathA.cost() + pathB.cost());
  }
}
//path::cost()
// returns cost to travel path
//
//pre:
// -none
//
//post:
// -returns cost to travel path
//
//O(1)
floatWInf path::cost() const
{
  
  return internalCost;
  
}

//path::operator>()
// returns true if this costs more than other
//
//pre:
// -other is a valid path
//
//post:
// -returns true if this cost more than other
//          false otherwise
//
//O(1)
bool path::operator>(path const & other) const
{
  
  return cost() > other.cost();
  
}

//path::operator>()
// returns true if this costs more than constCost
//
//pre:
// -constCost is a valid floatWInf
//
//post:
// -returns true if this cost more than other
//          false otherwise
//
//O(1)
bool path::operator>(floatWInf const & constCost) const
{
  
  return cost() > constCost;
  
}

//path::operator+(int const & element)
// adds an element to this path
//
//pre:
// -element has been properly initialized
//
//post:
// -path now has element appended to its end
//
//O(1)
path path::operator+(int const & element)
{
     vector< int > tempPath;
     tempPath = internalActualPath;
     tempPath.push_back(element);
     path returnTemp;
     returnTemp.setPath(tempPath, internalCost);
     
     return returnTemp;
}

//path::operator==(path const & other)
// compares two paths
//
//pre:
// -this & other have been properly set
//
//post:
// -returns true if these two paths are the same, and false otherwise
//
bool path::operator==(path const & other) const
{
     if(internalActualPath.size()!=other.actualPath().size())
          return false;
     else
     {
         for(int i(0); i<internalActualPath.size(); i++)
              if(internalActualPath[i]!=other.returnVertex(i))
                   return false;
         return true;
     }
}

//path::returnVertex()
// returns vertex in ith position in path
//
//pre:
// -i is between 0 and length()
//
//post:
// -returns vertex in ith position in path
//          -1 if path is null
//
//O(1)
int path::returnVertex(int i) const
{
  
  if(isNull() == true)
    return -1;
  else
    return internalActualPath[i];
  
}

//path::returnStart()
// returns vertex at start of path
//
//pre:
// -none
//
//post:
// -returns vertex at start of path
//          -1 if path is null
//
//O(1)
int path::returnStart() const
{
  
  if(isNull() == true)
    return -1;
  else
    return internalActualPath[0];
  
}

//path::returnEnd()
// returns vertex at end of path
//
//pre:
// -none
//
//post:
// -returns vertex at end of path
//          -1 if path is null
//
//O(1)
int path::returnEnd() const
{
  
  if(isNull() == true)
    return -1;
  else
    return internalActualPath[length() - 1];
  
}

//path::isSingleEdge()
// returns true if path is only one edge long
//
//pre:
// -none
//
//post:
// -returns true if path is only one edge long
//          false otherwise
//
//O(1)
bool path::isSingleEdge() const
{
  
  if(length() == 2)
    return true;
  else
    return false;
  
}

//path::isNull()
// returns true if path is null
//
//pre:
// -none
//
//post:
// -returns true if path is null
//          false otherwise
//
//O(1)
bool path::isNull() const
{
  
  if((length() == 0)
     ||(length() == 1))
    return true;
  else
    return false;
  
}

//path::length()
// returns the number of vertices in the path
//
//pre:
// -none
//
//post:
// -returns the number of vertices in the path
//
//O(1)
int path::length() const
{
  
  return internalActualPath.size();
  
}

int path::getElement(int ref) const {
    return internalActualPath[ref];
}

//path::actualPath()
// returns actual path
//
//pre:
// -none
//
//post:
// -returns actual path
//
//O(1)
vector< int > const & path::actualPath() const
{
  
  return internalActualPath;
  
}

//path::setPath()
// sets path to newPath and costs to nweCosts
//
//pre:
// -newPath is a vector of int's
// -newCosts is a vector of floatWInf with one less element than newPath
//
//post:
// -path is set to newPath with costs from newCosts
//
//O(length of newPath)
void path::setPath(vector< int > const & newPath, floatWInf newCost)
{
  internalActualPath.resize(newPath.size());
  internalCost = newCost;
  for(int i = 0; i < length(); i++)
    {
      internalActualPath[i] = newPath[i];
    }
}

//path::setCost()
// sets path to newPath and costs to newCosts
//
//pre:
// -newCosts is a vector of floatWInf with one less element than length()
//
//post:
// -path is set to newPath with costs from newCosts
//
//O(1)
void path::setCost(floatWInf newCost)
{
  
  internalCost = newCost;
  
}
