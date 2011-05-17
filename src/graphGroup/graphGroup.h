#ifndef _GRAPHGROUP_H_
#define _GRAPHGROUP_H_

//Christopher Earl
//graphGroup.h
// contains class graphGroup and reader functions

#include <vector>

using namespace std;

#include "basicStructures.h"
#include "vertex.h"
#include "path.h"
#include "basicEdgeGroup.h"
#include "journeyInfo.h"
#include "journeyGroup.h"
#include "edgeGroup.h"
#include "match.h"

class graphGroup
{
  
 private:
  
  journeyGroup journeys;
  edgeGroup edges;
  basicEdgeGroup graph;
  
  //path finding functions for Dijkstra and reversedDijkstra
  void findPath(int source, int destination, vector< vertex > const & vertices, vector< int > & actualPath, vector< vector< path > > & answers, int const v) const;
  void findReversedPath(int source, int destination, vector< vertex > const & vertices, vector< int > & actualPath, vector< vector< path > > & answers, int const v) const;
  
 public:
        
  
  graphGroup();
  graphGroup(basicEdgeGroup const & inputGroup, vector< journeyInfo > const & journeysInformation);
  
  //printing accessor member func's
  void printGraph() const;
  void printJourneys() const;      //all info on journeys
  void printJourney(int journeyNum) const;      //all info on journeyNum
  void printJourneyPaths() const;  //actual paths
  void printJourneyPath(int journeyNum) const;  //actual paths of journeyNum
  void printJourneyCosts() const;  //shared & single costs && savings
  void printJourneyCost(int journeyNum) const;  //shared & single costs && saving of journeyNum 
  
  //group accessor member func's
  int returnN() const;
  int numJourneys() const;
  basicEdgeGroup returnGraph() const;
  
  //journey-dependent member func's
  
  
  ///edge accessor member func's
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
  vector< vector< path > > Dijkstra(int ii, int journeyNum);
  void dijkstraCost(int ii, int journeyNum, vector< vertex > & vertices);
  vector< vector< path > > groupDijkstras(vector< journeyInfo > & journeysInformation/*, vector< vertex > & vertices*/);
  void backtrackPaths(vector< journeyInfo > & journeysInformation, vector< path > dijkstraGroup, vector< vertex > vertices);
  vector< vector< path > > reversedDijkstra(int jj, int journeyNum) const;
  

  ///shared path accessor member func's
  bool hasSharedPath(int journeyNum) const;
  vector< floatWInf > returnSharedCosts() const;
  floatWInf returnSharedCost(int journeyNum) const;
  vector< path > returnSharedPaths() const;
  path const & returnSharedPath(int journeyNum) const;
  
  ///single path accessor member func's
  bool hasSinglePath(int journeyNum) const;
  vector< floatWInf > returnSingleCosts() const;
  floatWInf returnSingleCost(int journeyNum) const;
  vector< path > returnSinglePaths() const;
  path const & returnSinglePath(int journeyNum) const;
  
  ///savings accessor member func's
  vector< floatWInf > returnSavings() const;
  floatWInf returnSaving(int journeyNum) const;
  
  ///shared path accessor member func's
  path findSP(int journeyNum) const;
  
  ///mutators
  void refindSharedCosts();
  void refindSharedCost(int journeyNum);
  void addJourneysSP(vector< int > journeysNum);
  void addJourneySP(int journeyNum);
  void addJourneys(vector< int > journeysNum, vector< path > const & newPaths);
  void addJourneys(vector<path> const& newPaths);
  void addJourney(int journeyNum, path const & newPath);
  void removeJourney(int journeyNum);
  void removeAllJourneys();
  void set(basicEdgeGroup const & inputGroup, vector< journeyInfo > const & journeysInformation);
  void set(vector< journeyInfo > const & journeysInformation);
  void update_journeys(vector<journeyInfo> const& listOfJourneys, 
		       vector<int> const& changed_journey_numbers);
  void update_edge_cost(int i, int j, floatWInf new_cost);
  ///pseudo-accessor (almost const)
  vector< path > tryJourneys(vector< int > journeysNum);  //const but not (things are changed but are changed back)
  
};

//Catalysts to the groupDijkstras function
void checkOverlap(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, path & subset, int ngIndex);
void originalGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex);
void repeatedGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex, int gIndex);
void subsetGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex, int gIndex);
void intersectionGroup(vector< vector< path > > & groupings, vector< vector< path > > & newGroupings, int ngIndex, int gIndex);

#endif
