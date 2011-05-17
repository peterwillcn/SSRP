#ifndef _SHEURISTICS_H_
#define _SHEURISTICS_H_

//Christopher Earl
//sHeuristics.h
// contains sHeuristicInfo and all heuristic functions for finding shared shortest paths

#include <vector>
#include <string>

using namespace std;

#include "basicStructures.h"
#include "path.h"
#include "journeyInfo.h"
#include "graphGroup.h"

//Naming conventions:
///L = lowest/least
///H = highest
///M = most
///C = cost
///E = edges
///s = single
///S = shared
///P = path
///_ = of
///N = number
///T = total
///a = average
///U = use/used (by others)
///e = expensive
///G = general
///l = lower
///n = enum symbol

enum sHeuristicNumber { nDumb, nLC_sE, nHC_sE, nLN_sE, nHN_sE, nLC_SE, nHC_SE, nLN_SE, nHN_SE, nLC_AE, nHC_AE, nLN_AE, nHN_AE, nLsavings, nHsavings, nLaN_U, nHaN_U, nLN_U, nHN_U, nGLeE, nGMeE, nLeE, nMeE };

const int totalsHeuristicNumber = 23;

string returnsHeuristicNumber(sHeuristicNumber method);

class sHeuristicInfo
{
  
 private:
  
  path internalPath;
  floatWInf internalC_sE;
  int internalN_sE;
  floatWInf internalC_SE;
  int internalN_SE;
  floatWInf internalC_AE;
  int internalN_AE;
  floatWInf internalSaving;
  floatWInf internalaN_U;
  vector< int > internalN_U;
  floatWInf internalGLeE;
  floatWInf internalGMeE;
  floatWInf internalLeE;
  floatWInf internalMeE;
  
 public:
  
  sHeuristicInfo();
  sHeuristicInfo(int journeyNum, path const & currentPath, graphGroup const & currentGraph);
  
  //accessor member functions
  path returnPath() const;
  floatWInf C_sE() const;
  int N_sE() const;
  floatWInf C_SE() const;
  int N_SE() const;
  floatWInf C_AE() const;
  int N_AE() const;
  floatWInf saving() const;
  floatWInf aN_U() const;
  vector< int > N_U() const;
  floatWInf GLeE() const;
  floatWInf GMeE() const;
  floatWInf LeE() const;
  floatWInf MeE() const;
  
  //comparing member functions
  bool lC_sE(sHeuristicInfo const & other) const;
  bool lN_sE(sHeuristicInfo const & other) const;
  bool lC_SE(sHeuristicInfo const & other) const;
  bool lN_SE(sHeuristicInfo const & other) const;
  bool lC_AE(sHeuristicInfo const & other) const;
  bool lN_AE(sHeuristicInfo const & other) const;
  bool lSavings(sHeuristicInfo const & other) const;
  bool laN_U(sHeuristicInfo const & other) const;
  bool lN_U(sHeuristicInfo const & other) const;
  bool lGLeE(sHeuristicInfo const & other) const;
  bool lGMeE(sHeuristicInfo const & other) const;
  bool lLeE(sHeuristicInfo const & other) const;
  bool lMeE(sHeuristicInfo const & other) const;
  
  //mutator member functions
  void set(int journeyNum, path const & currentPath, graphGroup const & currentGraph);
  
};

void sscheckPercentSavings(vector< graphGroup > & graphs, vector< vector< journeyInfo > > const & journeysInformations, vector< int > & equalCounter, bool graphFlag, bool testFlag, vector< vector< floatWInf > > & minSavings, vector< vector< floatWInf > > & maxSavings, vector< vector< floatWInf > > & averageSavings);
void genericsHeuristic(graphGroup & graph, sHeuristicNumber primary, sHeuristicNumber secondary, int & counter, bool debugFlag);
bool genericsHeuristicCompare(sHeuristicInfo const & first, sHeuristicInfo const & second, sHeuristicNumber method);

void sort(int start, int end, vector< floatWInf > & ToSort, vector< floatWInf > & workspace);
void merge(int start, int middle, int end, vector< floatWInf > & ToSort, vector< floatWInf > & workspace);

#endif
