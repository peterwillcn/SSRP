#ifndef _STGROUP_HPP_
#define _STGROUP_HPP_

#include <iostream>
#include <algorithm>

#include "basicEdgeGroup.h"
#include "debug.h"

class STGroup
{
public:
  STGroup(void);
  ~STGroup(void);
  
  void findMinSpanningTree(const basicEdgeGroup& graph, int startvertex);
  
  const basicEdgeGroup& returnMinSpanningTree() const; 
  
protected:
  basicEdgeGroup resultantTree;
  
private:
  
};

#endif
