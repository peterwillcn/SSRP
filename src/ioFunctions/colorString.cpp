#include "colorString.h"
#include "color.h"
#include <string>
using namespace std;

// private:
//     string data;
//     color myColor;

string colorToStr(int c) {
    switch(c) {
        case Color::NoColor:
            return "";
        case Color::Red:
            return FGRED;
        case Color::Blue:
            return FGBLUE;
        case Color::Yellow:
            return FGYELLOW;
        case Color::Green:
            return FGGREEN;
        case Color::White:
            return FGWHITE;
        case Color::Black:
            return FGBLACK;
    }
}

string String(string& data, int color) {
    string temp = colorToStr(color) + data + ENDC;
    return temp;
}

string String(const char* data, int color) {
    string temp = colorToStr(color) + data + ENDC;
    return temp;
}

colorString::colorString()
    : data(""), myColor(Color::NoColor) {
    // Do Nothing
}

colorString::colorString(const string& initData, int c)
    : data(initData), myColor(c) {
    // Do Nothing
}

colorString::~colorString() {
    // Do Nothing
}

char& colorString::operator[](int ref) {
    return data[ref];
}

const char& colorString::operator[](int ref) const {
    return data[ref];
}

colorString& colorString::operator+=(const colorString& other) {
    data += other.data;
    return *this;
}

colorString& colorString::operator+=(const char* other) {
    data += string(other);
    return *this;
}

colorString& colorString::operator+=(const string& other) {
    data += other;
    return *this;
}

colorString& colorString::operator+=(char other) {
    data += other;
    return *this;
}

int colorString::size() const {
    return data.size();
}

ostream& operator<<(ostream& os, const colorString& str) {
    os << colorToStr(str.myColor) << str.data << ENDC;
}

istream& operator>>(istream& is, colorString& str) {
    string temp;
    is >> temp;
    str.data = temp;
}
