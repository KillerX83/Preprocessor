	// generate header file
%defines "parser.h"

	// the parser implementation file name
%output "parser.cpp"

	// for location tracking support
%locations

	// Generate the parser description file
%verbose

	// Enable run-time trace
%define parse.trace

	// for reentrant parser
%define api.pure full

	// when multiple parsers' are used
	// not for this tutorial
	//%define api.prefix {tk}

	// provides verbose error messages
	// about syntax error
 %define parse.error verbose

	// yylex scanner interface
	// this is a must-have for re-entrant scanner 
%param	{yyscan_t scanner}

	// for interaction with my own C++ class
%parse-param	{CParseTree* pParseTree}

	// place this code at the top of 
	// generated bison implementation file, i.e., parser.cpp
%code requires
{
	#pragma warning (disable: 4005)

	#include <iostream>
	#include <cstdio>

	#include "ParseTree.h"
		
	using namespace std;

	typedef void* yyscan_t;

}

	// this code block is used for declaration type and functions
	// that requires YYSTYPE, the symantic type
%code {
	
	typedef void* yyscan_t;

	extern int yylex(YYSTYPE*, YYLTYPE*, yyscan_t);

	void yyerror (YYLTYPE*, yyscan_t yyscanner, CParseTree* pParseTree, const char*);
}

%initial-action
{
	/* code for initialization before parsing 
		code in this block is executed each time yyparse is called. */

		// yydebug = 1;
}

	// we are going to use
	// bison's newer semantic data type definitions
	// %define api.value.type union
%union
{	
	int intg;
	char* cstr;
	double d;
	node* ASTnode;
}
	// attach TKN_ prefix to the user defined 
	// token type
%define api.token.prefix {TKN_}

%token	DEBUG_ON DEBUG_OFF
%type<ASTnode> program stmt expression def read list 

	// for parser debugging and tracing use
%printer { fprintf(yyoutput, "--- %s", $$); } <cstr>

	// for destructors' to call when parser' stack unwinding
	// these routines are called only when error recovery by bison
%destructor { std::cout<<$$<<" is deleted"; delete[] $$; $$ = nullptr;  } <cstr>

%start program

%%

program: %empty
	| program statement
	;
	
statement: CleanString
	| '#' for identifier '=' expression to expression '\n' list #next
	| '#' def
	| '#' read
	;

def: variable type
	| variable type ',' def
	;

read: variable
	| variable ',' read
	;

expression: value
	| variable
	| expression '+' expression
	| expression '-' expression
	| expression '*' expression
	| expression '/' expression
	| '(' expression ')'
	;

list: %empty
	| stmt list
	;

value: constant
	| '&' variable
	;

variable: identifier
	| identifier '(' expression ')'
	| identifier '(' expression ',' expression ')'
	;



	
	// #def varname
	// #def varname2(varname)
%%

// newer yyerror() function definition
// for use with reentant scanner and parser
// with location tracking
void yyerror (YYLTYPE *yylloc, yyscan_t yyscanner,
	 CParseTree* pParseTree, const char* msg)
{
	std::cout<<"Error - "<<msg<<std::endl;
}