/*
 * File: color.h
 *
 *        Contains the ANSI Color Library
 *
 *        For More Information:
 *
 *        <http://en.wikipedia.org/wiki/ANSI_escape_code>
 */
#include <string>
#include <iostream>
using namespace std;

#ifndef _COLOR_LIB_
#define _COLOR_LIB_

/*
 * Function: ansi
 *
 *        Converts an ANSI code to Terminal Output
 *
 * Arguments:
 *
 * code - the ANSI Code
 *
 * Returns:
 *
 *        The ANSI Terminal Output for the Given Code
 */
extern const string ansi(string code);

// Foreground Color Codes
extern const string FGBLACK;
extern const string FGDARKGRAY;
extern const string FGDARKGREY;
extern const string FGDARKRED;
extern const string FGRED;
extern const string FGDARKGREEN;
extern const string FGGREEN;
extern const string FGDARKYELLOW;
extern const string FGYELLOW;
extern const string FGDARKBLUE;
extern const string FGBLUE;
extern const string FGDARKPURPLE;
extern const string FGPURPLE;
extern const string FGDARKCYAN;
extern const string FGCYAN;
extern const string FGGREY;
extern const string FGGRAY;
extern const string FGWHITE;

// Background Color Codes
extern const string BGBLACK;
extern const string BGRED;
extern const string BGGREEN;
extern const string BGYELLOW;
extern const string BGBLUE;
extern const string BGPURPLE;
extern const string BGCYAN;
extern const string BGWHITE;

// End Color Codes
extern const string ENDFGC;
extern const string ENDBGC;
extern const string ENDC;
extern const string RESET;

#endif
