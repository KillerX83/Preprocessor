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
	#include <stdio.h>
	
	using namespace std;

	#include "parser.h"
	static int braces = 0;
}
WS		[\t ]
INTG	[0-9]+
FLOAT	[0-9]+\.[0-9]+
ID	[a-zA-Z]+
STRING [^#\t&\n ][^&\n]*
%s operator
%s substitution
%%
<substitution>{WS}+ { BEGIN(INITIAL); size_t size = strlen(yytext) + 1;
	yylval->str = new char[size];
	strcpy_s(yylval->str, size, yytext);
return TKN_string; }

<operator,INITIAL>[\t ]+
<INITIAL>"#" { BEGIN(operator); return '#'; }
<INITIAL>{STRING} { std::cout << yytext << std::endl; 
size_t size = strlen(yytext) + 1;
	yylval->str = new char[size];
	strcpy_s(yylval->str, size, yytext);
return TKN_string; }
<operator,INITIAL>"\n" { BEGIN(INITIAL); printf("\n\nLINE %d\n\n", yylineno); return '\n'; }
"&" { BEGIN(substitution); return '&';}


<substitution>"(" { braces++; return '('; }



<substitution>{ID}/{WS} {
	size_t size = strlen(yytext) + 1;
	yylval->str = new char[size];
	strcpy_s(yylval->str, size, yytext);
	return TKN_identifier; 
}
<substitution>{ID} { 
	if (braces == 0) BEGIN(INITIAL);
	size_t size = strlen(yytext) + 1;
	yylval->str = new char[size];
	strcpy_s(yylval->str, size, yytext);
	return TKN_identifier; 
}
<substitution>{ID}/"(" { 
	size_t size = strlen(yytext) + 1;
	yylval->str = new char[size];
	strcpy_s(yylval->str, size, yytext);
	return TKN_identifier; 
}
<substitution>")" { braces--; if (braces == 0) BEGIN(INITIAL); return ')'; }

<operator,substitution>"," |
"+"  |
"-"  |
"*"  |
"/"  |
"="   { return yytext[0];}

<operator>"(" |
")" { return yytext[0]; }

<operator>"def" { return TKN_def; }
<operator>"read" { return TKN_read; }
<operator>"for" { return TKN_for; }
<operator>"to" { return TKN_to; }
<operator>"next" { return TKN_next; }
<operator>"int" { yylval->numtype = NUMTYPE::INT; return TKN_type; }
<operator>"real" { yylval->numtype = NUMTYPE::REAL; return TKN_type; }


<operator>{ID} { size_t size = strlen(yytext) + 1;
	yylval->str = new char[size];
	strcpy_s(yylval->str, size, yytext); return TKN_identifier; }
<operator,substitution>{INTG}	{ yylval->intg = atoi(yytext); return TKN_constantInt; }
<operator,substitution>{FLOAT} { yylval->dbl = atof(yytext); return TKN_constantFloat; }




%%
