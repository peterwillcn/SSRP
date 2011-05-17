//Christopher Earl
//test.cpp
// contains main() to test various classes
//Version that removed edges from the graph and reroutes

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

#include "basicStructures.h"
#include "vertex.h"
#include "path.h"
#include "edge.h"
#include "basicEdgeGroup.h"
#include "journeyInfo.h"
#include "journey.h"
#include "journeyGroup.h"
#include "edgeGroup.h"
#include "graphGroup.h"
#include "sHeuristics.h"
#include "ioFunctions.h"
#include "FWGroup.h"

//returns the index of (the first instance of)"key" in v, 
// or -1 if it's not there
int find_in_vector(const vector<int>& v, int key){
  for(int i = 0; i < v.size(); i++){
    if(v[i] == key)
      return i;
  }
  // if we get here, it's not there
  return -1;
}

      
int main()
{

  char usersAnswer;
  int testNumber;
  vector< graphGroup > mainGraphs;
  vector< vector< journeyInfo > > listsOfJourneys;
  vector< basicEdgeGroup > basicGraphs;
  vector< vector< floatWInf > > minSavings;
  vector< vector< floatWInf > > maxSavings;
  vector< vector< floatWInf > > averageSavings;
  vector< int > equalCounter;
  equalCounter.resize(totalsHeuristicNumber, 0);
  bool graphFlag;
  bool testFlag;
  ofstream fout;
  string fileName = "D000.txt";
  
  cout << "What number file (D###.txt) should be used? (do not include zero's) ";
  cin >> testNumber;
  if(testNumber < 10)
      fileName[3] = testNumber + '0';
  else if(testNumber < 100)
    {
      fileName[2] = (testNumber / 10) + '0';
      fileName[3] = (testNumber % 10) + '0';
    }
  else
    {
      fileName[1] = (testNumber / 100) + '0';
      fileName[2] = (testNumber / 10) + '0';
      fileName[3] = (testNumber % 10) + '0';
    }
  
  fout.open(fileName.data(), fstream::app);
  
  cout << "Print graph? ";
  cin >> usersAnswer;
  
  if(usersAnswer == 'y')
    graphFlag = true;
  else
    graphFlag = false;
  
  cout << "Print test information? ";
  cin >> usersAnswer;
  
  if(usersAnswer == 'y')
    testFlag = true;
  else
    testFlag = false;
  

  cout << "Print ALL journey reroutings?";
  bool show_reroutings;
  cin >> usersAnswer;
  if(usersAnswer == 'y')
    show_reroutings = true;
  else
    show_reroutings = false;
      
  readGraphs(basicGraphs);
  mainGraphs.resize(basicGraphs.size());
  listsOfJourneys.resize(basicGraphs.size());
  readJourneys(listsOfJourneys[0]);
  
 
  //we need the actual journey numbers
  for(int i = 0; i < listsOfJourneys[0].size(); i++)
    listsOfJourneys[0][i].setJourneyNum(i);
  mainGraphs[0].set(basicGraphs[0], listsOfJourneys[0]);
  //mainGraphs[0].printJourneys();
  
  vector<FWGroup> FloydPaths(mainGraphs.size());
  
  for(int i = 0; i < basicGraphs.size(); i++)
    {
      if(i > 0)
	{
	  listsOfJourneys[i] = listsOfJourneys[i - 1]; 
	}
     
      mainGraphs[i].set(basicGraphs[i], listsOfJourneys[i]);
      vector<int> journeysNum;
      
      for(int j = 0; j < listsOfJourneys[i].size(); j++){
	
	journeysNum.push_back(listsOfJourneys[i][j].journeyNum());

      }
      FloydPaths[i].set( journeysNum, mainGraphs[i]);
      // FloydPaths[i].print_cost_grid();
    }
  
  cout << "Running tests:" << endl;
  
  for(int i = 0; i < mainGraphs.size(); i++){
    if(graphFlag)
      mainGraphs[i].printGraph();
    
    //route each journey by it's FW path
    for(int j = 0; j < listsOfJourneys[i].size(); j++){
      mainGraphs[i].addJourney(listsOfJourneys[i][j].journeyNum(),
			       FloydPaths[i].returnPath(listsOfJourneys[i][j].source(), listsOfJourneys[i][j].destination()));
    }

    cout << "How many times to run through the edges?";
    int num_passes;
    cin >> num_passes;
    int journey_threshold;
    cout << "How many journeys on the edge before we delete the edge?";
    cin >> journey_threshold;
    cout << "Do you want to change the graph after one coalition edge improves? (as opposed to a majority)";
    bool coalition_one;
    char choice;
    cin >> choice;
    if(choice == 'y' || choice == 'Y')
      coalition_one = true;
    else
      coalition_one = false;
     cout << "Do you want to change the graph after one outsider edge improves? (as opposed to a majority)";
     bool outsider_one;
     cin >> choice;
     if(choice == 'y' || choice == 'Y')
       outsider_one = true;
     else
       outsider_one = false;

    for(int cur_pass = 0; cur_pass < num_passes; cur_pass++){
    
    if(show_reroutings){// then show the current journeys paths
	    cout << "Before ripping up anything" << endl;
	    for(int cur_printing = 0;
		cur_printing < mainGraphs[i].numJourneys(); cur_printing++)
	      mainGraphs[i].printJourney(cur_printing);
    }   
 

    //for each edge...
    for(int j = 0; j < mainGraphs[i].returnN(); j++)
      for(int k = 0; k < mainGraphs[i].returnN(); k++){
	// if edge (j,k) has > 1 journey on it
	if(mainGraphs[i].numJourneysUsing(j,k) >= journey_threshold ){
	  //then delete the edge- first remove the journeys using it
	  if(usersAnswer){
	    cout << "removing journeys from edge (" << j << "," << k << ")" << endl;
	  }
	    
	  vector<int> journeys_rerouted; // list of journeys we rip up
	  vector<path> saved_paths; // paths of the journeys we rip up
	  vector<floatWInf> saved_costs; // costs of the paths we rip up
	  saved_paths = mainGraphs[i].returnSharedPaths();
	  saved_costs = mainGraphs[i].returnSharedCosts();
	  for(int cur_journey = 0; cur_journey < mainGraphs[i].numJourneys();
	      cur_journey++){
	    if(mainGraphs[i].isJourneyIn(j,k,cur_journey)){ // then rip it up
	    				    
	      mainGraphs[i].removeJourney(listsOfJourneys[i][cur_journey].journeyNum());
	      journeys_rerouted.push_back(listsOfJourneys[i][cur_journey].journeyNum());
	      if(usersAnswer){
		  cout << "Ripping up " << cur_journey << endl;
	      }
	    }
	  }
	  //remove the edge from the graph
	  floatWInf saved_edge_cost = mainGraphs[i].totalEdgeCost(j,k);
	  mainGraphs[i].update_edge_cost(j,k,floatWInf()); //default constructor                                                           /creates infinity
	  
	  //now reroute everyone that was displaced
	  mainGraphs[i].addJourneysSP(journeys_rerouted);
	  bool displaced_improvement = false; // do any dispalced journeys
                                              //get better?
	  int displaced_improvement_num = 0;
	  bool outside_improvement = false;    //do any outsiders get better?
	  int outsider_improvement_num = 0;

	  float sad_rat_num = 0;
	  float sad_rat_den = 0;
	  //now see if anyone else wants to move
	  for(int cur_journey = 0; cur_journey < mainGraphs[i].numJourneys();
	      cur_journey++){
	    int my_journey_num = listsOfJourneys[i][cur_journey].journeyNum();
	    if(find_in_vector(journeys_rerouted, listsOfJourneys[i][cur_journey].journeyNum()) == -1){ //then it's not there
	      

	      mainGraphs[i].removeJourney(my_journey_num);
	      mainGraphs[i].addJourneySP(my_journey_num);
	      if(mainGraphs[i].returnSharedCost(my_journey_num) < saved_costs[my_journey_num])
		outsider_improvement_num++;; // an outsider got better

	    }
	    else{ // then this is a displaced journey
	      if(mainGraphs[i].returnSharedCost(my_journey_num) < saved_costs[my_journey_num])
		 displaced_improvement_num++ ; // a displaced journey got better
		 
	    }
	
	    floatWInf sad_difference = saved_costs[cur_journey] - 
	      mainGraphs[i].returnSharedCost(my_journey_num);

	    if(sad_difference > 0) // cost got better
	      sad_rat_den += sad_difference.value();
	    else  //cost got worse
	      sad_rat_num += -1* sad_difference.value();


	  }  // end loop through all journeys to update the outsiders
             //and check for improvement

	  //put the edge back
	  mainGraphs[i].update_edge_cost(j,k,saved_edge_cost);
	  if(show_reroutings){// then show the current journeys paths
	    //cout << "WASSUP!" << endl;(added by previous programmer)
	    for(int cur_printing = 0; 
		cur_printing < mainGraphs[i].numJourneys(); cur_printing++)
	      mainGraphs[i].printJourney(cur_printing);
  
	  }
	
	  // did enough displaced journeys improve?
	  if(coalition_one && displaced_improvement_num >0)
	    displaced_improvement = true;
	  if(!coalition_one && displaced_improvement_num > journeys_rerouted.size()/2)
	    displaced_improvement = true;

	  //did enough outsider journeys improve?
	  if(outsider_one && outsider_improvement_num > 0)
	    outside_improvement = true;
	  if(!outsider_one && outsider_improvement_num > (mainGraphs[i].numJourneys() - journeys_rerouted.size())/2)
	    outside_improvement = true;
	  if(displaced_improvement && outside_improvement){
	    // then we keep the new journeys
	  if(usersAnswer){
	    cout << "Keeping the new paths";
	    cout << "New sad rat : " << sad_rat_num/sad_rat_den << endl;
	    cout << "New paths:" << endl;
	    
	    for(int cur_journey = 0; cur_journey < mainGraphs[i].numJourneys();
		cur_journey++)
	      mainGraphs[i].printJourney(listsOfJourneys[i][cur_journey].journeyNum());
	  }
	  }
	  else{ // put the old paths back
	    if(usersAnswer){
	      cout << "No improvement- replacing old paths" << endl;
	    }
	    mainGraphs[i].removeAllJourneys();
	    mainGraphs[i].addJourneys(saved_paths);
	  }
	}// end "if >1 journey on this edge"
      } // end "for all edges"
    } // end # of passes

    cout << "After:" << endl;
    for(int j = 0; j < mainGraphs[i].numJourneys(); j++)
	  mainGraphs[i].printJourney(j);
	
	floatWInf final_total_cost = 0;
    for(int j = 0; j < mainGraphs[i].numJourneys(); j++)
	   final_total_cost += mainGraphs[i].returnSharedCost(j);
	cout << endl;
    cout << "Final total cost: " << final_total_cost << endl;
    cout << endl;
    
    //************************************************************************//
    //*********************************TEST***********************************//
    //************************************************************************//
    
    cout << "\n************************************************************************\n"
         << "*********************************TEST***********************************\n"
         << "************************************************************************\n\n\n";

    for(int k(0); k<mainGraphs.size(); k++)
      {
	
	int numBacktrackGroups;
	vector< vector< path > > dijkstraGroups;
	vector< vertex > vertices;
	vertices.resize(0);
	dijkstraGroups = mainGraphs[k].groupDijkstras(listsOfJourneys[k]);
        
	if(!dijkstraGroups.empty())
	  {
	    vector< int > optimalGroupIndex, numJourneysVertices;
	    optimalGroupIndex.resize(0);
	    numJourneysVertices.resize(0);
	    
	    
	    
	    if(dijkstraGroups.size()>1)
	      {
		//initializes a vector of the product of journeys and shared vertices to help rank the groups
		for(int i(0); i<dijkstraGroups.size(); i++)
		  numJourneysVertices.push_back(dijkstraGroups[i][0].length()*dijkstraGroups[i][1].length());
		
		for(int i(0); i<numJourneysVertices.size(); i++)
		  {
		    int largest=0;
		    
		    for(int j(1); j<numJourneysVertices.size(); j++)
		      if(numJourneysVertices[largest]<numJourneysVertices[j])
			largest=j;
		    
		    optimalGroupIndex.push_back(largest);
		    numJourneysVertices[largest]=-1;
		  }
		//now i have the indices for dijkstraGroups in order from most lucrative group to try to least lucrative
	      }
	      
	      char again;
	    
	    do{
	      
	      char groupSelection;
	      cout << "\nWould you like the program to choose the most beneficial groups\nto backtrack from? (y/n): ";
	      cin >> groupSelection;
	      
	      if(groupSelection=='y'||groupSelection=='Y')
		{
		  
		  if(dijkstraGroups.size()>1)
		    {
		      //Then we have to pick a group to use
		      //Do this by multiplying #ofJourneys by #ofSharedVertices
		      
		      cout << "\nHow many different overlappings would you like to try? (maximum of " << dijkstraGroups.size() << ") ";
		      cin >> numBacktrackGroups;
		      
		      
		      for(int i(0); i<numBacktrackGroups; i++)
			mainGraphs[k].backtrackPaths(listsOfJourneys[k], dijkstraGroups[optimalGroupIndex[i]], vertices);
		      
		    }
		  else
		    {
		      //use only group
		      mainGraphs[k].backtrackPaths(listsOfJourneys[k], dijkstraGroups[0], vertices);
		    }
		}
	      else
		{
		  char check;
		  int tempJourney;
		  vector< int > journeyOverlap;
		  journeyOverlap.resize(0);
		  
		  cout << "\nWhich journeys would you like to find an overlap for?\n(separate journeys with a space): ";
		  cin.ignore(1000, '\n');
		  check=cin.get();
		  while(check!='\n')
		    {
		      cin.putback(check);
		      cin >> tempJourney;
		      journeyOverlap.push_back(tempJourney);
		      check=cin.get();
		    }
		  //Now I have the journey numbers that I want to look for in dijkstraGroups
		  
		  if(dijkstraGroups.size()>1)
		    {
		      vector< int > backtrackGroupVertices;
		      backtrackGroupVertices.resize(0);

		      for(int i(0); i<dijkstraGroups.size(); i++)
			{
			  bool allJourneysFound=false;
			  int numJourneysFound(0);
			  
			  for(int x(0); x<journeyOverlap.size(); x++)
			    {
			      for(int y(0); y<dijkstraGroups[0][1].length(); y++)
				{
				  //check to see if the journeys requested exist in the group
				  if(journeyOverlap[x]==dijkstraGroups[0][1].returnVertex(y))
				    {
				      numJourneysFound++;
				      break;
				    }
				}
			      
			      if(numJourneysFound==journeyOverlap.size())
				{
				  allJourneysFound=true;
				  break;
				}
			    }
			  
			  if(allJourneysFound)
			    backtrackGroupVertices.push_back(i);
			}
		      
		      if(backtrackGroupVertices.size()>1)
			{ 
			  cout << "\nHow many different overlappings would you like to try? (maximum of " << backtrackGroupVertices.size() << ") ";
			  cin >> numBacktrackGroups;

			  for(int i(0); i<numBacktrackGroups; i++)
			    mainGraphs[k].backtrackPaths(listsOfJourneys[k], dijkstraGroups[backtrackGroupVertices[i]], vertices);
			}
		      else
			mainGraphs[k].backtrackPaths(listsOfJourneys[k], dijkstraGroups[backtrackGroupVertices[0]], vertices);
		    }
		  else
		    {
		      bool allJourneysFound=false;
		      int numJourneysFound(0);
		      
		      for(int i(0); i<journeyOverlap.size(); i++)
			{
			  for(int j(0); j<dijkstraGroups[0][1].length(); j++)
			    {
			      //check to see if the journeys requested exist in the group
			      if(journeyOverlap[i]==dijkstraGroups[0][1].returnVertex(j))
				{
				  numJourneysFound++;
				  break;
				}
			    }
			  
			  if(numJourneysFound==journeyOverlap.size())
			    {
			      allJourneysFound=true;
			      break;
			    }
			}
		      
		      if(allJourneysFound)
			{
			  mainGraphs[k].backtrackPaths(listsOfJourneys[k], dijkstraGroups[0], vertices);
			}
		      else
			cout << "\nA group does not exist with all of the requested journeys!\n";
		    }
		}
		  
		  cout << "\nWould you like to backtrack from other groups? (y/n): ";
		  cin >> again;
		  
		}while(again=='y'||again=='Y');
	    
	  }
      }
	
    cout << "\n************************************************************************\n"
         << "*********************************TEST***********************************\n"
         << "************************************************************************\n\n\n";
    
    //************************************************************************//
    //*********************************TEST***********************************//
    //************************************************************************//
     
     // this checks if the final solution is a Nash Equilibrium
    vector<path> final_paths; 
	vector<floatWInf> final_costs;
	final_paths = mainGraphs[i].returnSharedPaths();
	final_costs = mainGraphs[i].returnSharedCosts();
	bool nash_equilibrium = true;
	
    for(int j = 0; j < mainGraphs[i].numJourneys(); j++){
        path new_path;
        mainGraphs[i].removeJourney(j);
        mainGraphs[i].addJourneySP(j);
        floatWInf x = mainGraphs[i].returnSharedCost(j);
        if( x >= final_costs[j])
            cout << "journey " << j << " has no incentive to move." << endl;
        else{
            cout << "journey " << j << " will defect from the final solution." << endl;
            nash_equilibrium = false;
        }
        mainGraphs[i].removeJourney(j);
        mainGraphs[i].addJourney( j, final_paths[j]);
        
    }
    cout << endl;
    if( nash_equilibrium)
        cout << "This solution is a Nash Equilibruim." <<endl;
    else
        cout << "This solution is not a Nash Equilibrium." <<endl;
    
  
  }

  
  
  fout << endl;
      
  fout.close();
  
  return 0;
  
}
  
