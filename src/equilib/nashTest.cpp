#include "nashTest.hpp"

bool nashEquilibrium(graphGroup& g, int depth) 
{
    bool result = true;
    
    vector<path> final_paths = g.returnSharedPaths();
    vector<floatWInf> final_costs = g.returnSharedCosts();
    
    for(int j = 0; j < g.numJourneys(); j++) 
    {
        path new_path;
        g.removeJourney(j);
        g.addJourneySP(j);
        floatWInf x = g.returnSharedCost(j);
        if( x >= final_costs[j]) 
        {
            output("journey " + str(j) + " has no incentive to move.");
        }
        else 
        {
            output("journey " + str(j) + " will defect from the final solution.");
            if(depth < nashDepth)
            {
              output("Running test on resultant graph");
              nashEquilibrium(g, depth + 1);
            }
            else
            {
              output("could not find nash equilibrium after " + str(nashDepth) + " attempts.");
            }
            printJourney(g.getJourney(j));
            result = false;
        }
        g.removeJourney(j);
        g.addJourney(j, final_paths[j]);
    }
    
    return result;
}