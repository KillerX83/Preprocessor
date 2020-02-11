	// output file definitions
%option outfile="lexer.cpp" header-file="lexer.h"

	// 8 bit scanner for unicode processing
	// reentrant scanner
%option 8bit reentrant noyywrap

	// we are going to use stack frame for "include" feature 
%option stack

%option warn nodefault

	// to interface with bison for reentrant parser
	// and scanner
%option bison-bridge bison-locations

	// line number tracking
%option yylineno

	// with multiple flex files are used in the same project
	// to prevent name crashes
	//%option prefix="tk"

	// our own parse tree data type
%option extra-type="CParseTree*"

	// these options are for windows compatibility
%option always-interactive
%option nounistd

	// put this block at the top of the 
	// generated scanner

%top{

	// this macro definition is for windows compatibility
#define YY_NO_UNISTD_H

	#pragma warning( disable: 4005)

	#include <iostream>
	#include <cmath>
	#include <cstring>
	
	using namespace std;

	#include "parser.h"
}

INTG	[0-9]+
FLOAT	[0-9]+.[0-9]+
CHARS	[a-zA-Z]+
%%



"#" |
","	|
"(" |
"+" |
"-" |
"*" |
"/" |
"&" |
"=" |
")" { return yytext[0];}

"def" { return def; }
"read" { return read; }
"for" { return for; }
"to" { return to; }
"int" { yylval.TYPE = 0; return int; }
"real" { yylval.TYPE = 1; return real; }

{CHARS}+ { return identifier; }
{INTG}	{ yylval.intg = atoi(yytext); return constant; }
{FLOAT} { yylval.dbl = atof(yytext); return constant; }

"debug_on"	{ return TKN_DEBUG_ON; }
"debug_off"	{ return TKN_DEBUG_OFF; }

[ \t] {}
\n	{ return yytext[0]; }

.+\n { return CleanString}

%%
