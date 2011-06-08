%{

#include "options.h"
#include <utility>
#include <string>
#include <iostream>
using namespace std;

// Declarations:

int yylex();

int yyerror(char*);

void reportError(const string& msg);
void reportErrorYYText(const string& msg);

int numberUnreportedErrors = 0;

%}

%token <int_val> INTEGER
%token <str_val> STRING
%token STATMODE
%token DEMOMODE
%token COUNTFLAG
%token VERTICESFLAG
%token JOURNEYSFLAG
%token DIRECTEDFLAG
%token UNDIRECTEDFLAG
%token WEIGHTFLAG
%token FILEFLAG
%token PRINTFLAG
%token NOPRINTFLAG
%token HELP
%token BISHARING

%union {
    int int_val;
    pair<int,int>* pair_val;
    string* str_val;
}

%start MODE

%%

// Grammar:

MODE
    : HELP
        {
            numErrors++;
        }
    | STATMODE STATARGLIST
        {
            programMode = STAT;
        }
    | DEMOMODE DEMOARGLIST
        {
            programMode = DEMO;
        }
    | error
        {
            reportErrorYYText("Invalid mode: ");
        }
    | /* nothing */
        {
            reportError("Missing mode");
            numErrors++;
        }
    ;

STATARGLIST
    : /* NOTHING */
    | STATARG STATARGLIST
    ;

STATARG
    : COMMONARG
    | COUNTFLAG INTEGER
        {
            STATcount = yylval.int_val;
        }
    | COUNTFLAG error
        {
            reportErrorYYText("Invalid count operand: ");
        }
    | VERTICESFLAG INTEGER
        {
            STATvertices = yylval.int_val;
        }
    | VERTICESFLAG error
        {
            reportErrorYYText("Invalid vertex operand: ");
        }
    | JOURNEYSFLAG INTEGER
        {
            STATjourneys = yylval.int_val;
        }
    | JOURNEYSFLAG error
        {
            reportErrorYYText("Invalid journey operand: ");
        }
    | DIRECTEDFLAG
    | UNDIRECTEDFLAG
    | WEIGHTFLAG INTEGER INTEGER
        {
            STATmaxWeight = max($2,
                                $3);
            STATminWeight = min($2,
                                $3);
        }
    | WEIGHTFLAG error
        {
            reportError("Invalid weight operand(s)");
        }
    ;

DEMOARGLIST
    : /* NOTHING */
    | DEMOARG DEMOARGLIST
    ;

DEMOARG
    : COMMONARG
    | FILEFLAG STRING
    | FILEFLAG error
        {
            reportErrorYYText("Invalid file operand: ");
        }
    ;

COMMONARG
    : error
        {
            reportErrorYYText("Invalid option: ");
        }
    | PRINTFLAG
        {
            dumpGraphToFile = true;
        }
    | NOPRINTFLAG
        {
            dumpGraphToFile = false;
        }
    | BISHARING
        {
            biSharing = true;
        }
    ;

%%

// Definitions:

int yylex() {
    return scanner->yylex();
}

int yyerror(char* msg) {
    numberUnreportedErrors++;
    return 0;
}

// prints an error message along with the line number
void reportError(const string& msg){
    if(numberUnreportedErrors > 0){
        numberUnreportedErrors--;
        cerr << "Error: " << msg << endl;
        numErrors++;
    }
}

// prints an error message along with the line number
void reportErrorYYText(const string& msg){
    if(numberUnreportedErrors > 0){
        numberUnreportedErrors--;
        cerr << "Error: " << msg << " \"" << scanner->YYText() << "\"\n";
        numErrors++;
    }
}
