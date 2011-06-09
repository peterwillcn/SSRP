#ifndef _EDGE_H_
#define _EDGE_H_

//Christopher Earl
//edge.h
// contains class edge

#include <vector>

using namespace std;

#include "basicStructures.h"

class edge
{
  
 private:

  floatWInf internalCost;
  int currentNumJourneys;
  vector< bool > journeysThrough;
  
 public:
  
  edge();
  edge(const edge& other);
  edge(int totalNumJourneys);
  edge(floatWInf cost, int totalNumJourneys);
  
  //accessor member func's
  bool isUsable() const;
  floatWInf totalCost() const;
  floatWInf currentCost(int journeyNum) const;
  floatWInf currentCosts(vector< int > journeysNum) const;
  bool isJourneyIn(int journeyNum) const;
  int numJourneysUsing() const;
  int numJourneys() const;

  //mutator member func's
  void addJourney(int journeyNum);
  void removeJourney(int journeyNum);
  void removeAllJourneys();
  void setTotalCost(floatWInf newCost);
  void setTotalNumJourneys(int newNumJourneys);
  
};

#endif
