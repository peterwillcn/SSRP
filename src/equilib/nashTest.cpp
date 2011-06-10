#include "nashTest.hpp"
#include "debug.h"

/*
    * this function will run until an equilibrium has been found.
    * it is believed, but not known, that an equilibrium will be found for any SSP game from any arbitrary begining strategy profile
*/
bool nashEquilibrium(graphGroup& g) 
{
    bool result = true;
    
    vector<path> final_paths = g.returnSharedPaths();
    vector<floatWInf> final_costs = g.returnSharedCosts();

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
        
        //check if the journey has lowered it's cost
        floatWInf x = g.returnSharedCost(j);
        if( x < final_costs[j]) 
        {
            //journey can make a better deicision, defect to this profile and begin again
            if(nash_out)
            {
              output("journey " + str(j) + " has a better strategy");
              printJourney(g.getJourney(j));
            }
            final_paths = g.returnSharedPaths();
            final_costs = g.returnSharedCosts();
            j = 0;
            continue;
        }
        else // move to the next journey
          ++j;
    }

    if(nash_out)
      output("This solution is a nash equilibrium");
    
    result = true;
    return result;
}