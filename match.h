#ifndef MATCH_H
#define MATCH_H

//Nikki Peterson
//match.h
// contains class match and functions

#include <iostream>
#include <vector>
using namespace std;

#include "match.h"
#include "graphGroup.h"

class match
{
 private:
         vector< path > paths1;
         vector< path > paths2;
         vector< vector< path > > sharedVertices;
 public:
        //Constructors
        match();
        match(vector< path > const & newPaths1, vector< path > const & newPaths2);
        //constructs new groups and returns them so they can be added to the cumulative 2D vector of groups
        vector< vector< path > > findMatch(int journeyNum1, int journeyNum2);
        //mutators
        void setPaths(int pathsIndicator, vector< path > const & newPath);
        //accessors
        vector< path > returnPaths(int pathsIndicator) const;
        vector< vector< path > > returnSharedVertices() const;
};

path KMP(vector< int > const & text, vector< int > const & pattern);

#endif
