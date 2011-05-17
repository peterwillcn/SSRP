#ifndef _BASICEDGEGROUP_H_
#define _BASICEDGEGROUP_H_

//Christopher Earl
//basicEdgeGroup.h
// contains classs basicEdgeGroup

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#include "basicStructures.h"

class basicEdgeGroup
{
  
 private:
  
  int type;
  int style;
  vector< vector< floatWInf > > group;
  
 public:
  
  basicEdgeGroup();
  basicEdgeGroup(basicEdgeGroup const & newGroup);
  basicEdgeGroup(int numVertices);
  basicEdgeGroup(int numVertices, int type, int style);
  
  //group member func's
  ///accessors
  int returnN() const;
  int returnType() const;
  int returnStyle() const;
  floatWInf returnEdgeCost(int i, int j) const;
  void reverse(basicEdgeGroup & reversee) const;
  ///mutators
  void setN(int newN);
  void setType(int newType);
  void setStyle(int newStyle);
  
  //basicEdge member func's
  ///accessor
  floatWInf cost(int i, int j) const;
  ///mutator
  void addEdge(int i, int j, floatWInf weight);
  
};

#endif
