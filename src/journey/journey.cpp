//Christopher Earl
//journeys.cpp
// contains journey member functions

#include <vector>

using namespace std;

#include "basicStructures.h"
#include "path.h"
#include "journey.h"

//journey::journey()
// c'tor
//
//pre:
// -none
//
//post:
// -journey constructed without values
//
//O(1)
journey::journey()
  :internalSource(), internalDestination(), internalSharedPath(), internalSinglePath()
{
  
}


journey::journey(const journey& other):
internalSource(other.internalSource), 
internalDestination(other.internalDestination),
internalSharedPath(other.internalSharedPath),
internalSinglePath(other.internalSinglePath)
{
}

//journey::journey()
// c'tor
//
//pre:
// -source is a valid vertex number
// -destination is a valid vertex number
//
//post:
// -journey constructed with source and destination
//
//O(1)
journey::journey(int source, int destination)
  :internalSource(source), internalDestination(destination), internalSharedPath(), internalSinglePath()
{
  
}

//journey::returnSAD()
// returns source and destination vertices of this journey
//
//pre:
// -source and destination have been set
//
//post:
// -returns source and destination verteices of this journey
//
//O(1)
vector< int >  journey::returnSAD() const
{
  
  vector< int > answer;
  answer.resize(2);
  answer[0] = internalSource;
  answer[1] = internalDestination;
  
  return answer;
  
}

//journey::saving()
// returns current savings of this journey
//
//pre:
// -none
//
//post:
// -returns current savings of this journey
//          0 if shared cost is infinity or there is no shared path (or difference is actually 0)
//          infinity if there is a shared path but no single path (doesn't happen hopefully)
//          some number (possibly 0) if both paths exist
//
//O(1)
floatWInf journey::saving() const
{
  
  floatWInf answer;
  answer.setValue();

  if((internalSharedPath.isNull() == true)
     ||(internalSharedPath.cost().isInfinity() == true))
    answer.setValue(0);
  else
    if((internalSinglePath.isNull() == true)
       ||(internalSinglePath.cost().isInfinity() == true))
      answer.setValue();
    else
      answer = singleCost().value() - sharedCost().value();
 
  return answer;
  
}

//journey::setSAD()
// sets source and destination
//
//pre:
// -newSource and newDestination are valid vertices
//
//post:
// -source equals newSource
// -destination equals newDestination
//
//O(1)
void journey::setSAD(int newSource, int newDestination)
{
  
  path emptyPath;
  
  reset();
  setSinglePath(emptyPath);

  internalSource = newSource;
  internalDestination = newDestination;
  
}

//journey::reset()
// erases shared path but leaves source, destination and single path alone
//
//pre:
// -none
//
//post:
// -shared path is now null but source, destination, and single path are the same
//
//O(1)
void journey::reset()
{
   
  path emptyPath;
  
  setSharedPath(emptyPath);
  
}

//journey::hasSharedPath()
// returns true if journey currently has a shared path
//
//pre:
// -none
//
//post:
// -returns true if journey currently has a shared path
//          false otherwise
//
//O(1)
bool journey::hasSharedPath() const
{
  
  return !(internalSharedPath.isNull());
  
}

//journey::sharedCost()
// returns cost of shared path
//
//pre:
// -none
//
//post:
// -returns cost of shared path
//
//O(1)
floatWInf journey::sharedCost() const
{
  
  return internalSharedPath.cost();
  
}

//journey::sharedPath()
// returns path of shared path
//
//pre:
// -none
//
//post:
// -returns path of shared path
//
//O(1)
path const & journey::sharedPath() const
{
  
  return internalSharedPath;
  
}

//journey::sharedActualPath()
// returns actual path of shared path
//
//pre:
// -none
//
//post:
// -returns actual path of shared path
//
//O(1)
vector< int > const & journey::sharedActualPath() const
{
  
  return internalSharedPath.actualPath();
  
}

//journey::setSharedPath()
// sets shared path to parameter
//
//pre:
// -newPath is a valid path
//
//post:
// -shared path equals newPath
//
//O(length of newPath)
void journey::setSharedPath(path const & newPath)
{
  
  internalSharedPath.setPath(newPath.actualPath(), newPath.cost());
  
}

//journey::setSharedCost()
// sets shared cost to parameter
//
//pre:
// -newCost is a valid floatWInf
//
//post:
// -shared path's cost equals newCost
//
//O(1)
void journey::setSharedCost(floatWInf const & newCost)
{
  
  internalSharedPath.setCost(newCost);
  
}

//journey::hasSinglePath()
// returns true if journey currently has a single path
//
//pre:
// -none
//
//post:
// -returns true if journey currently has a single path
//          false otherwise
//
//O(1)
bool journey::hasSinglePath() const
{
  
  return !(internalSinglePath.isNull());
  
}

//journey::singleCost()
// returns cost of single path
//
//pre:
// -none
//
//post:
// -returns cost of single path
//
//O(1)
floatWInf journey::singleCost() const
{
  
  return internalSinglePath.cost();
  
}

//journey::singlePath()
// returns path of single path
//
//pre:
// -none
//
//post:
// -returns path of single path
//
//O(1)
path const & journey::singlePath() const
{
  
  return internalSinglePath;
  
}

//journey::singleActualPath()
// returns actual path of single path
//
//pre:
// -none
//
//post:
// -returns actual path of single path
//
//O(1)
vector< int > const & journey::singleActualPath() const
{
  
  return internalSinglePath.actualPath();
  
}

//journey::setSinglePath()
// sets single path to parameter
//
//pre:
// -newPath is a valid path
//
//post:
// -single path equals newPath
//
//O(1)
void journey::setSinglePath(path const & newPath)
{
  
  internalSinglePath.setPath(newPath.actualPath(), newPath.cost());
  
}

int journey::getDestination() const {
    return internalDestination;
}

int journey::getSource() const {
    return internalSource;
}