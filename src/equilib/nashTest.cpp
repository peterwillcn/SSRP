#include "nashTest.hpp"
#include "debug.h"
#include "ioFunctions.h"

/*
    * this function will run until an equilibrium has been found.
    * it is believed, but not known, that an equilibrium will be found for any SSP game from any arbitrary begining strategy profile
*/
bool nashEquilibrium(graphGroup& g, bool pareto) 
{
    bool result = true;
    int count = 0;
    
    vector<path> final_paths = g.returnSharedPaths();
    vector<floatWInf> final_costs = g.returnSharedCosts();
    floatWInf final_social_cost = 0;
    
    for(int q = 0; q < final_costs.size(); ++q)
    {
        final_social_cost += final_costs[q]; 
    }

    if(nash_out)
      output("searching for a nash equilibrium");
 
    
    //loop through all journeys
    int j = 0; 
    while(j < g.numJourneys()) 
    {
        //remove journey from graph
        g.removeJourney(j);
        
        //readd journey on its shortest path considering sharing
        g.addJourneySP(j);
        
        floatWInf next_social_cost = 0;
        
        //check social cost
        for(int q = 0; q < g.returnSharedCosts().size(); ++q)
        {
            next_social_cost += g.returnSharedCosts()[q]; 
        }
        
        //check if the journey has lowered it's cost
        floatWInf x = g.returnSharedCost(j);
        if( x < final_costs[j]) 
        {
            //if looking for pareto optima check if the social cost has increased
            if(pareto)
                if(next_social_cost > final_social_cost)
                    continue;
                
            //journey can make a better deicision, defect to this profile and begin again
            if(nash_out)
            {
              output("journey " + str(j) + " has a better strategy");
              printJourney(g.getJourney(j));
            }
            
            final_paths = g.returnSharedPaths();
            final_costs = g.returnSharedCosts();
            final_social_cost  = 0;
            for(int q = 0; q < final_costs.size(); ++q)
            {
                final_social_cost += final_costs[q]; 
            }

            
            ++count;
            j = 0;
            continue;
        }
        else // move to the next journey
          ++j;
    }

    if(nash_out)
      output("Found an NE after " + str(count) + " deviation(s)");
    
    result = true;
    return result;
}