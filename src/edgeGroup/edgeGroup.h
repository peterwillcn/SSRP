#ifndef _EDGEGROUP_H_
#define _EDGEGROUP_H_

//Christopher Earl
//edgeGroup.h
// contains classes edgeGroup

#include <vector>

using namespace std;

#include "basicStructures.h"
#include "vertex.h"
#include "path.h"
#include "edge.h"
#include "basicEdgeGroup.h"
#include "journeyInfo.h"

class edgeGroup
{
  
 private:
  
  int internalNumJourneys;
  vector< vector< edge > > edges;
  
  //path finder functions:
  path Dijkstra(journeyInfo information) const;
  void findPath(journeyInfo information, vector< vertex > const & vertices, vector< int > & foundPath) const;
  
 public:
  
  edgeGroup();
  edgeGroup(int numVertices, int numJourneys);
  edgeGroup(const edgeGroup& other);
  edgeGroup(basicEdgeGroup const & inputGroup, int numJourneys);
  
  //edge accessors
  bool isEdgeUsable(int i, int j) const;
  bool isSectionUsable(vector< int > section) const;
  floatWInf totalEdgeCost(int i, int j) const;
  floatWInf totalSectionCost(vector< int > section) const;
  floatWInf currentEdgeCost(int i, int j, int journeyNum) const;
  floatWInf currentSectionCost(vector< int > section, int journeyNum) const;
  floatWInf currentEdgeCosts(int i, int j, vector< int > journeysNum) const;
  floatWInf currentSectionCosts(vector< int > section, vector< int > journeysNum) const;
  bool isJourneyIn(int i, int j, int journeyNum) const;
  bool isJourneyInSection(vector< int > section, int journeyNum) const;
  int numJourneysUsing(int i, int j) const;
  
  //group accessors
  path findSP(journeyInfo information) const;
  int returnN() const;
  int numJourneys() const;

  //mutators
  void addJourneySP(journeyInfo information);
  void addJourney(int journeyNum, path const & newPath);
  void removeJourney(int journeyNum);
  void removeAllJourneys();
  void set(basicEdgeGroup const & newGraph, int newNumJourneys);
  void update_edge_cost(int i, int j, floatWInf new_cost);
};

#endif
