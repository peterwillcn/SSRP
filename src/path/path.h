#ifndef _PATH_H_
#define _PATH_H_

//Christopher Earl
//path.h
// contains class path

#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

#include "basicStructures.h"

class path
{
  
 private:
  
  floatWInf internalCost;
  vector< int > internalActualPath;
  
 public:
  
  path();
  path(const path& newPath);
  path(path const & pathA, path const & pathB); //combines two paths together
  path(vector< int > const & actualPath, floatWInf cost);
  
  //cost accessor member func's
  floatWInf cost() const;
  bool operator>(path const & other) const;
  bool operator>(floatWInf const & constCost) const;
  path operator+(int const & element);
  bool operator==(path const & other) const;
  
  //detailed accessor path member func's
  int returnVertex(int i) const;
  int returnStart() const;
  int returnEnd() const;
  bool isSingleEdge() const;
  bool isNull() const;
  int length() const;
  int getElement(int ref) const;

  //general path member func's
  ///accessor
  vector< int > const & actualPath() const;
  ///mutator
  void setPath(vector< int > const & newPath, floatWInf newCost);
  void setCost(floatWInf newCost);
  
};

#endif
