#ifndef _FWGROUP_H_
#define _FWGROUP_H_

//Christopher Earl
//FWGroup.h
// contains class FWGroup

#include <vector>

using namespace std;

#include "basicStructures.h"
#include "vertex.h"
#include "path.h"
#include "graphGroup.h"

class FWGroup
{
  
 private:
  
  int numJ;
  vector< vector< path > > sections;
  
  //FloydWarshall()
  void FloydWarshall(vector< int > journeysNum, graphGroup const & graph);
  //findPaths() part of FloydWarshall()
  void findPath(int start, int end, vector< vector< vertex > > const & vertices, vector< int > & foundPath);
  
 public:
  
  FWGroup();
  
  //path accessor member func's
  path const & returnPath(int i, int j) const;
  floatWInf cost(int i, int j) const;
  
  //printing accessor function
  void print_cost_grid() const;
  
  //group member func's
  int numJourneys() const;
  int returnN() const;
  ///mutators
  void set(vector< int > journeysNum, graphGroup const & graph);


  
};

#endif
