#include "nashTest.hpp"
#include "debug.h"
#include "ioFunctions.h"
#include "options.h"

/*
    * this function will run until an equilibrium has been found.
    * it is believed, but not known, that an equilibrium will be found for any SSP game from any arbitrary begining strategy profile
    * UPDATE: It is now known that this function will always find an equilibrium
*/
void nashEquilibrium(graphGroup& g) 
{
    unsigned int count = 0;
    
    graphGroup testGroup;
    
    vector<path> final_paths = g.returnSharedPaths();
    vector<floatWInf> final_costs = g.returnSharedCosts();
    floatWInf final_social_cost = g.totalSharedCost();

    if(nash_out)
      output("searching for a nash equilibrium");
 
    
    //loop through all journeys
    unsigned int j = 0;
    floatWInf bestImprove = 0;
    int bestJourney = -1;
    bool noImprove = false;
    
    //defect journeys until none can improve
    while(!noImprove)
    {
        j = 0;
        bestJourney = -1;
        bestImprove = 0;
        
        //find best journey to defect
        while(j < g.numJourneys()) 
        {
            
            testGroup = g;
            //remove journey from graph
            testGroup.removeJourney(j);
            
            //readd journey on its shortest path considering sharing
            testGroup.addJourneySP(j);
            
            floatWInf next_social_cost = 0;
            
            //check social cost
            next_social_cost = testGroup.totalSharedCost(); 
                
            //check if the journey has lowered it's cost
            floatWInf newCost = testGroup.returnSharedCost(j);
            if(newCost < final_costs[j]) 
            {
                //if looking for pareto optima check if the social cost has increased
                if(usePareto)
                {
                    if(next_social_cost > final_social_cost)
                    {
                        ++j;
                        continue;
                    }
                }
                    
                //journey can make a better deicision, defect to this profile and begin again
                if(nash_out)
                {
                    output("journey " + str(j) + " has a better strategy");
                    printJourney(g.getJourney(j));
                }
               
               
                //if we find a better deviation choose it for now
                if(final_costs[j] - newCost > bestImprove)
                {
                   bestImprove = final_costs[j] - newCost;
                   bestJourney = j;
                }
                
            }
            
            ++j;
        }
        
        //someone improved
        if(bestJourney != -1)
        {    
            //actually defect journey
            g.removeJourney(bestJourney);
            g.addJourneySP(bestJourney);
            
            if(nash_out)
            {
                output("journey " + str(bestJourney) + " has the best improvement");
                printJourney(g.getJourney(bestJourney));
            }
            
            final_paths = g.returnSharedPaths();
            final_costs = g.returnSharedCosts();
            final_social_cost  = 0;
            final_social_cost += g.totalSharedCost(); 
            
            ++count;
        }
        else
        {
            noImprove = true;
        }
        
    }

    if(nash_out)
      output("Found an NE after " + str(count) + " deviation(s)");
}
