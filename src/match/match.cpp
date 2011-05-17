//Nikki Peterson
//match.cpp
//contains match member functions

#include <vector>
#include <iostream>

using namespace std;

#include "path.h"
#include "match.h"

//match::match()
// c'tor
//
//pre:
// -none
//
//post:
// -match members constructed to empty paths
//
//O(1)
match::match()
  :paths1(), paths2()
{
     sharedVertices.resize(0);
}

//match::match(vector< path > const & newPaths1, vector< path > const & newPaths2)
// c'tor
//
//pre:
// -none
//
//post:
// -match members constructed to new paths respectively
//
//O(1)
match::match(vector< path > const & newPaths1, vector< path > const & newPaths2)
{
     for(int i(0); i<newPaths1.size(); i++)
          paths1.push_back(newPaths1[i]);
     for(int i(0); i<newPaths2.size(); i++)
          paths2.push_back(newPaths2[i]);
     sharedVertices.resize(0);
}

//match::findMatch()
// member function
//
//pre:
// -path1 and path2 have been intialized/set
//
//post:
// -returns a 2D vector of groups representing different matches among two dijkstra paths (text & pattern)
//
vector< vector< path > > match::findMatch(int journeyNum1, int journeyNum2)
{    
     //test to see if paths1 and paths2 are set right
     cout << "Testing paths1 & paths2\n";
     for(int i(0); i<paths1.size(); i++)
     {
          for(int j(0); j<paths1[i].length(); j++)
               cout << paths1[i].returnVertex(j) << "  ";
          cout << endl;
     }
               
     cout << endl;
     
     for(int i(0); i<paths2.size(); i++)
     {
          for(int j(0); j<paths2[i].length(); j++)
               cout << paths2[i].returnVertex(j) << "  ";
          cout << endl;
     }
     cout << "Done with paths output!\n";
     //end test
     
       
       for(int u(0); u<paths1.size(); u++)
       {
            for(int v(0); v<paths2.size(); v++)
            {
                 sharedVertices.resize(sharedVertices.size()+1);
       
                 path textpath;
                 path patternpath;
                 vector< int > text;
                 vector< int > pattern;
                 text.resize(0);
                 pattern.resize(0);
       
                 if(paths1[u].length()>paths2[v].length())
	             {
	                  textpath=paths1[u];
	                  patternpath=paths2[v];
	             }
	             else
	             {
	                  textpath=paths2[v];
	                  patternpath=paths1[u];
	             }
    
                 //puts path into vector
                 for(int i(0); i<patternpath.length(); i++)
                      pattern.push_back(patternpath.returnVertex(i));
         
                 //puts path into vector
                 for(int i(0); i<textpath.length(); i++)
                      text.push_back(textpath.returnVertex(i));
                 
                 //Knuth-Morris-Pratt method
                 path matches;
                 
                 matches = KMP(text, pattern);
                 
                 //if sharedVertices has not been set to anything yet
                 if(((sharedVertices.size()==1)&&(sharedVertices[0].empty()))&&(matches.length()>1))
                 {
                      sharedVertices[0].push_back(matches);
                      path temp;
                      temp = temp+journeyNum1+journeyNum2;
                      sharedVertices[0].push_back(temp);
                      sharedVertices[0].push_back(textpath);
                      sharedVertices[0].push_back(patternpath);
                 }
	             else if(matches.length()>1)
                 {
                      bool samePath=false;
                      //Checks to see if this pattern has already been found among other journeys
                      for(int i(0); i<sharedVertices.size(); i++)
                           if(!sharedVertices[i].empty())
                                if(matches==sharedVertices[i][0])
                                     samePath=true;
                      if(!samePath)//this is a new shared path between only these two journeys so far
                      {
                           //sharedVertices.resize(sharedVertices.size()+1);
                           sharedVertices[sharedVertices.size()-1].push_back(matches);
                           path temp;
                           temp = temp+journeyNum1+journeyNum2;
                           sharedVertices[sharedVertices.size()-1].push_back(temp);
                           sharedVertices[sharedVertices.size()-1].push_back(textpath);
                           sharedVertices[sharedVertices.size()-1].push_back(patternpath);
                      }
                      else//This shared path already exists with other journeys
                      {
                           bool hasTextpath=false, hasPatternpath=false;
                           int index;
                           for(int i(0); i<sharedVertices.size(); i++)
                                if(sharedVertices[i][0]==matches)
                                {
                                     index=i;
                                     break;
                                }
                           for(int i(2); i<sharedVertices[index].size(); i++)
                           {
                                if(sharedVertices[index][i]==textpath)
                                     hasTextpath=true;
                                if(sharedVertices[index][i]==patternpath)
                                     hasPatternpath=true;
                           }
                           if(!hasTextpath)
                                sharedVertices[index].push_back(textpath);
                           if(!hasPatternpath)
                                sharedVertices[index].push_back(patternpath);
                      }
                 }
                 
                 //deletes reserved space in sharedVertices if no match is found between these two journeys
                 if(sharedVertices[sharedVertices.size()-1].empty())
                      sharedVertices.resize(sharedVertices.size()-1);
            }
       }
       
       if(!sharedVertices.empty())
       {
       vector< vector< path > > groupings;
       vector< vector< path > > newGroupings;
       groupings.resize(1);
       
       newGroupings = sharedVertices;
       groupings[0] = newGroupings[newGroupings.size()-1];
       newGroupings.resize(newGroupings.size()-1);
       
       //Tests groupings
       /*cout << "\n\nThis is what groupings holds!!\n\n";
       for(int i(0); i<groupings.size(); i++)
       {
           for(int j(0); j<groupings[i].size(); j++)
           {
               for(int k(0); k<groupings[i][j].length(); k++)
                    cout << groupings[i][j].returnVertex(k) << "  ";
               cout << endl;
           }
           
           cout << endl << endl;
       }
       //Ends groupings test
       
       //Tests newGroupings
       cout << "\n\nThis is what newGroupings holds!!\n\n";
       for(int i(0); i<newGroupings.size(); i++)
       {
           for(int j(0); j<newGroupings[i].size(); j++)
           {
               for(int k(0); k<newGroupings[i][j].length(); k++)
                    cout << newGroupings[i][j].returnVertex(k) << "  ";
               cout << endl;
           }
           
           cout << endl << endl;
       }*/
       //Ends newGroupings test
       
       for(int m(0); m<newGroupings.size(); m++)
       {
            path subset;
            
		    checkOverlap(groupings, newGroupings, subset, m);
       }
      
      sharedVertices = groupings;
      }
      
      //Tests sharedVertices
      cout << "\n\nThis is what sharedVertices holds!!\n\n";
       for(int i(0); i<sharedVertices.size(); i++)
       {
           for(int j(0); j<sharedVertices[i].size(); j++)
           {
               for(int k(0); k<sharedVertices[i][j].length(); k++)
                    cout << sharedVertices[i][j].returnVertex(k) << "  ";
               cout << endl;
           }
           
           cout << endl << endl;
       }
       //Ends sharedVertices test
       
       return sharedVertices;
}


//match::KMP(vector< int > const & text, vector< int > const & pattern) const
// member function
//
//pre:
// -text and pattern have been properly set
//
//post:
// -returns any subset of the two given vectors
//
path KMP(vector< int > const & text, vector< int > const & pattern)
{
     
     path intersection;
	vector< int > newPattern;
	newPattern=pattern;
     //finds consecutively matched vertices
     while(newPattern.size()>1)
     {
     //creates shift table
     vector< int > T(newPattern.size() + 1, -1);
     for(int i = 1; i <= newPattern.size(); i++)
     {
          int pos = T[i - 1];
          while(pos != -1 && newPattern[pos] != newPattern[i - 1])
               pos = T[pos];
          T[i] = pos + 1;
     }
	
     //finds consecutively matched vertices
     path matches;
     path temp;
     int textp = 0;
     int patternp = 0;
     while(textp < text.size())
     {
          while(patternp != -1 && (patternp == newPattern.size() || newPattern[patternp] != text[textp]))
               patternp = T[patternp];
          if((newPattern[patternp] == text[textp]) && (patternp != -1))
               matches = matches+newPattern[patternp];

          if(patternp == newPattern.size())
               break;
               
          patternp++;
          textp++;
     }
     
     if(matches.length()>intersection.length())
          intersection = matches;
     
     vector< int > tempPattern;
     tempPattern.resize(0);
     for(int i(1); i<newPattern.size(); i++)
          tempPattern.push_back(newPattern[i]);
     newPattern = tempPattern;
     }

     return intersection;
}


//match::setPaths(int pathsIndicator, vector< path > const & newPaths)
// member function
//
//pre:
// -none
//
//post:
// -respective paths are set to newPaths
//
//O(1)
void match::setPaths(int pathsIndicator, vector< path > const & newPaths)
{
     if(pathsIndicator=1)
          for(int i(0); i<newPaths.size(); i++)
               paths1.push_back(newPaths[i]);
     else if(pathsIndicator=2)
          for(int i(0); i<newPaths.size(); i++)
               paths2.push_back(newPaths[i]);
     else
          cout << "\nIllegal paths' indicator!\n";
}

//match::returnPaths(int pathsIndicator)
// member function
//
//pre:
// -vector of paths (either 1 or 2 depending on the pathIndicator) has been set
//
//post:
// -returns respective paths
//
//O(1)
vector< path > match::returnPaths(int pathsIndicator) const
{
     if(pathsIndicator=1)
          return paths1;
     else if(pathsIndicator=2)
          return paths2;
     else
          cout << "\nIllegal paths' indicator!\n";
}

//match::returnSharedVertices() const
// member function
//
//pre:
// -findMatch has most likely already been called
//
//post:
// -returns shared vertices between two journeys
//
//O(1)
vector< vector< path > > match::returnSharedVertices() const
{
     return sharedVertices;
}
