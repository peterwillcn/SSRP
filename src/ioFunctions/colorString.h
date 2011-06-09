#ifndef _COLOR_STRING_
#define _COLOR_STRING_

#include <string>
#include "color.h"
using namespace std;

namespace Color {
    const int NoColor = 0;
    const int Red = 1;
    const int Blue = 2;
    const int Green = 3;
    const int Yellow = 4;
    const int White = 5;
    const int Black = 6;
}

string String(string& data, int color = Color::NoColor);
string String(const char* data, int color = Color::NoColor);

class colorString {
private:
    string data;
    int myColor;

    friend ostream& operator<<(ostream&, const colorString&);
    friend istream& operator>>(istream&, colorString&);

public:

    colorString();
    colorString(const string& initData, int color = Color::NoColor);

    ~colorString();

    char& operator[](int ref);
    const char& operator[](int ref) const;

    colorString& operator+=(const colorString& other);
    colorString& operator+=(const char* other);
    colorString& operator+=(const string& other);
    colorString& operator+=(char other);

    int size() const;
};

ostream& operator<<(ostream& os, const colorString& str);
istream& operator>>(istream& is, colorString& str);

#endif
