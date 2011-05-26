#include "nashTest.hpp"

bool nashEquilibrium(graphGroup& g) 
{
    bool result = true;
    
    vector<path> final_paths = g.returnSharedPaths();
    vector<floatWInf> final_costs = g.returnSharedCosts();
    
    //loop through each journey
    //if a journey can improve start back at journey 0
    //if all journeys can not improve an equilibrium has been found
    
    
    int j = 0; 
    while(j < g.numJourneys()) 
    {
        path new_path;
        g.removeJourney(j);
        g.addJourneySP(j);
        floatWInf x = g.returnSharedCost(j);
        if( x < final_costs[j]) 
        {
            final_costs[j] = x;
            output("journey " + str(j) + " has a better strategy");
            j = 0;
            //output(spaces + "journey " + str(j) + " has no incentive to move.");
        }
        
        j++;
        
        /*
        else 
        {
            result = false;
            output(spaces + "journey " + str(j) + " will defect from the final solution.");
            if(depth < nashDepth)
            {
              output(spaces + "Running test on resultant graph");
              result = nashEquilibrium(g, depth + 1);
            }
            else
            {
              output(spaces + "could not find nash equilibrium after " + str(nashDepth) + " attempts.");
            }
            printJourney(g.getJourney(j));
        }
        
        
        g.removeJourney(j);
        g.addJourney(j, final_paths[j]);
        */
    }
    
    result = true;
    return result;
}