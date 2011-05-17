#include "rand.h"
#include <cstdlib>
#include <ctime>

static bool seeded;

//randomGenerator()
// generates random number
//
//pre:
// -randMax is one more than maximum number desired
//
//post:
// -returns random number between 0 and randMax, including 0 but not randMax
int randomGenerator(int randMax)
{

    return randomWeight(0, randMax);

}

//randomWeight()
// generates random weight
//
//pre:
// -min contains lower bound of weight
// -max contains upper bound of weight
//
//post:
// -returns a number that meets given requirements
//
int randomWeight(int min, int max)
{

    if(not(seeded)) {
        srand(time(0));
        seeded = true;
    }
    return ((rand() % (max-min+1)) + min);

}