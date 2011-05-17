#ifndef _JOURNEYINFO_H_
#define _JOURNEYINFO_H_

//Christopher Earl
//journeyInfo.h
// contains class journeyInfo

#include <vector>

using namespace std;

class journeyInfo
{
  
 private:
  
  int internalJourneyNum;
  int internalSource;
  int internalDestination;
  
 public:
  
  journeyInfo();
  journeyInfo(int journeyNum, int source, int destination);
  
  //accessors
  int journeyNum() const;
  int source() const;
  int destination() const;
  
  //mutators
  void setJourneyNum(int newJourneyNum);
  void setSource(int newSource);
  void setDestination(int newDestination);
  
};

#endif
