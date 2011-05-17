//Christopher Earl
//sHeuristics.cpp
// contains all heuristics for finding shared shortest paths

#include <vector>
#include <iostream>
#include <string>

using namespace std;

#include "basicStructures.h"
#include "path.h"
#include "journeyInfo.h"
#include "graphGroup.h"
#include "sHeuristics.h"

///
///sHeuristicInfo member functions
///

//sHeuristicInfo::sHeuristicInfo()
// c'tor
//
//pre:
// -none
//
//post:
// -sHeuristicInfo constructed
//
sHeuristicInfo::sHeuristicInfo()
{
    
}

//sHeuristicInfo::sHeuristicInfo()
// constructs a sHeuristicInfo using currentPath and currentGraph
//
//pre:
// -currentPath is a valid path on currentGraph
// -currentGraph is a valid graph
//
//post:
// -sHeuristicInfo constructed based on currentPath and currentGraph
//
sHeuristicInfo::sHeuristicInfo(int journeyNum, path const & currentPath, graphGroup const & currentGraph)
{
  
  set(journeyNum, currentPath, currentGraph);
  
}

//sHeuristicInfo::returnPath()
// returns path
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns path
//
path sHeuristicInfo::returnPath() const
{
  
  return internalPath;
  
}

//sHeuristicInfo::C_sE()
// returns cost of single edges
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns cost of single edges
//
floatWInf sHeuristicInfo::C_sE() const
{
  
  return internalC_sE;
  
}

//sHeuristicInfo::N_sE()
// returns number of single edges
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns number of single edges
//
int sHeuristicInfo::N_sE() const
{
  
  return internalN_sE;
  
}

//sHeuristicInfo::C_SE()
// returns cost of shared edges
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns cost of shared edges
//
floatWInf sHeuristicInfo::C_SE() const
{
  
  return internalC_SE;
  
}

//sHeuristicInfo::N_SE()
// returns number of shared edges
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns number of shared edges
//
int sHeuristicInfo::N_SE() const
{
  
  return internalN_SE;
  
}

//sHeuristicInfo::C_AE()
// returns cost of all edges
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns cost of all edges
//
floatWInf sHeuristicInfo::C_AE() const
{
  
  return internalC_AE;
  
}

//sHeuristicInfo::N_AE()
// returns number of all edges
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns number of all edges
//
int sHeuristicInfo::N_AE() const
{
  
  return internalN_AE;
  
}

//sHeuristicInfo::saving()
// returns saving
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns saving
//
floatWInf sHeuristicInfo::saving() const
{
  
  return internalSaving;
  
}

//sHeuristicInfo::aN_U()
// returns the average of the number of journeys using each edge
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns the average of the number of journeys using each edge
//
floatWInf sHeuristicInfo::aN_U() const
{
  
  return internalaN_U;
  
}

//sHeuristicInfo::N_U()
// returns vector of number of journeys using each edge in order of increasing use
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns vector of number of journeys using each edge in order of increasing use
//
vector< int > sHeuristicInfo::N_U() const
{
  
  return internalN_U;
  
}

//sHeuristicInfo::GLeE()
// returns general least expensive edge
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns general least expensive edge
//
floatWInf sHeuristicInfo::GLeE() const
{
  
  return internalGLeE;
  
}

//sHeuristicInfo::GMeE()
// returns general most expensive edge
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns general most expensive edge
//
floatWInf sHeuristicInfo::GMeE() const
{
  
  return internalGMeE;
  
}

//sHeuristicInfo::LeE()
// returns least expensive edge
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns least expensive edge
//
floatWInf sHeuristicInfo::LeE() const
{
  
  return internalLeE;
  
}

//sHeuristicInfo::MeE()
// returns most expensive edge
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns most expensive edge
//
floatWInf sHeuristicInfo::MeE() const
{
  
  return internalMeE;
  
}

//sHeuristicInfo::lC_sE()
// returns true if this has a lower cost of single edges than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower cost of single edges than other does
//          false otherwise
//
bool sHeuristicInfo::lC_sE(sHeuristicInfo const & other) const
{
  
  return internalC_sE < other.C_sE();
  
}

//sHeuristicInfo::lN_sE()
// returns true if this has a lower number of single edges than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower number of single edges than other does
//          false otherwise
//
bool sHeuristicInfo::lN_sE(sHeuristicInfo const & other) const
{
  
  return internalN_sE < other.N_sE();
  
}

//sHeuristicInfo::lC_SE()
// returns true if this has a lower cost of shared edges than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower cost of shared edges than other does
//          false otherwise
//
bool sHeuristicInfo::lC_SE(sHeuristicInfo const & other) const
{
  
  return internalC_SE < other.C_SE();
  
}

//sHeuristicInfo::lN_SE()
// returns true if this has a lower number of shared edges than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower number of shared edges than other does
//          false otherwise
//
bool sHeuristicInfo::lN_SE(sHeuristicInfo const & other) const
{
  
  return internalN_SE < other.N_SE();
  
}

//sHeuristicInfo::lC_AE()
// returns true if this has a lower cost of all edges than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower cost of all edges than other does
//          false otherwise
//
bool sHeuristicInfo::lC_AE(sHeuristicInfo const & other) const
{
  
  return internalC_AE < other.C_AE();
  
}

//sHeuristicInfo::lN_AE()
// returns true if this has a lower number of all edges than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower number of all edges than other does
//          false otherwise
//
bool sHeuristicInfo::lN_AE(sHeuristicInfo const & other) const
{
  
  return internalN_AE < other.N_AE();
  
}

//sHeuristicInfo::lSavings()
// returns true if this has a lower savings than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower savings than other does
//          false otherwise
//
bool sHeuristicInfo::lSavings(sHeuristicInfo const & other) const
{
  
  return internalSaving < other.saving();
  
}

//sHeuristicInfo::laN_U()
// returns true if this has a lower average number of used than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower average number of used than other does
//          false otherwise
//
bool sHeuristicInfo::laN_U(sHeuristicInfo const & other) const
{
  
  return internalaN_U < other.aN_U();
  
}

//sHeuristicInfo::lN_U()
// returns true if this has a lower number of used than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower number of used than other does
//          false otherwise
//
bool sHeuristicInfo::lN_U(sHeuristicInfo const & other) const
{
  
  bool answer = false;
  int edgeCounter = 0;
  int tester = 0;
  
  //determine if current journey is less than chosenJourney 
  if(internalN_U.size() < other.N_U().size())
    edgeCounter = internalN_U.size();
  else
    edgeCounter = other.N_U().size();
  tester = -1;
  //leaves loop when no more to check or there is a difference
  for(int j = 0; j < edgeCounter && tester < 0; j++)
    if(!(internalN_U[internalN_U.size() - 1 - j] == other.N_U()[other.N_U().size() - 1 - j]))
      tester = j;
  if(((tester > -1)                                                                                     //if( ( (there is a difference)
      &&(internalN_U[internalN_U.size() - 1 - tester] < other.N_U()[other.N_U().size() - 1 - tester]))    //and (internalN_U is less than other))
     ||((tester = -1)
	&&(internalN_U.size() < other.N_U().size())))                                                       //or (internalN_U is shorter than other))
    answer = true;
  
  return answer;
  
}

//sHeuristicInfo::lGLeE()
// returns true if this has a lower general least expensive edge than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower general least expensive edge than other does
//          false otherwise
//
bool sHeuristicInfo::lGLeE(sHeuristicInfo const & other) const
{
  
  return internalGLeE < other.GLeE();
  
}

//sHeuristicInfo::lGMeE()
// returns true if this has a lower general most expensive edge than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower general most expensive edge than other does
//          false otherwise
//
bool sHeuristicInfo::lGMeE(sHeuristicInfo const & other) const
{
  
  return internalGMeE < other.GMeE();
  
}

//sHeuristicInfo::lLeE()
// returns true if this has a lower least expensive edge than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower least expensive edge than other does
//          false otherwise
//
bool sHeuristicInfo::lLeE(sHeuristicInfo const & other) const
{
  
  return internalLeE < other.LeE();
  
}

//sHeuristicInfo::lMeE()
// returns true if this has a lower most expensive edge than other does
//
//pre:
// -this has been set to a currentPath and a currentGraph
//
//post:
// -returns true if this has a lower most expensive edge than other does
//          false otherwise
//
bool sHeuristicInfo::lMeE(sHeuristicInfo const & other) const
{
  
  return internalMeE < other.MeE();
  
}

//sHeuristicInfo::set()
// sets this using currentPath and currentGraph
//
//pre:
// -currentPath is a valid path on currentGraph
// -currentGraph is a valid graph
//
//post:
// -this is set based on currentPath and currentGraph
//
void sHeuristicInfo::set(int journeyNum, path const & currentPath, graphGroup const & currentGraph)
{
  
  int vertexCounter = 0;
  int vertexCounter2 = 0;
  bool foundAnother = false;
  int rawN_U = 0;
  
  internalC_sE = 0;
  internalN_sE = 0;
  internalC_SE = 0;
  internalN_SE = 0;
  internalC_AE = 0;
  internalN_AE = 0;
  internalSaving = 0;
  internalaN_U = 0;
  internalN_U.resize(0);
  internalGLeE.setValue();
  internalGMeE = -1;
  internalLeE.setValue();
  internalMeE = -1;
  internalPath.setPath(currentPath.actualPath(), currentPath.cost());
  
  while(vertexCounter < currentPath.length() - 1)
    {
      //add to C_sE, N_sE, C_SE, or N_SE if necessary
      if(currentGraph.numJourneysUsing(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1)) == 0)
	{
	  internalC_sE += currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum);
	  internalN_sE++;
	}
      else
	{
	  internalC_SE += currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum);
	  internalN_SE++;
	}
      
      //add to C_AE and N_AE
      internalC_AE += currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum);
      internalN_AE++;
      
      //add to rawN_U (for aN_U) and N_U
      rawN_U += currentGraph.numJourneysUsing(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1));
      internalN_U.push_back(currentGraph.numJourneysUsing(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1)));
      
      //check if GLeE, GMeE, LeE or MeE need to be updated
      ///if current edge has no paths through it
      if(currentGraph.numJourneysUsing(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1)) == 0)
	{
	  //BLeE and GMeE first
	  ///find if current edge looked at has another journey's path adjacent to it
	  vertexCounter2 = 0;
	  foundAnother = false;
	  while(vertexCounter2 < currentGraph.returnN()
		&& foundAnother == false)
	    {
	      if(((currentGraph.isEdgeUsable(vertexCounter2, currentPath.returnVertex(vertexCounter)) == true)
		  && (currentGraph.numJourneysUsing(vertexCounter2, currentPath.returnVertex(vertexCounter)) > 0))
		 ||((currentGraph.isEdgeUsable(currentPath.returnVertex(vertexCounter + 1), vertexCounter2) == true)
		    && (currentGraph.numJourneysUsing(currentPath.returnVertex(vertexCounter + 1), vertexCounter2) > 0)))
		foundAnother = true;
	      vertexCounter2++;
	    }
	  ///if there is an adjacent path and if current weight is less than GLeE or more than GMeE
	  if((foundAnother == true)
	     &&(currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum) < internalGLeE))
	    internalGLeE = currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum);
	  if((foundAnother == true)
	     &&(currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum) > internalGMeE))
	    internalGMeE = currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum);
	  
	  //LeE and MeE next
	  if(((vertexCounter > 0)
	       &&(currentGraph.isEdgeUsable(currentPath.returnVertex(vertexCounter - 1), currentPath.returnVertex(vertexCounter)) == true)
	       &&(currentGraph.numJourneysUsing(currentPath.returnVertex(vertexCounter - 1), currentPath.returnVertex(vertexCounter)) > 0))
	      ||((vertexCounter < currentPath.length() - 2)
		 &&(currentGraph.isEdgeUsable(currentPath.returnVertex(vertexCounter + 1), currentPath.returnVertex(vertexCounter + 2)) == true)
		 &&(currentGraph.numJourneysUsing(currentPath.returnVertex(vertexCounter + 1), currentPath.returnVertex(vertexCounter + 2)) > 0)))
	    {
	      if(currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum) < internalLeE)
		internalLeE = currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum);
	      if(currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum) > internalMeE)
		internalMeE = currentGraph.currentEdgeCost(currentPath.returnVertex(vertexCounter), currentPath.returnVertex(vertexCounter + 1), journeyNum);
	    }
	}
      
      vertexCounter++;
    }
  
  //find aN_U
  internalaN_U = (float)(rawN_U / (currentPath.length() - 1));
  
  //find saving
  internalSaving = currentGraph.returnSinglePath(journeyNum).cost().value() - currentPath.cost().value();
  
}

///
///general heuristic functions
///

//returnsHeuristicNumber()
// returns the string value of given sHeuristicNumber
//
//pre:
// -method is a valid sHeuristicNumber
//
//post:
// -returns the string value of method
//
string returnsHeuristicNumber(sHeuristicNumber method)
{
  
  string answer;
  
  switch(method){
  case nDumb:
    answer = "nDumb";
    break;
  case nLC_sE:
    answer = "nLC_sE";
    break;
  case nHC_sE:
    answer = "nHC_sE";
    break;
  case nLN_sE:
    answer = "nLN_sE";
    break;
  case nHN_sE:
    answer = "nHN_sE";
    break;
  case nLC_SE:
    answer = "nLC_SE";
    break;
  case nHC_SE:
    answer = "nHC_SE";
    break;
  case nLN_SE:
    answer = "nLN_SE";
    break;
  case nHN_SE:
    answer = "nHN_SE";
    break;
  case nLC_AE:
    answer = "nLC_AE";
    break;
  case nHC_AE:
    answer = "nHC_AE";
    break;
  case nLN_AE:
    answer = "nLN_AE";
    break;
  case nHN_AE:
    answer = "nHN_AE";
    break;
  case nLsavings:
    answer = "nLsavings";
    break;
  case nHsavings:
    answer = "nHsavings";
    break;
  case nLaN_U:
    answer = "nLaN_U";
    break;
  case nHaN_U:
    answer = "nHaN_U";
    break;
  case nLN_U:
    answer = "nLN_U";
    break;
  case nHN_U:
    answer = "nHN_U";
    break;
  case nGLeE:
    answer = "nGLeE";
    break;
  case nGMeE:
    answer = "nGMeE";
    break;
  case nLeE:
    answer = "nLeE";
    break;
  case nMeE:
    answer = "nMeE";
    break;
  default:
    answer = "not valid sHeuristic";
  }
  
  return answer;
  
}

//sscheckPercentSavings()
// single sHeuristic check savings
// Does ten random shifts (or numJourney shifts if numJourneys < 10) min, max and average are of these shifts
//
//pre:
// -graphs is a vector of valid graphGroups
// -journeysInformations is a vector of vectors of valid journeyInfo's for each graph in graphs
// -graphs and journeysInformations both have the same number of elements
// -equalCounter is a vector of int's that has totalsHeuristicNumber elements and is not reset to zero in this function
// -graphFlag is true if graphs should be printed
// -testFlag is true if test information should be printed
//
//post:
// -minSavings[g][h] holds the minimum average savings of all journeys in graph g that sHeuristic h had on a single shift
// -maxSavings[g][h] holds the maximumn average savings of all journeys in graph g that sHeuristic h had on a single shift
// -averageSavings[g][h] holds the average of the average savings of all journeys of all shifts in graph g that sHeuristic h had
//
//I hope you understood the above because I refuse to explain it again.
void sscheckPercentSavings(vector< graphGroup > & graphs, vector< vector< journeyInfo > > const & journeysInformations, vector< int > & equalCounter, bool graphFlag, bool testFlag, vector< vector< floatWInf > > & minSavings, vector< vector< floatWInf > > & maxSavings, vector< vector< floatWInf > > & averageSavings)
{
  
  int numShifts;  //holds number of shifts
  vector< journeyInfo > shiftedJourneysInformation;  //holds shifted list of journeys
  vector< floatWInf > rawTotalSavings;  //holds raw percent totals of savings of a single test
  rawTotalSavings.resize(totalsHeuristicNumber, 0);
  floatWInf testAveragePercentSavings;  //holds percent of savings of a single test of a single sHeurisitic
  int shiftingNumber;  //holds number to shift journeys by
  int randomIndex;  //holds number to find random shiftingNumber
  vector< int > shiftingIndex;  //holds unused shiftingNumbers

  minSavings.resize(graphs.size());
  maxSavings.resize(graphs.size());
  averageSavings.resize(graphs.size());
  
  //run through all graphs
  for(int g = 0; g < graphs.size(); g++)
    {
      //set up need vectors and information
      shiftedJourneysInformation.resize(journeysInformations[g].size());
      minSavings[g].resize(totalsHeuristicNumber);
      maxSavings[g].resize(totalsHeuristicNumber, -1);
      averageSavings[g].resize(totalsHeuristicNumber, 0);
      
      //print current graph
      if(graphFlag == true)
	{
	  cout << "Graph " << g << ":" << endl;
	  graphs[g].printGraph();
	}
      
      //run through 10 or graphs[g].numJourneys() (whichever is lower) tests
      if(10 < graphs[g].numJourneys())
	numShifts = 10;
      else
	numShifts = graphs[g].numJourneys();
      
      for(int i = 0; i < numShifts; i++)
	{
	  //shift journeysInformation
	  if(numShifts < 10)  //do all shifts
	    {
	      for(int j = 0; j < journeysInformations[g].size(); j++)
		{
		  //find number to shift by
		  shiftingNumber = j + i;
		  if(shiftingNumber >= journeysInformations[g].size())
		    shiftingNumber -= journeysInformations[g].size();
		  
		  //copy journeyInfo into correct spot
		  shiftedJourneysInformation[shiftingNumber] = journeysInformations[g][j];
		}
	    }
	  else  //do ten random shifts
	    {
	      //set up shiftingIndex
	      shiftingIndex.resize(journeysInformations[g].size());
	      for(int j = 0; j < journeysInformations[g].size(); j++)
		shiftingIndex[j] = j;
	      
	      for(int j = 0; j < 10; j++)
		{
		  //find number to shift by
		  randomIndex = randomWeight(0, shiftingIndex.size());
		  shiftingNumber = shiftingIndex[randomIndex];
		  shiftingIndex[randomIndex] = shiftingIndex[shiftingIndex.size() - 1];
		  shiftingIndex.resize(shiftingIndex.size() - 1);
		  
		  if(shiftingNumber >= journeysInformations[g].size())
		    shiftingNumber -= journeysInformations[g].size();
		  
		  //copy journeyInfo into correct spot
		  shiftedJourneysInformation[shiftingNumber] = journeysInformations[g][j];
		}
	      
	    }
	  //run test
	  for(int h = 0; h < totalsHeuristicNumber; h++)
	    {
	      //set graph up for Heuristic
	      graphs[g].set(shiftedJourneysInformation);
	      
	      //print savings info
	      if(testFlag == true)
		cout << "*** G: " << g << "  T:" << i << "  sH: " << returnsHeuristicNumber((sHeuristicNumber)(h)) << endl;
	      
	      //run Heuristic
	      genericsHeuristic(graphs[g], (sHeuristicNumber)(h), nDumb, equalCounter[h], false);
	      
	      //print savings info
	      if(testFlag == true)
		graphs[g].printJourneys();
	      
	      //find raw total of savings
	      for(int j = 0; j < graphs[g].numJourneys(); j++)
		  rawTotalSavings[h] += graphs[g].returnSaving(j).value() / graphs[g].returnSingleCost(j).value();  // individual journey savings / total single cost
	    }
	  
	  //find min, max, and raw total savings
	  for(int h = 0; h < totalsHeuristicNumber; h++)
	    {
	      testAveragePercentSavings = (float)(rawTotalSavings[h].value() / graphs[g].numJourneys());  // raw total journey precent savings / number of journeys
	      
	      if(minSavings[g][h] > testAveragePercentSavings)
		minSavings[g][h] = testAveragePercentSavings;

	      if(maxSavings[g][h] < testAveragePercentSavings)
		maxSavings[g][h] = testAveragePercentSavings;

	      averageSavings[g][h] += testAveragePercentSavings;

	      rawTotalSavings[h] = 0;  //reset percentSavings for next test
	    }
	}
      
      //find average savings
      for(int h = 0; h < totalsHeuristicNumber; h++)
	averageSavings[g][h] = (float)(averageSavings[g][h].value() / numShifts);
    }
  
}

////***does not currently use secondary***\\
//genericsHeuristic()
// sets graph based on primary and secondary heuristic methods
//
//pre:
// -graph is a valid graph
// -primary is a valid sHeuristicNumber
// -secondary is a valid sHeuristicNumber
// -equalCounter is an int and is not reset to zero in this function
// -debugFlag is true if debugging information should be printed
//
//post:
// -graph set based on primary and secondary heuristic methods
//
void genericsHeuristic(graphGroup & graph, sHeuristicNumber primary, sHeuristicNumber secondary, int & counter, bool debugFlag)
{
  
  int journeyCounter = 0;
  vector< bool > used;
  used.resize(graph.numJourneys(), false);
  vector< sHeuristicInfo > information;
  int currentJourney = -1;
  information.resize(graph.numJourneys());
  
  while(graph.numJourneys() > journeyCounter)
    {
      for(int i = 0; graph.numJourneys() > i; i++)
	if(used[i] == false)
	  information[i].set(i, graph.findSP(i), graph);
      
      for(int i = 0; graph.numJourneys() > i; i++)
	{
	  if(used[i] == false)
	    {
	      if(currentJourney == -1)
		currentJourney = i;
	      //if i is better than currentJourney based on primary
	      else if((!(primary == nDumb))
		      &&(genericsHeuristicCompare(information[i], information[currentJourney], primary) == true))
		currentJourney = i;
	      //if i is not better and currentJourney is not better than the other (that is, they are equal)
	      else if((!(primary == nDumb))
		       &&(!(genericsHeuristicCompare(information[currentJourney], information[i], primary) == true)))
		counter++;
	    }
	}
      
      //currentJourney has been found now
      //print debugging info if needed
      if(debugFlag == true)
	cout << journeyCounter << " : " << currentJourney << endl;
      graph.addJourney(currentJourney, information[currentJourney].returnPath());
      used[currentJourney] = true;
      journeyCounter++;
      currentJourney = -1;
    }
}

//genericsHeuristicCompare()
// returns true if first is "better" than second based on method
//
//pre:
// -graph is a valid graph
//
//post:
// -returns true if first is "better" than second based on method
//          false otherwise
//
bool genericsHeuristicCompare(sHeuristicInfo const & first, sHeuristicInfo const & second, sHeuristicNumber method)
{
  
  bool answer;
  
  switch(method){
  case nDumb:
    answer = true;
    break;
  case nLC_sE:
    answer = first.lC_sE(second);
    break;
  case nHC_sE:
    answer = second.lC_sE(first);
    break;
  case nLN_sE:
    answer = first.lN_sE(second);
    break;
  case nHN_sE:
    answer = second.lN_sE(first);
    break;
  case nLC_SE:
    answer = first.lC_SE(second);
    break;
  case nHC_SE:
    answer = second.lC_SE(first);
    break;
  case nLN_SE:
    answer = first.lN_SE(second);
    break;
  case nHN_SE:
    answer = second.lN_SE(first);
    break;
  case nLC_AE:
    answer = first.lC_AE(second);
    break;
  case nHC_AE:
    answer = second.lC_AE(first);
    break;
  case nLN_AE:
    answer = first.lN_AE(second);
    break;
  case nHN_AE:
    answer = second.lN_AE(first);
    break;
  case nLsavings:
    answer = first.lSavings(second);
    break;
  case nHsavings:
    answer = second.lSavings(first);
    break;
  case nLaN_U:
    answer = first.laN_U(second);
    break;
  case nHaN_U:
    answer = second.laN_U(first);
    break;
  case nLN_U:
    answer = first.lN_U(second);
    break;
  case nHN_U:
    answer = second.lN_U(first);
    break;
  case nGLeE:
    answer = first.lGLeE(second);
    break;
  case nGMeE:
    answer = second.lGMeE(first);
    break;
  case nLeE:
    answer = first.lLeE(second);
    break;
  case nMeE:
    answer = second.lMeE(first);
    break;
  default:
    answer = false;
  }
  
  return answer;
  
}

//sort()
// sorts intWInfs
//
//pre:
// -start is the beginning of where to sort
// -end is the end of where to sort
// -ToSort is the vector to be sorted
// -workspace is initalized at least as far as end
//
//post:
// -ToSort between start and end is sorted
//
//O( (end - start) * log(end - start) )
void sort(int start, int end, vector< floatWInf > & ToSort, vector< floatWInf > & workspace)
{
  
  int middle;  //used to hold middle of start and end
  
  middle = start + (end - start)/2;
  
  if(start != end)
    {
      if(start + 1 == end)  //if start and end are next to each other
	{
	  if(ToSort[start] > ToSort[end])
	    {
	      workspace[start] = ToSort[end];
	      ToSort[end] = ToSort[start];
	      ToSort[start] = workspace[start];
	    }
	}
      else  //if here, start != end && start + 1 != end
	{
	  sort(start, middle, ToSort, workspace);
	  sort(middle + 1, end, ToSort, workspace);
	  merge(start, middle, end, ToSort, workspace);
	}
    }
  
}

//merge()
// merges two sections into one
//
//pre:
// -start begins sections to merge
// -middle is brake between sections to merge
// -end is end of sections to merge
// -ToSort contains sections to merge
// -workspace is initialized at least to end
//
//post:
// -ToSort between start and end are merged and sorted
//
//O(length of firstSection + length of secondSection)
void merge(int start, int middle, int end, vector< floatWInf > & ToSort, vector< floatWInf > & workspace)
{
  
  int firstSection = start;  //beginning of first sorted section
  int secondSection = middle + 1;  //beginning of second sorted section
  int completed = start;  //beginning of final merge
  int firstSectionEnd = middle;  //end of first sorted section
  int secondSectionEnd = end;  //end of second sorted section
  
  //while still have more to sort in both sections
  while((firstSection <= firstSectionEnd)
	&&(secondSection <= secondSectionEnd))
    {
      if(ToSort[secondSection] > ToSort[firstSection])
	{
	  workspace[completed] = ToSort[firstSection];
	  firstSection++;
	}
      else
	{
	  workspace[completed] = ToSort[secondSection];
	  secondSection++;
	}
      completed++;
    }
  
  //if there is still more in second section
  if(firstSection > firstSectionEnd)
    {
      while(secondSection <= secondSectionEnd)
	{
	  workspace[completed] = ToSort[secondSection];
	  secondSection++;
	  completed++;
	}
    }
  
  //if there is still more in first section
  if(secondSection > secondSectionEnd)
    {
      while(firstSection <= firstSectionEnd)
	{
	  workspace[completed] = ToSort[firstSection];
	  firstSection++;
	  completed++;
	}
    }
  
  //move back to keysToSort
  completed = start;

  while(completed <= end)
    {
      ToSort[completed] = workspace[completed];
      completed++;
    }
  
}

