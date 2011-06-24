#include "STGroup.hpp"

STGroup::STGroup(void):
resultantTree()
{

}

STGroup::~STGroup(void)
{

}

//find a minimum spanning tree using prim's algorithim with a specified start vertex
void STGroup::findMinSpanningTree(const basicEdgeGroup& graph, int startvertex)
{
  //the resultant tree will have v - 1 edges
  this->resultantTree = basicEdgeGroup(graph.returnN());
  this->resultantTree.setUndirected();

  std::vector<int> curVerticies;
  std::vector<bool> inTree(graph.returnN(), false);
  curVerticies.push_back(startvertex);
  inTree[startvertex] = true;
  int edgesAdded = 0;

  //loop until tree is full
  while(edgesAdded < graph.returnN() - 1)
  {
    //set the next potential vertex to 0
    int curInTree = 0;
    int curAdjacentMin = 0;
    floatWInf curMinCost = floatWInf(true, 0);
    
    //check each of the verticies already in the tree
    for(int j = 0; j < curVerticies.size(); ++j)
    {
      int curVertex = curVerticies[j];
      //check all adjacent verticies
      for(int i = 0; i < graph.returnN(); ++i)
      {
        
        //no edge to this vertex
        if(graph.returnEdgeCost(curVertex, i) == 0)
          continue;
        
        //this will always be a 0 edge
        if(i == curVertex)
          continue;
        
        //don't check verticies already added
        if(inTree[i])
          continue;
        
        //if we find a closer edge and not already in the tree plan to add it to the tree
        if(graph.returnEdgeCost(curVertex, i) < curMinCost)
        {
          curInTree = curVertex;
          curAdjacentMin = i;
          curMinCost = floatWInf(false, graph.returnEdgeCost(curInTree, curAdjacentMin).value());
          if(debug)
          {
            std::cout << "New closest vertex from " << curInTree << " to " << curAdjacentMin << " with cost " << curMinCost << std::endl;
          }
        }
      }
    }
    
    //add the closest vertex not in the tree
    this->resultantTree.addEdge(curInTree, curAdjacentMin, curMinCost.value());
    this->resultantTree.addEdge(curAdjacentMin, curInTree, curMinCost.value());
    
    if(debug)
    {
      std::cout << "Added edge from " << curInTree << " to " << curAdjacentMin << " with cost " << curMinCost << std::endl;
    }

    curVerticies.push_back(curAdjacentMin);
    inTree[curAdjacentMin] = true;

    ++edgesAdded;
  }
  
}


const basicEdgeGroup& STGroup::returnMinSpanningTree() const
{
  return this->resultantTree;    
}
