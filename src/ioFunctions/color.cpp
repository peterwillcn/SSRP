#include "color.h"
#include <string>

using namespace std;

const string ansi(string code){
    return "\033[" + code + "m";
}

// Foreground Color Codes
const string FGBLACK = ansi("0;30");
const string FGDARKGRAY = ansi("1;30");
const string FGDARKGREY = ansi("1;30");
const string FGDARKRED = ansi("0;31");
const string FGRED = ansi("1;31");
const string FGDARKGREEN = ansi("0;32");
const string FGGREEN = ansi("1;32");
const string FGDARKYELLOW = ansi("0;33");
const string FGYELLOW = ansi("1;33");
const string FGDARKBLUE = ansi("0;34");
const string FGBLUE = ansi("1;34");
const string FGDARKPURPLE = ansi("0;35");
const string FGPURPLE = ansi("1;35");
const string FGDARKCYAN = ansi("0;36");
const string FGCYAN = ansi("1;36");
const string FGGREY = ansi("0;37");
const string FGGRAY = ansi("0;37");
const string FGWHITE = ansi("1;37");

// Background Color Codes
const string BGBLACK = ansi("0;40");
const string BGRED = ansi("0;41");
const string BGGREEN = ansi("0;42");
const string BGYELLOW = ansi("0;43");
const string BGBLUE = ansi("0;44");
const string BGPURPLE = ansi("0;45");
const string BGCYAN = ansi("0;46");
const string BGWHITE = ansi("1;47");

// End Color Codes
const string ENDFGC = ansi("39");
const string ENDBGC = ansi("49");
const string ENDC = ansi("22") + ENDFGC + ENDBGC;
const string RESET = ansi("0");