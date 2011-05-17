#ifndef _JOURNEYGROUP_H_
#define _JOURNEYGROUP_H_

//Christopher Earl
//journeyGroup.h
// contains class journeyGroup

#include <vector>

using namespace std;

#include "basicStructures.h"
#include "path.h"
#include "journeyInfo.h"
#include "journey.h"

class journeyGroup
{
  
 private:
  
  vector< journey > internalJourneys;

 public:
  
  
  journeyGroup();
  journeyGroup(journeyGroup const & newJourneyGroup);
  journeyGroup(int totalNumJourneys);
  journeyGroup(vector< journeyInfo > const & journeysInformation);
  
  //group accessor member func
  int numJourneys() const;
 

 
  //journey starting info member func's
  ///accessor
  vector< journeyInfo > returnInfos() const;
  journeyInfo returnInfo(int journeyNum) const;
  ///mutators
  void set(vector< journeyInfo > journeysInformation);
  void resetAll();

  //shared member func's
  ///accessors
  bool hasSharedPath(int journeyNum) const;
  floatWInf sharedCost(int journeyNum) const;
  path const & sharedPath(int journeyNum) const;
  vector< int > const & sharedActualPath(int journeyNum) const;
  ///mutators
  void setSharedPath(int journeyNum, path const & newPath);
  void setSharedCost(int journeyNum, floatWInf const & newCost);
  void reset(int journeyNum);
  
  //single member func's
  ///accessors
  bool hasSinglePath(int journeyNum) const;
  floatWInf singleCost(int journeyNum) const;
  path const & singlePath(int journeyNum) const;
  vector< int > const & singleActualPath(int journeyNum) const;
  ///mutators
  void setSinglePath(int journeyNum, path const & newPath);
  void setSAD(journeyInfo newInformation);

  //savings accessor member func
  floatWInf saving(int journeyNum) const;
  
};

#endif
