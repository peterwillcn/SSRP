#ifndef _JOURNEY_H_
#define _JOURNEY_H_

//Christopher Earl
//journey.h
// contains class journey

#include <vector>

using namespace std;

#include "basicStructures.h"
#include "path.h"

class journey
{
  
 private:
  
  int internalSource;
  int internalDestination;
  path internalSharedPath;
  path internalSinglePath;
  
 public:
  
  journey();
  journey(int source, int destination);
  
  //journey member func's
  ///accessors
  vector< int > returnSAD() const;
  floatWInf saving() const;
  ///mutators
  void setSAD(int newSource, int newDestination);
  void reset();
  
  //shared path member func's
  ///accessors
  bool hasSharedPath() const;
  floatWInf sharedCost() const;
  path const & sharedPath() const;
  vector< int > const & sharedActualPath() const;
  ///mutator
  void setSharedPath(path const & newPath);
  void setSharedCost(floatWInf const & newCost);
  
  //single path member func's
  ///accessors
  bool hasSinglePath() const;
  floatWInf singleCost() const;
  path const & singlePath() const;
  vector< int > const & singleActualPath() const;
  ///mutator
  void setSinglePath(path const & newPath);
  
};

#endif
