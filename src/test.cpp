//Christopher Earl
//test.cpp
// contains main() to test various classes
//Version that removed edges from the graph and reroutes

#include <vector>
#include <iostream>
#include <iomanip>
#include <sstream>
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
#include "ioFunctions.h"
#include "FWGroup.h"
#include "STGroup.hpp"
#include "nashTest.hpp"
#include "debug.h"

//returns the index of (the first instance of)"key" in v,
// or -1 if it's not there
template<typename t>
int find_in_vector(const vector<t>& v, t key){
    for(int i = 0; i < v.size(); i++){
        if(v[i] == key)
            return i;
    }
    // if we get here, it's not there
    return -1;
}

const string welcomeHeader =
"\n\
+------------------------------------------------------------------------------+\n\
|                          Shared Shorest Path Project                         |\n\
| Authors: Christopher Earl (2006)                                             |\n\
|          Brooks Emerick (2008)                                               |\n\
|          Sean Quigley (2009)                                                 |\n\
|          Nicole Peterson (2010)                                              |\n\
|          Ronald Fenelus (2011)                                               |\n\
|          Zeal Jagannatha (2011)                                              |\n\
| Mentor:  Sean McCulloch                                                      |\n\
+------------------------------------------------------------------------------+\n";


int main() {

    vector< graphGroup > mainGraphs;
    vector< vector< journeyInfo > > listsOfJourneys;
    vector< basicEdgeGroup > basicGraphs;
    vector< vector< floatWInf > > minSavings;
    vector< vector< floatWInf > > maxSavings;
    vector< vector< floatWInf > > averageSavings;
    string fileName;

    output(welcomeHeader);

    bool printGraphInfo = getChoice("Print graph?");

    bool show_reroutings = getChoice("Print journey reroutings?");

    readGraphs(basicGraphs);
    mainGraphs.resize(basicGraphs.size());
    listsOfJourneys.resize(basicGraphs.size());
    readJourneys(listsOfJourneys[0]);


    //we need the actual journey numbers
    for(int i = 0; i < listsOfJourneys[0].size(); i++)
        listsOfJourneys[0][i].setJourneyNum(i);
    mainGraphs[0].set(basicGraphs[0], listsOfJourneys[0]);
    // mainGraphs[0].printJourneys();

    vector<FWGroup> FloydPaths(mainGraphs.size());

    for(int i = 0; i < basicGraphs.size(); i++) {
        if(i > 0)
            listsOfJourneys[i] = listsOfJourneys[i - 1];

        mainGraphs[i].set(basicGraphs[i], listsOfJourneys[i]);
        vector<int> journeysNum;

        for(int j = 0; j < listsOfJourneys[i].size(); j++)
            journeysNum.push_back(listsOfJourneys[i][j].journeyNum());

        FloydPaths[i].set(journeysNum, mainGraphs[i]);
        // FloydPaths[i].print_cost_grid();
    }

    if(debug)
        output("Running tests...");

    for(int graphNum = 0; graphNum < mainGraphs.size(); graphNum++){
        if(printGraphInfo)
            printGraph(mainGraphs[graphNum]);

        //route each journey by it's FW path
        for(int j = 0; j < listsOfJourneys[graphNum].size(); j++){
            mainGraphs[graphNum].addJourney(listsOfJourneys[graphNum][j].journeyNum(),
                                               FloydPaths[graphNum].returnPath(listsOfJourneys[graphNum][j].source(),
                                                                                  listsOfJourneys[graphNum][j].destination()));
        }

        int num_passes = inputInt("How many times to run through the edges?");
        int journey_threshold =
            inputInt("How many journeys on the edge before we delete the edge?");
        bool coalition_one =
            getChoice("Do you want to change the graph after one coalition edge improves?");
        bool outsider_one =
            getChoice("Do you want to change the graph after one outsider edge improves?");

        for(int cur_pass = 0; cur_pass < num_passes; cur_pass++){

            if(show_reroutings){
                // then show the current journeys paths
                if(debug)
                    output("About to rip some stuff up...");
                for(int cur_printing = 0;
                    cur_printing < mainGraphs[graphNum].numJourneys();
                    cur_printing++)
                    printJourney(mainGraphs[graphNum].getJourney(cur_printing));
            }


            //for each edge...
            for(int j = 0; j < mainGraphs[graphNum].returnN(); j++) {
                for(int k = 0; k < mainGraphs[graphNum].returnN(); k++) {
                    // if edge (j,k) has > 1 journey on it
                    if(mainGraphs[graphNum].numJourneysUsing(j,k) >= journey_threshold ){
                        //then delete the edge- first remove the journeys using it
                        if(debug){
                            output("removing journeys from edge ("
                                   + str(j) + "," + str(k) + ")");
                        }

                        vector<int> journeys_rerouted; // list of journeys we rip up
                        vector<path> saved_paths; // paths of the journeys we rip up
                        vector<floatWInf> saved_costs; // costs of the paths we rip up
                        saved_paths = mainGraphs[graphNum].returnSharedPaths();
                        saved_costs = mainGraphs[graphNum].returnSharedCosts();
                        for(int cur_journey = 0;
                            cur_journey < mainGraphs[graphNum].numJourneys();
                            cur_journey++){
                            if(mainGraphs[graphNum].isJourneyIn(j,k,cur_journey)){ // then rip it up

                                mainGraphs[graphNum].removeJourney(listsOfJourneys[graphNum][cur_journey].journeyNum());
                                journeys_rerouted.push_back(listsOfJourneys[graphNum][cur_journey].journeyNum());
                                if(debug)
                                    output("Ripping up " + str(cur_journey));
                            }
                        }
                        //remove the edge from the graph
                        floatWInf saved_edge_cost = mainGraphs[graphNum].totalEdgeCost(j,k);
                        mainGraphs[graphNum].update_edge_cost(j,k,floatWInf()); //default constructor                                                           /creates infinity

                        //now reroute everyone that was displaced
                        mainGraphs[graphNum].addJourneysSP(journeys_rerouted);
                        bool displaced_improvement = false; // do any dispalced journeys
                        //get better?
                        int displaced_improvement_num = 0;
                        bool outside_improvement = false;    //do any outsiders get better?
                        int outsider_improvement_num = 0;

                        float sad_rat_num = 0;
                        float sad_rat_den = 0;
                        //now see if anyone else wants to move
                        for(int cur_journey = 0; cur_journey < mainGraphs[graphNum].numJourneys();
                            cur_journey++){
                            int my_journey_num = listsOfJourneys[graphNum][cur_journey].journeyNum();
                            if(find_in_vector(journeys_rerouted,
                                              listsOfJourneys[graphNum][cur_journey].journeyNum())
                                == -1){
                                //then it's not there

                                mainGraphs[graphNum].removeJourney(my_journey_num);
                                mainGraphs[graphNum].addJourneySP(my_journey_num);
                                if(mainGraphs[graphNum].returnSharedCost(my_journey_num) < saved_costs[my_journey_num])
                                    // an outsider got better
                                    outsider_improvement_num++;
                            }
                            else{ // then this is a displaced journey
                                if (mainGraphs[graphNum].returnSharedCost(my_journey_num)
                                    < saved_costs[my_journey_num])
                                    // a displaced journey got better
                                    displaced_improvement_num++ ;
                            }
                            floatWInf sad_difference = saved_costs[cur_journey] -
                                mainGraphs[graphNum].returnSharedCost(my_journey_num);
                            if(sad_difference > 0) // cost got better
                                sad_rat_den += sad_difference.value();
                            else  //cost got worse
                                sad_rat_num += -1* sad_difference.value();
                        }  // end loop through all journeys to update the outsiders
                        //and check for improvement

                        //put the edge back
                        mainGraphs[graphNum].update_edge_cost(j,k,saved_edge_cost);
                        if(show_reroutings){
                            // then show the current journeys paths
                            for(int cur_printing = 0; cur_printing < mainGraphs[graphNum].numJourneys(); cur_printing++)
                                printJourney(mainGraphs[graphNum].getJourney(cur_printing));
                        }
                        // did enough displaced journeys improve?
                        if(coalition_one && displaced_improvement_num >0)
                            displaced_improvement = true;
                        if(!coalition_one && displaced_improvement_num > journeys_rerouted.size()/2)
                            displaced_improvement = true;

                        //did enough outsider journeys improve?
                        if(outsider_one && outsider_improvement_num > 0)
                            outside_improvement = true;
                        if(!outsider_one && outsider_improvement_num > (mainGraphs[graphNum].numJourneys() - journeys_rerouted.size())/2)
                            outside_improvement = true;
                        if(displaced_improvement && outside_improvement){
                            // then we keep the new journeys
                            if(debug){
                                output("Keeping the new paths");
                                output("New sad rat : " + str(sad_rat_num*1.0/sad_rat_den));
                                output("New paths:");

                                for(int cur_journey = 0; cur_journey < mainGraphs[graphNum].numJourneys();
                                    cur_journey++)
                                    printJourney(mainGraphs[graphNum].getJourney(listsOfJourneys[graphNum][cur_journey].journeyNum()));
                            }
                        }
                        else{ // put the old paths back
                            if(debug){
                                output("No improvement- replacing old paths");
                            }
                            mainGraphs[graphNum].removeAllJourneys();
                            mainGraphs[graphNum].addJourneys(saved_paths);
                        }
                    } // end "if >1 journey on this edge"
                }
            } // end "for all edges"
        } // end # of passes

        output("After:");
        for(int j = 0; j < mainGraphs[graphNum].numJourneys(); j++)
            printJourney(mainGraphs[graphNum].getJourney(j));

        floatWInf final_total_cost = 0;
        for(int j = 0; j < mainGraphs[graphNum].numJourneys(); j++)
            final_total_cost += mainGraphs[graphNum].returnSharedCost(j);
        output("Final total cost: " + str(final_total_cost));

        // this checks if the final solution is a Nash Equilibrium
        bool nash_equilibrium = nashEquilibrium(mainGraphs[graphNum]);

        dumpGraph(mainGraphs[graphNum]);
        //print spanning tree
        STGroup st;
        st.findMinSpanningTree(mainGraphs[graphNum].returnGraph());
        vector<journeyInfo> jiplaceholder;
        graphGroup spanningTree = graphGroup(st.returnMinSpanningTree(), jiplaceholder);
        dumpGraph(spanningTree);

        output(string("This solution is ")
               + (nash_equilibrium ? "" : "not ")
               + "a Nash Equilibrium.");
    }

    return 0;
}