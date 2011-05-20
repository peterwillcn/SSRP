#ifndef _BASICSTRUCTURES_H_
#define _BASICSTRUCTURES_H_

//Christopher Earl
//basicStructures.h
// contains classes intWInf and floatWInf

#include <iostream>
#include <vector>

using namespace std;

extern const string InfinitySymbol;

class intWInf
{
    
private:
    
    bool internalInfinity;
    int internalInt;
    
public:
    intWInf();
    intWInf(intWInf const & newIntWInf);
    intWInf(int newInt);
    intWInf(bool inf, int value);
    
    //accessor member func's
    bool isInfinity() const;
    int value() const;
    
    //operators for intWInf
    bool operator==(intWInf const & other) const;
    void operator=(intWInf const & other);
    void operator+=(intWInf const & other);
    bool operator>(intWInf const & other) const;
    bool operator>=(intWInf const & other) const;
    bool operator<(intWInf const & other) const;
    bool operator<=(intWInf const & other) const;
    intWInf operator+(intWInf const & other) const;
    
    //operators for int
    bool operator==(int const & other) const;
    void operator=(int const & other);
    void operator+=(int const & other);
    bool operator>(int const & other) const;
    bool operator>=(int const & other) const;
    bool operator<(int const & other) const;
    bool operator<=(int const & other) const;
    intWInf operator+(int const & other) const;
    
    //mutator member func's
    void setValue();
    void setValue(int newValue);
    
};

class floatWInf
{
    
private:
    
    bool internalInfinity;
    float internalFloat;
    
public:
    
    floatWInf();
    floatWInf(floatWInf const & newFloatWInf);
    floatWInf(float newFloat);
    floatWInf(bool inf, float value);
    
    //accessor member func's
    bool isInfinity() const;
    float value() const;
    
    //operators for floatWInf
    bool operator==(floatWInf const & other) const;
    void operator=(floatWInf const & other);
    void operator+=(floatWInf const & other);
    bool operator>(floatWInf const & other) const;
    bool operator>=(floatWInf const & other) const;
    bool operator<(floatWInf const & other) const;
    bool operator<=(floatWInf const & other) const;
    floatWInf operator+(floatWInf const & other) const;
    floatWInf operator-(floatWInf const & other) const;
    
    
    
    //operators for float
    bool operator==(float const & other) const;
    void operator=(float const & other);
    void operator+=(float const & other);
    bool operator>(float const & other) const;
    bool operator>=(float const & other) const;
    bool operator<(float const & other) const;
    bool operator<=(float const & other) const;
    floatWInf operator+(float const & other) const;
    floatWInf operator/(float const & other) const;
    //mutator member func's
    void setValue();
    void setValue(float newFloat);
    
};

float abs(float value);
ostream& operator<<(ostream& fout, const intWInf& obj);
ostream& operator<<(ostream& fout, const floatWInf& obj);

extern const floatWInf infinity;  //float used to hold infinity

# endif
