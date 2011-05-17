#ifndef _VERTEX_H_
#define _VERTEX_H_

//Christopher Earl
//vertex.h
// contains class vertex

#include <vector>

using namespace std;

#include "basicStructures.h"

class vertex
{
  
 private:
  
  floatWInf internalFloat;
  intWInf internalPredecessor;
  vector< intWInf > internalPredecessors;
  
 public:
  
  vertex();
  vertex(vertex const & newVertex);
  vertex(floatWInf cost, intWInf predecessor);
  
  //cost member func's
  ///accessor
  floatWInf cost() const;
  ///mutators
  void setCost(floatWInf newCost);
  
  //predecessor member func's
  ///accessors
  bool hasPredecessor() const;
  intWInf predecessor() const;
  vector< intWInf > predecessors() const;
  intWInf predecessors(int index) const;
  ///mutators
  void setPredecessor(intWInf newPredecessor);
  void setPredecessors(intWInf newPredecessor, bool greater);
  
};

#endif
