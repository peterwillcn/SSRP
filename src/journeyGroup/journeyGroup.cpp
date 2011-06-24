//Christopher Earl
//journeys.cpp
// contains journeyGroup member functions

#include <vector>

using namespace std;

#include "basicStructures.h"
#include "path.h"
#include "journeyInfo.h"
#include "journey.h"
#include "journeyGroup.h"

//journeyGroup::journeyGroup()
// c'tor
//
//pre:
// -none
//
//post:
// -journeyGroup constructed without values
//
//O(1)
journeyGroup::journeyGroup()
  :internalJourneys()
{
  
}

//journeyGroup::journeyGroup()
// c'tor
//
//pre:
// -newJourneyGroup is a valid journeyGroup
//
//post:
// -journeyGroup constructed with newJourneyGroup's values
//
//O(numJourneys() * log(numJourneys()))
journeyGroup::journeyGroup(journeyGroup const & newJourneyGroup)
{
  
  //set journey info
  set(newJourneyGroup.returnInfos());
  
  //set single and (possibly) shared paths
  for(int i = 0; i < numJourneys(); i++)
    {
      if(newJourneyGroup.hasSinglePath(i))
	{
	  setSinglePath(i, newJourneyGroup.singlePath(i));
	  if(newJourneyGroup.hasSharedPath(i))
	    setSharedPath(i, newJourneyGroup.sharedPath(i));
	}
    }
  
}

//journeyGroup::journeyGroup()
// c'tor
//
//pre:
// -numJourneys is a valid number of journeys
//
//post:
// -journeyGroup constructed with number of journeys and without other values
//
//O(numJourneys())
journeyGroup::journeyGroup(int totalNumJourneys)
{
  
  internalJourneys.resize(totalNumJourneys);
  
}

//journeyGroup::journeyGroup()
// c'tor
//
//pre:
// -journeysInformation is a vector of all journeyInfo's in graph
//
//post:
// -journeyGroup constructed from journeysInformation
//
//O(numJourneys())
journeyGroup::journeyGroup(vector< journeyInfo > const & journeysInformation)
{
   
  internalJourneys.resize(journeysInformation.size());
  
  for(int i = 0; i < numJourneys(); i++)
    internalJourneys[i] = journey(journeysInformation[i].source(), journeysInformation[i].destination());
  
}

//journeyGroup::numJourneys()
// returns number of journeys
//
//pre:
// -none
//
//post:
// -returns number of journeys
//
//O(1)
int journeyGroup::numJourneys() const
{
  
  return internalJourneys.size();
  
}

//journeyGroup::returnInfos()
// returns all journeys information
//
//pre:
// -journeyGroup has been set
//
//post:
// -returns all journeys information
//
//O(numJourneys())
vector< journeyInfo > journeyGroup::returnInfos() const
{
  vector< journeyInfo > answers(numJourneys());
  
  for(int i = 0; i < numJourneys(); i++)
    answers[i] = returnInfo(i);

  return answers;
  
}

//journeyGroup::returnInfo()
// returns journey information
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns journey information
//
//O(1)
journeyInfo journeyGroup::returnInfo(int journeyNum) const
{
  
  return journeyInfo(journeyNum, internalJourneys[journeyNum].returnSAD()[0], internalJourneys[journeyNum].returnSAD()[1]);
  
}

//journeyGroup::set()
// sets the number of journeys and the sources and destinations for all of them
//
//pre:
// -journeysInformations has all the journeys information
//
//post:
// -the number of journeys has been set as have the sources and destinations for all of them
//
//O(numJourneys() * log(numJourneys()))
void journeyGroup::set(vector< journeyInfo > journeysInformation)
{
  
  internalJourneys.resize(journeysInformation.size());

  for(int i = 0; i < numJourneys(); i++)
    internalJourneys[i].setSAD(journeysInformation[i].source(), journeysInformation[i].destination());
  
}

//journeyGroup::resetAll()
// resets the shared paths of all the journeys
//
//pre:
// -none
//
//post:
// -all the journeys have no shared paths
//
//O(numJourneys())
void journeyGroup::resetAll()
{
  
  for(int i = 0; i < numJourneys(); i++)
    reset(i);
  
}

//journeyGroup::hasSharedPath()
// returns true if given journey has a shared path
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns true if given journey has a shared path
//
//O(1)
bool journeyGroup::hasSharedPath(int journeyNum) const
{
  
  return internalJourneys[journeyNum].hasSharedPath();
  
}

//journeyGroup::sharedCost()
// returns cost of shared path of given journey
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns cost of shared path of given journey
//
//O(1)
floatWInf journeyGroup::sharedCost(int journeyNum) const
{
  
  return internalJourneys[journeyNum].sharedCost();
  
}

//journeyGroup::sharedPath()
// returns shared path of given journey
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns shared path of given journey
//
//O(1)
path const & journeyGroup::sharedPath(int journeyNum) const
{
  
  return internalJourneys[journeyNum].sharedPath();
  
}

//journeyGroup::sharedActualPath()
// returns actual shared path of given journey
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns actual shared path of given journey
//
//O(1)
vector< int > const & journeyGroup::sharedActualPath(int journeyNum) const
{
  
  return internalJourneys[journeyNum].sharedActualPath();
  
}

//journeyGroup::setSharedPath()
// sets given journey's shared path to newPath
//
//pre:
// -journeyNum is a valid journey number
// -newPath is a valid path
//
//post:
// -journeyNum's shared path equals newPath
//
//O(length of newPath)
void journeyGroup::setSharedPath(int journeyNum, path const & newPath)
{
  
  internalJourneys[journeyNum].setSharedPath(newPath);
  
}

//journeyGroup::setSharedCost()
// sets given journey's shared cost to newCost
//
//pre:
// -journeyNum is a valid journey number
// -newCost is a valid floatWInf
//
//post:
// -journeyNum's shared cost equals newCost
//
//O(1)
void journeyGroup::setSharedCost(int journeyNum, floatWInf const & newCost)
{
  
  internalJourneys[journeyNum].setSharedCost(newCost);
  
}

//journeyGroup::reset()
// resets given journey's shared path
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -journeyNum's shared journey is gone
//
//O(1)
void journeyGroup::reset(int journeyNum)
{
  
  internalJourneys[journeyNum].reset();
  
}

int journeyGroup::getSource(int journeyNum) const {
    return internalJourneys[journeyNum].getSource();
}

int journeyGroup::getDestination(int journeyNum) const {
    return internalJourneys[journeyNum].getDestination();
}

//journeyGroup::hasSinglePath()
// returns true if given journey has a single path
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns true if given journey has a single path
//
//O(1)
bool journeyGroup::hasSinglePath(int journeyNum) const
{
  
  return internalJourneys[journeyNum].hasSinglePath();
  
}

//journeyGroup::singleCost()
// returns cost of single path of given journey
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns cost of single path of given journey
//
//O(1)
floatWInf journeyGroup::singleCost(int journeyNum) const
{
  
  return internalJourneys[journeyNum].singleCost();
  
}

//journeyGroup::singlePath()
// returns single path of given journey
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns single path of given journey
//
//O(1)
path const & journeyGroup::singlePath(int journeyNum) const
{
  
  return internalJourneys[journeyNum].singlePath();
  
}

//journeyGroup::singleActualPath()
// returns actual single path of given journey
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns actual single path of given journey
//
//O(1)
vector< int > const & journeyGroup::singleActualPath(int journeyNum) const
{
  
  return internalJourneys[journeyNum].singleActualPath();
  
}

//journeyGroup::setSinglePath()
// sets given journey's single path to newPath
//
//pre:
// -journeyNum is a valid journey number
// -newPath is a valid path
//
//post:
// -journeyNum's single path equals newPath
//
//O(length of newPath)
void journeyGroup::setSinglePath(int journeyNum, path const & newPath)
{
  
  internalJourneys[journeyNum].setSinglePath(newPath);
  
}

//journeyGroup::setSAD()
// sets given journey's source, destination and resets single path
//
//pre:
// -newInformation is a valid journeyInfo
//
//post:
// -journeyNum's shared and single paths are gone, and source and destination are set
//
//O(1)
void journeyGroup::setSAD(journeyInfo newInformation)
{
  
  internalJourneys[newInformation.journeyNum()].setSAD(newInformation.source(), newInformation.destination());
  
}

const journey& journeyGroup::operator[](const int i) const {
    return internalJourneys[i];
}

//journeyGroup::saving()
// returns the savings of given journey
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns the savings of journeyNum
//
//O(1)
floatWInf journeyGroup::saving(int journeyNum) const
{
  
  return internalJourneys[journeyNum].saving();
  
}
