%{

#include <utility>
#include <string>
using namespace std;

#include "parser.hpp"

%}

%option noyywrap

%%

[0-9]*          { yylval.int_val = atoi(yytext); return INTEGER; }

stat            { return STATMODE; }

demo            { return DEMOMODE; }

"-c"            { return COUNTFLAG; }

"-v"            { return VERTICESFLAG; }

"-j"            { return JOURNEYSFLAG; }

"-d"            { return DIRECTEDFLAG; }

"-u"            { return UNDIRECTEDFLAG; }

"-w"            { return WEIGHTFLAG; }

"-f"            { return FILEFLAG; }

[_a-zA-Z0-9]*   { yylval.str_val = new string(yytext); return STRING; }

\ |\t|\n        { ; }

%%