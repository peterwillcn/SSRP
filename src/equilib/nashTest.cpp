#include "nashTest.hpp"

bool nashEquilibrium(graphGroup& g, int depth) 
{
    bool result = true;
    
    vector<path> final_paths = g.returnSharedPaths();
    vector<floatWInf> final_costs = g.returnSharedCosts();
    
    std::string spaces;
    if(depth > 0)
    {
      spaces = "  ";
      for(int i = 1; i < depth; ++i)
      {
        spaces += spaces;
      }
    }
    
    output(spaces + "Testing for nash equilibrium at depth " + str(depth));
    
    
    int j = 0; 
    while(j < g.numJourneys() ||
          !result
    ) 
    {
        path new_path;
        g.removeJourney(j);
        g.addJourneySP(j);
        floatWInf x = g.returnSharedCost(j);
        if( x >= final_costs[j]) 
        {
            output(spaces + "journey " + str(j) + " has no incentive to move.");
        }
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
        j++;
    }
    
    return result;
}