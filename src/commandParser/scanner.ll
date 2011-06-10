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
stats           { return STATMODE; }

demo            { return DEMOMODE; }

"-c"            { return COUNTFLAG; }

"-v"            { return VERTICESFLAG; }

"-j"            { return JOURNEYSFLAG; }

"-d"            { return DIRECTEDFLAG; }

"-u"            { return UNDIRECTEDFLAG; }

"-w"            { return WEIGHTFLAG; }

"-f"            { return FILEFLAG; }

"-p"            { return PRINTFLAG; }

"-np"           { return NOPRINTFLAG; }

"-h"            { return HELP; }
"--help"        { return HELP; }

"-b"            { return BISHARING; }

"--dease"       { return DEASEFLAG; }

"--nash"        { return NASHFLAG; }

"--heuristics-info" { return HEURISTICSINFO; }

[a-zA-Z0-9.]*   { yylval.str_val = new string(yytext); return STRING; }

\ |\t|\n        { ; }

%%