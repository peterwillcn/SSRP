//Christopher Earl
//vertex.cpp
// contains vertex member functions

#include <vector>
#include <iostream>//TAKE OUT TAKE OUT USED FOR TESTING

using namespace std;

#include "basicStructures.h"
#include "vertex.h"

//vertex::vertex()
// c'tor
//
//pre:
// -none
//
//post:
// -vertex constructed to infinity with no predecessor
//
//O(1)
vertex::vertex()
  :internalFloat(), internalPredecessor()
{
     //testestestestestestestestest
     internalPredecessors.resize(0);
     //testestestestestestestestest
}

//vertex::vertex()
// c'tor
//
//pre:
// -newVertex is a valid vertex
//
//post:
// -vertex constructed to newVertex
//
//O(1)
vertex::vertex(vertex const & newVertex)
  :internalFloat(newVertex.cost()), internalPredecessor(newVertex.predecessor())
{
     //testestestestestestestestest
     internalPredecessors.resize(0);
     //testestestestestestestestest
}

//vertex::vertex()
// c'tor
//
//pre:
// -cost is a valid floatWInf
// -predecessor is a valid predecessor number (or infinity for all)
//
//post:
// -vertex constructed to cost with predecessor
//
//O(1)
vertex::vertex(floatWInf cost, intWInf predecessor)
  :internalFloat(cost), internalPredecessor(predecessor)
{
     //testestestestestestestestest
     internalPredecessors.resize(0);
     //testestestestestestestestest
}

//vertex::cost()
// returns the cost of traveling to this
//
//pre:
// -none
//
//post:
// -returns cost of traveling to this
//
//O(1)
floatWInf vertex::cost() const
{
  
  return internalFloat;
  
}

//vertex::setCost()
// sets cost to newCost
//
//pre:
// -newCost is a valid floatWInf
//
//post:
// -cost equals newCost
//
//O(1)
void vertex::setCost(floatWInf newCost)
{
  
  internalFloat = newCost;
  
}

//vertex::hasPredecessor()
// returns true if this has a predecessor
//
//pre:
// -none
//
//post:
// -returns true if this has a predecessor
//          false otherwise
//
//O(1)
bool vertex::hasPredecessor() const
{
  
  return !(internalPredecessor.isInfinity());
  
}

//vertex::predecessor()
// returns predecessor
//
//pre:
// -none
//
//post:
// -returns predecessor
// -if there is no predecessor, returns infinity
//
//O(1)
intWInf vertex::predecessor() const
{
  
  return internalPredecessor;
  
}

//vertex::cost()
// returns the internal predecessor at this index
//
//pre:
// -none
//
//post:
// -returns the internal predecessor at this index
//
//O(1)
intWInf vertex::predecessors(int index) const
{
  return internalPredecessors[index];
}

//vertex::cost()
// returns the list of internal predecessors
//
//pre:
// -none
//
//post:
// -returns the list of internal predecessors
//
//O(1)
vector< intWInf > vertex::predecessors() const
{
  return internalPredecessors;
}

//vertex::setPredecessor()
// sets predecessor to newPredecessor
//
//pre:
// -newPredecessor is a valid intWInf
//                 is infinity if there is no predecessor
//
//post:
// -predecessor equals newPredecessor
//
//O(1)
void vertex::setPredecessor(intWInf newPredecessor)
{
  
  internalPredecessor = newPredecessor;
  
}

//vertex::setPredecessors()
// adds newPredecessor to the vector of predecessors
//
//pre:
// -newPredecessor is a valid intWInf
//                 is infinity if there is no predecessor
//
//post:
// -the newest element in the vector of predecessors equals newPredecessor
//
//O(1)
void vertex::setPredecessors(intWInf newPredecessor, bool greater)
{
     //MIGHT HAVE TO CHANGE THIS WHEN WE ACTUALLY KEEP TRACK OF TIED DIJKSTAR PATHS!!!!!!!!!
     if(internalPredecessors.size()==0)
     {
          //cout << "\n\nsetPredecessors:  internalPredecessors.size()==0!\n\n";
          internalPredecessors.push_back(newPredecessor);
     }
     else if((!greater)&&(!(internalPredecessors[0].isInfinity())))
     {
          //cout << "\n\nsetPredecessors:  the costs are equal & the previous element in internalPredecessors is not infinity!\n\n";
          internalPredecessors.push_back(newPredecessor);
     }
     else
     {
         //cout << "\n\nsetPredecessors: the cost is greater than or the previous element in internalPredecessors is infinity!\n\n";
         int size = internalPredecessors.size();
         internalPredecessors[size-1]=newPredecessor;
     }
}
