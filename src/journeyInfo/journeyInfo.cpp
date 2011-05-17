//Christopher Earl
//journeyInfo.cpp
// contains journeyInfo member functions

#include <vector>

using namespace std;

#include "journeyInfo.h"

//journeyInfo::journeyInfo()
// c'tor
//
//pre:
// -none
//
//post:
// -journeyInfo constructed without any values
//
//O(1)
journeyInfo::journeyInfo()
  :internalJourneyNum(), internalSource(), internalDestination()
{
  
}

//journeyInfo::journeyInfo()
// c'tor
//
//pre:
// -journeyNum is a valid journey number
// -source is a valid vertex number
// -destination is a valid vertex number
//
//post:
// -journeyInfo constructed with journeyNum, source, and destination
//
//O(1)
journeyInfo::journeyInfo(int journeyNum, int source, int destination)
  :internalJourneyNum(journeyNum), internalSource(source), internalDestination(destination)
{
  
}

//journeyInfo::journeyNum()
// returns journeyNum
//
//pre:
// -journeyNum has been set
//
//post:
// -returns journeyNum
//
//O(1)
int journeyInfo::journeyNum() const
{
  
  return internalJourneyNum;
  
}

//journeyInfo::source()
// returns source
//
//pre:
// -source has been set
//
//post:
// -returns source
//
//O(1)
int journeyInfo::source() const
{
  
  return internalSource;
  
}

//journeyInfo::destination()
// returns destination
//
//pre:
// -destination has been set
//
//post:
// -returns destination
//
//O(1)
int journeyInfo::destination() const
{
  
  return internalDestination;
  
}

//journeyInfo::setJourneyNum()
// sets journeyNum
//
//pre:
// -newJourneyNum is a valid journey number
//
//post:
// -journeyNum equals newJourneyNum
//
//O(1)
void journeyInfo::setJourneyNum(int newJourneyNum)
{
  
  internalJourneyNum = newJourneyNum;
  
}

//journeyInfo::setSource()
// sets source
//
//pre:
// -newSource is a valid vertex number
//
//post:
// -source equals newSource
//
//O(1)
void journeyInfo::setSource(int newSource)
{
  
  internalSource = newSource;
  
}

//journeyInfo::setDestination()
// sets destination
//
//pre:
// -newDestination is a valid vertex number
//
//post:
// -destination equals newDestination
//
//O(1)
void journeyInfo::setDestination(int newDestination)
{
  
  internalDestination = newDestination;
  
}

