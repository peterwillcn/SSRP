//Christopher Earl
//edgeGroup.cpp
// contains edge and edgeGroup member functions

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#include "basicStructures.h"
#include "edge.h"

//edge::edge()
// c'tor
//
//pre:
// -none
//
//post:
// -edge constructed with infinite cost and no journeys
//
//O()
edge::edge()
  :internalCost(), currentNumJourneys(0), journeysThrough()
{
  
}


edge::edge(const edge& other):
internalCost(other.internalCost),
currentNumJourneys(other.currentNumJourneys),
journeysThrough(other.journeysThrough)
{
	
}

//edge::edge()
// c'tor
//
//pre:
// -totalNumJourneys is a valid number of journeys
//
//post:
// -edge constructed with infinite cost and totalNumJourneys
//
//O(numJourneys)
edge::edge(int totalNumJourneys)
  :internalCost(), currentNumJourneys(0)
{
  
  journeysThrough.resize(totalNumJourneys, false);
  
}

//edge::edge()
// c'tor
//
//pre:
// -cost is a valid floatWInf
// -totalNumJourneys is a valid number of journeys
//
//post:
// -edge constructed with cost and totalNumJourneys
//
//O(numJourneys)
edge::edge(floatWInf cost, int totalNumJourneys)
  :internalCost(cost), currentNumJourneys(0)
{
  
  journeysThrough.resize(totalNumJourneys, false);
  
}

//edge::isUsable()
// returns true if edge is able to be traversed
//
//pre:
// -none
//
//post:
// -returns true if edge is able to be traversed
//          false otherwise
//
//O(1)
bool edge::isUsable() const
{
  
  return !(internalCost.isInfinity());
  
}

//edge::totalCost()
// returns total cost of traversing edge
//
//pre:
// -total cost has been set
//
//post:
// -returns total cost of traversing edge
//
//O(1)
floatWInf edge::totalCost() const
{
  
  return internalCost;
  
}

//edge::currentCost()
// returns the cost of traversing edge by given journey
//
//pre:
// -total cost has been set
// -journeyNum is a valid journey number
//
//post:
// returns the cost of traversing edge by given journey
//
//O(1)
floatWInf edge::currentCost(int journeyNum) const
{ 
  floatWInf temp;
  if(internalCost.isInfinity() == true)
    temp.setValue();
  else
    if(journeysThrough[journeyNum] == true)
      temp.setValue(internalCost.value() / currentNumJourneys);
    else
      temp.setValue(internalCost.value() / (currentNumJourneys + 1));
  
  return temp;
  
}

//edge::currentCosts()
// returns cost of traversing edge with all given journeys traversing it
//
//pre:
// -total cost has been set
// -journeyNum is a valid journey number
//
//post:
// -returns cost of trraversing edge with all given journeys traversing it
//
//O(length of journeysNum)
/*
floatWInf edge::currentCosts(vector< int > journeysNum) const
{
  
  floatWInf temp;
  //int tempCount = currentNumJourneys;
  
  if(internalCost.isInfinity() == true)
    temp.setValue();
  else
    {
      //for(int i = 0; i < journeysNum.size(); i++)
	//if(journeysThrough[journeysNum[i]] == false)
	  //tempCount = tempCount + 1;
      
      temp.setValue(internalCost.value() / currentNumJourneys);
    }
  
  return temp;
  
}
*/

//edge::isJourneyIn()
// returns true if journey is currently traversing edge
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -returns true if journey is currently traversing edge
//          false otherwise
//
//O(1)
bool edge::isJourneyIn(int journeyNum) const
{
  
  return journeysThrough[journeyNum];
  
}

//edge::numJourneysUsing()
// returns number of journeys currently traversing edge
//
//pre:
// -total number of journeys is set
//
//post:
// -returns number of journeys currently traversing edge
//
//O(1)
int edge::numJourneysUsing() const
{
  
  return currentNumJourneys;
  
}

//edge::numJourneys()
// returns total number of journeys
//
//pre:
// -total number of journeys is set
//
//post:
// -returns total number of journeys
//
//O(1)
int edge::numJourneys() const
{
  
  return journeysThrough.size();
  
}

//edge::addJourney()
// sets journey to traverse edge
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -given journey set to traverse edge
//
//O(1)
void edge::addJourney(int journeyNum)
{
  
  if(journeysThrough[journeyNum] == false)
    {
      journeysThrough[journeyNum] = true;
      currentNumJourneys++;
    }
  
}

//edge::removeJourney()
// sets journey to not traverse edge
//
//pre:
// -journeyNum is a valid journey number
//
//post:
// -given journey set to not traverse edge
//
//O(1)
void edge::removeJourney(int journeyNum)
{
  
  if(journeysThrough[journeyNum] == true)
    {
      journeysThrough[journeyNum] = false;
      currentNumJourneys--;
    }  
  
}

//edge::removeAllJourneys()
// sets all journeys to not traverse edge
//
//pre:
// -none
//
//post:
// -all journeys set to not traverse edge
//
//O(numJourneys())
void edge::removeAllJourneys()
{
  
  for(int i = 0; i < numJourneys(); i++)
      journeysThrough[i] = false;

  currentNumJourneys = 0;

}

//edge::setTotalCost()
// sets total cost
//
//pre:
// -newCost is a valid floatWInf
//
//post:
// -total cost equals newCost
//
//O(1)
void edge::setTotalCost(floatWInf newCost)
{
  
  internalCost = newCost;
  
}

//edge::setTotalNumJourneys()
// sets total number of journeys
//
//pre:
// -newNumJourneys is a valid int
//
//post:
// -total number of journeys equals newNumJourneys
//
//O(1)
void edge::setTotalNumJourneys(int newNumJourneys)
{
  
  journeysThrough.resize(newNumJourneys);
  
}

