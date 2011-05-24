#include "STGroup.hpp"

STGroup::STGroup(void):
resultantTree()
{

}

STGroup::~STGroup(void)
{

}

void STGroup::findMinSpanningTree(const basicEdgeGroup& graph)
{
  this->resultantTree = basicEdgeGroup(graph.returnN());

  std::vector<int> curVerticies;
  curVerticies.push_back(0);
  int edgesAdded = 0;

  //loop until tree is full
  while(edgesAdded < graph.returnN() - 1)
  {
    //set the next potential vertex to 0
    int curInTree = 0;
    int curAdjacentMin = 0;
    floatWInf curMinCost = floatWInf(true, 0);
    //check each of the verticies already in the tree
    for(int curVertex = 0; curVertex < curVerticies.size(); ++curVertex)
    {
      //check all adjacent verticies
      for(int i = 0; i < graph.returnN(); ++i)
      {
        //this will always be a 0 edge
        if(i == curVertex)
          continue;
        
        //don't check verticies already added
        if(std::find(curVerticies.begin(), curVerticies.end(), i) != curVerticies.end())
          continue;
        
        //if we find a closer edge that is nonzero and not already in the tree plan to add it to the tree
        if(graph.returnEdgeCost(curVertex, i) < curMinCost &&
           !(graph.returnEdgeCost(curVertex, i) == 0) &&
           resultantTree.returnEdgeCost(curVertex, i) == 0 &&
           resultantTree.returnEdgeCost(i, curVertex) == 0
        )
        {
          curInTree = curVertex;
          curAdjacentMin = i;
          curMinCost = floatWInf(false, graph.returnEdgeCost(curInTree, curAdjacentMin).value());
          std::cout << "New closest vertex from " << curInTree << " to " << curAdjacentMin << " with cost " << curMinCost << std::endl;
        }
      }
    }
    //add the closest vertex not in the tree
    this->resultantTree.addEdge(curInTree, curAdjacentMin, curMinCost.value());
    this->resultantTree.addEdge(curAdjacentMin, curInTree, curMinCost.value());
    
    std::cout << "Added vertex from " << curInTree << " to " << curAdjacentMin << " with cost " << curMinCost << std::endl;

    curVerticies.push_back(curAdjacentMin);

    ++edgesAdded;
  }
}


const basicEdgeGroup& STGroup::returnMinSpanningTree() const
{
  return this->resultantTree;    
}