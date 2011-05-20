//Christopher Earl
//basicStructures.cpp
// contains intWInf and floatWinf member functions

#include <vector>
#include <iostream>

using namespace std;

#include "basicStructures.h"

const string InfinitySymbol = "*";

///
///intWInf member functions
///

//intWInf::intWInf()
// c'tor
//
//pre:
// -none
//
//post:
// -intWInf constructed to infinity
//
//O(1)
intWInf::intWInf()
:internalInfinity(true), internalInt(0)
{
    
}

//intWInf::intWInf()
// c'tor
//
//pre:
// -newIntWInf is a valid intWInf
//
//post:
// -intWInf constructed to newIntWInf
//
//O(1)
intWInf::intWInf(intWInf const & newIntWInf)
:internalInfinity(newIntWInf.isInfinity()), internalInt(newIntWInf.value())
{
    
}

//intWInf::intWInf()
// c'tor
//
//pre:
// -newInt is a valid integer
//
//post:
// -intWInf constructed to newInt
//
//O(1)
intWInf::intWInf(int newInt)
:internalInfinity(false), internalInt(newInt)
{
    
}

//intWInf::intWInf()
// c'tor
//
//pre:
// -inf is true if value is infinity
// -value is a valid integer
//
//post:
// -intWInf constructed to value given
//
//O(1)
intWInf::intWInf(bool inf, int value)
:internalInfinity(inf), internalInt(value)
{
    
}

//intWInf::isInfinity()
// returns true if value is infinity
//
//pre:
// -none
//
//post:
// -returns true if internalInfinity is true
//          false otherwise
//
//O(1)
bool intWInf::isInfinity() const
{
    
    return internalInfinity;
    
}

//intWInf::value()
// returns value
//
//pre:
// -none
//
//post:
// -returns value
//
//O(1)
int intWInf::value() const
{
    
    return internalInt;
    
}

//intWInf::operator==()
// returns true if object's value is equal to other's
//
//pre:
// -other is a valid intWInf
//
//post:
// -returns true if values are equal
//          false otherwise
//
//O(1)
bool intWInf::operator==(intWInf const & other) const
{
    
    bool answer = false;
    
    if(((isInfinity() == true)           //if( ( (this is infinity)
    &&(other.isInfinity() == true))     //and (other is infinity))
    ||((isInfinity() == false)         //or ( (this is not infinity)
    &&(other.isInfinity() == false)  //and (other is not infinity)
    &&(value() == other.value())))   //and (values are equal)))
    answer = true;
    
    return answer;
    
}

//intWInf::operator=()
// sets this equal to other
//
//pre:
// -other is a valid intWInf
//
//post:
// -this equals other
//
//O(1)
void intWInf::operator=(intWInf const & other)
{
    
    if(other.isInfinity() == true)
        setValue();
    else
        setValue(other.value());
    
}

//intWInf::operator+=()
// sets this equal to itself plus other
//
//pre:
// -other is a valid intWInf
//
//post:
// -this equals itself plus other
//
//O(1)
void intWInf::operator+=(intWInf const & other)
{
    
    if(other.isInfinity() == true
        ||isInfinity() == true)
        setValue();
    else
        setValue(value() + other.value());
    
}

//intWInf::operator>()
// returns true if object's value is greater than other's
//
//pre:
// -other is a valid intWInf
//
//post:
// -returns true if object's value is greater than other's
//          false otherwise
//
//O(1)
bool intWInf::operator>(intWInf const & other) const
{
    
    bool answer = false;
    
    if((other.isInfinity() == false)    //if( (other is not infinity)
    &&((isInfinity() == true)        //and ( (this is infinity)
    ||(value() > other.value())))    //or (this > other)))
    answer = true;
    
    return answer;
    
}

//intWInf::operator>=()
// returns true if object's value is greater than or equal to other's
//
//pre:
// -other is a valid intWInf
//
//post:
// -returns true if object's value is greater than or equal to other's
//          false otherwise
//
//O(1)
bool intWInf::operator>=(intWInf const & other) const
{
    
    bool answer = false;
    
    if((*this > other)
        ||(*this == other))
        answer = true;
    
    return answer;
    
}

//intWInf::operator<()
// returns true if object's value is less than other's
//
//pre:
// -other is a valid intWInf
//
//post:
// -returns true if object's value is less than other's
//          false otherwise
//
//O(1)
bool intWInf::operator<(intWInf const & other) const
{
    
    bool answer = false;
    
    if((isInfinity() == false)          //if( (this is not infinity)
    &&((other.isInfinity() == true)  //and ( (other is infinity)
    ||(value() < other.value())))    //or (this < other)))
    answer = true;
    
    return answer;
    
}

//intWInf::operator<=()
// returns true if object's value is less than or equal to other's
//
//pre:
// -other is a valid intWInf
//
//post:
// -returns true if object's value is less than or equal to other's
//          false otherwise
//
//O(1)
bool intWInf::operator<=(intWInf const & other) const
{
    
    bool answer = false;
    
    if((*this < other)
        ||(*this == other))
        answer = true;
    
    return answer;
    
}

//intWInf::operator+()
// adds two intWInf together
//
//pre:
// -other is a valid intWInf
//
//post:
// -returns sum of this and other
//
//O(1)
intWInf intWInf::operator+(intWInf const & other) const
{
    
    intWInf answer(true, 0);
    
    if((isInfinity() == false)
        &&(other.isInfinity() == false))
        answer.setValue(value() + other.value());
    
    return answer;
    
}

//intWInf::operator==()
// returns true if object's value is equal to other's
//
//pre:
// -other is a valid int
//
//post:
// -returns true if values are equal
//          false otherwise
//
//O(1)
bool intWInf::operator==(int const & other) const
{
    
    bool answer = false;
    
    if((isInfinity() == false)           //if( (this is infinity)
    &&(value() == other))             //and (values are equal))
    answer = true;
    
    return answer;
    
}

//intWInf::operator=()
// sets this equal to other
//
//pre:
// -other is a valid int
//
//post:
// -this equals other
//
//O(1)
void intWInf::operator=(int const & other)
{
    
    setValue(other);
    
}

//intWInf::operator+=()
// sets this equal to itself plus other
//
//pre:
// -other is a valid int
//
//post:
// -this equals itself plus other
//
//O(1)
void intWInf::operator+=(int const & other)
{
    
    if(isInfinity() == false)
        setValue(value() + other);
    
}

//intWInf::operator>()
// returns true if object's value is greater than other's
//
//pre:
// -other is a valid int
//
//post:
// -returns true if object's value is greater than other's
//          false otherwise
//
//O(1)
bool intWInf::operator>(int const & other) const
{
    
    bool answer = false;
    
    if((isInfinity() == true)       //if( (this is infinity)
    ||(value() > other))  //or (this > other))
    answer = true;
    
    return answer;
    
}

//intWInf::operator>=()
// returns true if object's value is greater than or equal to other's
//
//pre:
// -other is a valid int
//
//post:
// -returns true if object's value is greater than or equal to other's
//          false otherwise
//
//O(1)
bool intWInf::operator>=(int const & other) const
{
    
    bool answer = false;
    
    if((*this > other)
        ||(*this == other))
        answer = true;
    
    return answer;
    
}

//intWInf::operator<()
// returns true if object's value is less than other's
//
//pre:
// -other is a valid int
//
//post:
// -returns true if object's value is less than other's
//          false otherwise
//
//O(1)
bool intWInf::operator<(int const & other) const
{
    
    bool answer = false;
    
    if((isInfinity() == false)  //if( (this is not infinity)
    &&(value() < other))     //and (this < other))
    answer = true;
    
    return answer;
    
}

//intWInf::operator<=()
// returns true if object's value is less than or equal to other's
//
//pre:
// -other is a valid int
//
//post:
// -returns true if object's value is less than or equal to other's
//          false otherwise
//
//O(1)
bool intWInf::operator<=(int const & other) const
{
    
    bool answer = false;
    
    if((*this < other)
        ||(*this == other))
        answer = true;
    
    return answer;
    
}

//intWInf::operator+()
// adds an intWInf and an int together
//
//pre:
// -other is a valid int
//
//post:
// -returns sum of this and other
//
//O(1)
intWInf intWInf::operator+(int const & other) const
{
    
    intWInf answer(true, 0);
    
    if(isInfinity() == false)
        answer.setValue(value() + other);
    
    return answer;
    
}

//intWInf::setValue()
// sets value to infinity
//
//pre:
// -none
//
//post:
// -value is infinity
//
//O(1)
void intWInf::setValue()
{
    
    internalInfinity = true;
    internalInt = 0;
    
}

//intWInf::setValue()
// sets value to parameter
//
//pre:
// -newValue is a valid int
//
//post:
// -value is equal to newValue
//
//O(1)
void intWInf::setValue(int newValue)
{
    
    internalInfinity = false;
    internalInt = newValue;
    
}

///
///floatWInf member functions
///

//floatWInf::floatWInf()
// c'tor
//
//pre:
// -none
//
//post:
// -floatWInf constructed to infinity
//
//O(1)
floatWInf::floatWInf()
:internalInfinity(true), internalFloat(0)
{
    
}

//floatWInf::floatWInf()
// c'tor
//
//pre:
// -newFloatWInf is a valid floatWInf
//
//post:
// -floatWInf constructed to newFloatWInf
//
//O(1)
floatWInf::floatWInf(floatWInf const & newFloatWInf)
:internalInfinity(newFloatWInf.isInfinity()), internalFloat(newFloatWInf.value())
{
    
}

//floatWInf::floatWInf()
// c'tor
//
//pre:
// -newFloat is a valid float
//
//post:
// -floatWInf constructed to newFloat
//
//O(1)
floatWInf::floatWInf(float newFloat)
:internalInfinity(false), internalFloat(newFloat)
{
    
}

//floatWInf::floatWInf()
// c'tor
//
//pre:
// -inf is true if value is infinity
// -value is a valid float
//
//post:
// -floatWInf constructed to value given
//
//O(1)
floatWInf::floatWInf(bool inf, float value)
:internalInfinity(inf), internalFloat(value)
{
    
}

//floatWInf::isInfinity()
// returns true if value is infinity
//
//pre:
// -none
//
//post:
// -returns true if value is infinity
//          false otherwise
//
//O(1)
bool floatWInf::isInfinity() const
{
    
    return internalInfinity;
    
}

//floatWInf::value()
// returns value
//
//pre:
// -none
//
//post:
// -retruns value
//
//O(1)
float floatWInf::value() const
{
    
    return internalFloat;
    
}

//floatWInf::operator==()
// returns true if values of object and other are equal
//
//pre:
// -other is a valid floatWInf
//
//post:
// -returns true if values of object and other are equal
//          false otherwise
//
//O(1)
bool floatWInf::operator==(floatWInf const & other) const
{
    
    float acceptableDifference = .0005;
    bool answer = false;
    
    if(((isInfinity() == true)           //if( ( (this is infinity)
    &&(other.isInfinity() == true))     //and (other is infinity))
    ||((isInfinity() == false)         //or ( (this is not infinity)
    &&(other.isInfinity() == false)  //and (other is not infinity)
    //and (values are equal)))
    &&(abs(value() - other.value()) < acceptableDifference)))
    answer = true;
    
    return answer;
    
}

//floatWInf::operator=()
// sets this equal to other
//
//pre:
// -other is a valid floatWInf
//
//post:
// -this equals other
//
//O(1)
void floatWInf::operator=(floatWInf const & other)
{
    
    if(other.isInfinity() == true)
        setValue();
    else
        setValue(other.value());
    
}

//floatWInf::operator+=()
// sets this equal to itself plus other
//
//pre:
// -other is a valid floatWInf
//
//post:
// -this equals itself + other
//
//O(1)
void floatWInf::operator+=(floatWInf const & other)
{
    
    if((other.isInfinity() == true)
        ||(isInfinity() == true))
        setValue();
    else
        setValue(value() + other.value());
    
}

//floatWInf::operator>()
// returns true if object's value is greater than other's
//
//pre:
// -other is a valid floatWInf
//
//post:
// -returns true if object's value is greater than other's
//          false otherwise
//
//O(1)
bool floatWInf::operator>(floatWInf const & other) const
{
    
    bool answer = false;
    
    if((other.isInfinity() == false)    //if( (other is not infinity)
    &&((isInfinity() == true)        //and ( (this is infinity)
    ||(value() > other.value())))    //or (this > other)))
    answer = true;
    
    return answer;
    
}

//floatWInf::operator>=()
// returns true if object's value is greater than or equal to other's
//
//pre:
// -other is a valid floatWInf
//
//post:
// -returns true if object's value is greater than or equal to other's
//          false otherwise
//
//O(1)
bool floatWInf::operator>=(floatWInf const & other) const
{
    
    bool answer = false;
    
    if((*this > other)
        ||(*this == other))
        answer = true;
    
    return answer;
    
}

//floatWInf::operator<()
// returns true if object's value is less than other's
//
//pre:
// -other is a valid floatWInf
//
//post:
// -returns true if object's value is less than other's
//          false otherwise
//
//O(1)
bool floatWInf::operator<(floatWInf const & other) const
{
    
    bool answer = false;
    
    if((isInfinity() == false)          //if( (this is not infinity)
    &&((other.isInfinity() == true)  //and ( (other is infinity)
    ||(value() < other.value())))    //or (this < other)))
    answer = true;
    
    return answer;
    
}

//floatWInf::operator<=()
// returns true if object's value is less than or equal to other's
//
//pre:
// -other is a valid floatWInf
//
//post:
// -returns true if object's value is less than or equal to other's
//          false otherwise
//
//O(1)
bool floatWInf::operator<=(floatWInf const & other) const
{
    
    bool answer = false;
    
    if((*this < other)
        ||(*this == other))
        answer = true;
    
    return answer;
    
}

//floatWInf::operator+()
// adds two floatWInf together
//
//pre:
// -other is a valid floatWInf
//
//post:
// -returns sum of this and other
//
//O(1)
floatWInf floatWInf::operator+(floatWInf const & other) const
{
    
    floatWInf answer(true, 0);
    
    if((isInfinity() == false)
        &&(other.isInfinity() == false))
        answer.setValue(value() + other.value());
    
    return answer;
    
}

//floatWInf::operator-()
// subtracts two floatWInf together
//
//pre:
// -other is a valid floatWInf
//
//post:
// -returns difference of this and other
//
//O(1)
floatWInf floatWInf::operator-(floatWInf const & other) const
{
    
    floatWInf answer(true, 0);
    
    if((isInfinity() == false)
        &&(other.isInfinity() == false))
        answer.setValue(value() - other.value());
    
    return answer;
    
}

//floatWInf::operator==()
// returns true if values of object and other are equal
//
//pre:
// -other is a valid float
//
//post:
// -returns true if values of object and other are equal
//          false otherwise
//
//O(1)
bool floatWInf::operator==(float const & other) const
{
    
    float acceptableDifference = .0005;
    bool answer = false;
    
    if((isInfinity() == false)  //if( (this is not infinity)
                            //and (values are equal)))
        &&(abs(value() - other) < acceptableDifference))
    answer = true;
    
    return answer;
    
}

//floatWInf::operator=()
// sets this equal to other
//
//pre:
// -other is a valid float
//
//post:
// -this equals other
//
//O(1)
void floatWInf::operator=(float const & other)
{
    
    setValue(other);
    
}

//floatWInf::operator+=()
// sets this equal to itself plus other
//
//pre:
// -other is a valid float
//
//post:
// -this equals itself + other
//
//O(1)
void floatWInf::operator+=(float const & other)
{
    
    if(isInfinity() == false)
        setValue(value() + other);
    
}

//floatWInf::operator>()
// returns true if object's value is greater than other's
//
//pre:
// -other is a valid float
//
//post:
// -returns true if object's value is greater than other's
//          false otherwise
//
//O(1)
bool floatWInf::operator>(float const & other) const
{
    
    bool answer = false;
    
    if((isInfinity() == true)  //if( (this is infinity)
    ||(value() > other))      //or (this > other))
    answer = true;
    
    return answer;
    
}

//floatWInf::operator>=()
// returns true if object's value is greater than or equal to other's
//
//pre:
// -other is a valid float
//
//post:
// -returns true if object's value is greater than or equal to other's
//          false otherwise
//
//O(1)
bool floatWInf::operator>=(float const & other) const
{
    
    bool answer = false;
    
    if((*this > other)
        ||(*this == other))
        answer = true;
    
    return answer;
    
}

//floatWInf::operator<()
// returns true if object's value is less than other's
//
//pre:
// -other is a valid float
//
//post:
// -returns true if object's value is less than other's
//          false otherwise
//
//O(1)
bool floatWInf::operator<(float const & other) const
{
    
    bool answer = false;
    
    if((isInfinity() == false)  //if( (this is not infinity)
    &&(value() < other))     //and (this < other))
    answer = true;
    
    return answer;
    
}

//floatWInf::operator<=()
// returns true if object's value is less than or equal to other's
//
//pre:
// -other is a valid float
//
//post:
// -returns true if object's value is less than or equal to other's
//          false otherwise
//
//O(1)
bool floatWInf::operator<=(float const & other) const
{
    
    bool answer = false;
    
    if((*this < other)
        ||(*this == other))
        answer = true;
    
    return answer;
    
}

//floatWInf::operator+()
// adds two floatWInf together
//
//pre:
// -other is a valid float
//
//post:
// -returns sum of this and other
//
//O(1)
floatWInf floatWInf::operator+(float const & other) const
{
    
    floatWInf answer(true, 0);
    
    if(isInfinity() == false)
        answer.setValue(value() + other);
    
    return answer;
    
}

//floatWInf::operator/()
// divides floatWInf by a float
//
//pre:
// -other is a valid float
//
//post:
// -returns quotient of this and other
//
//O(1)
floatWInf floatWInf::operator/(float const & other) const
{
    
    floatWInf answer(true, 0);
    
    if(isInfinity() == false && other != 0)
        answer.setValue(value() / other);
    
    return answer;
    
}

//extraction operator
//pre- noe
//post- outputs value to the ostream.  If the value is infinity, outputs *

ostream& operator<<(ostream& fout, const intWInf& obj) {
    if(obj.isInfinity())
        fout << InfinitySymbol;
    else
        fout << obj.value();
    return fout;
}

ostream& operator<<(ostream& fout, const floatWInf& obj){
    if(obj.isInfinity())
        fout << InfinitySymbol;
    else
        fout << obj.value();
    return fout;
}

//floatWInf::setValue()
// sets value to infinity
//
//pre:
// -none
//
//post:
// -value is infinity
//
//O(1)
void floatWInf::setValue()
{
    
    internalInfinity = true;
    internalFloat = 0;
    
}

//floatWInf::setValue()
// sets value to parameter
//
//pre:
// -newFloat is a valid float
//
//post:
// -value is equal to newFloat
//
//O(1)
void floatWInf::setValue(float newFloat)
{
    
    internalInfinity = false;
    internalFloat = newFloat;
    
}

//abs()
// returns absolute value of parameter
//
//pre:
// -none
//
//post:
// -returns absolute value of parameter
//
//O(1)
float abs(float value)
{
    
    if(value >= 0)
        return value;
    else
        return (float)(-1)*value;
    
}
