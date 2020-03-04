	// generate header file
%defines "parser.h"

	// the parser implementation file name
%output "parser.cpp"

	// for location tracking support
%locations



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
	#include <string>
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

		yydebug = 1;
}

	// we are going to use
	// bison's newer semantic data type definitions
	// %define api.value.type union
%union
{	
	int intg;
	std::string cstr;
	double dbl;
	enum class TYPE { INTG=0, DBL} ;
}
	// attach TKN_ prefix to the user defined 
	// token type
%define api.token.prefix {TKN_}

%token	DEBUG_ON DEBUG_OFF
%token '#' '&'  ',' '\n' 
%token for next to read def string
%token  identifier
%token constant
%token  type
%right '='
%left '+' '-'
%left '*' '/'

	

%start program

%%

program: %empParseTreey
	| program statement { $2-> Action(); pParseTree.TreeFree($2); }
	;
	
statement: '#' for identifier '=' expression to expression '\n' list  '\n'		{ $$ = pParseTree.NewFor($3, $5, $7, $9); }
	| '#' def DefOp '\n'														{ $$ = $3; }
	| '#' read ReadOp '\n'														{ $$ = $3; }
	| line																		{ $$ = $1; }
	| '\n'
	;

line: string '&' variable line			{ $$ = pParseTree.NewLine($1, $3, $4); }
	| string '\n'						{ $$ = pParseTree.NewLine($1, NULL, NULL); }
	| '&' variable line					{ $$ = pParseTree.NewLine(NULL, $2, $3); }
	| '\n'
	;

DefOp: variable type			{ $$ = pParseTree.NewDef($1, $2, NULL); }
	| variable type ',' DefOp	{ $$ = pParseTree.NewDef($1, $2, $4); }
	;

ReadOp: variable				{ $$ = pParseTree.NewRead($1); }
	| variable ',' ReadOp		{ $$ = pParseTree.NewRead($1, $3); }
	;

expression: constant				{ $$ = pParseTree.NewNum($1); }
	| variable						{ $$ = $1; }
	| expression '+' expression		{ $$ = pParseTree.NewSum($1, $3); }
	| expression '-' expression		{ $$ = pParseTree.NewSub($1, $3); } 
	| expression '*' expression		{ $$ = pParseTree.NewProduct($1, $3); } 
	| expression '/' expression		{ $$ = pParseTree.NewDiv($1, $3); } 
	| '(' expression ')'			{ $$ = $2; }
	;

list: '#' next identifier		 // можно ли убрать связь list и for?
	| statement list			{ $$ = pParseTree.NewList($1, $2); }
	;

variable: identifier								{ $$ = pParseTree.NewVar($1, NULL, NULL); }
	| identifier '(' expression ')'					{ $$ = pParseTree.NewVar($1, $3, NULL); }
	| identifier '(' expression ',' expression ')' 	{ $$ = pParseTree.NewVar($1, $3, $5); }
	;


%%

// newer yyerror() function definition
// for use with reentant scanner and parser
// with location tracking
void yyerror (YYLTYPE *yylloc, yyscan_t yyscanner,
	 CParseTree* pParseTree, const char* msg)
{
	std::cout<<"Error - "<<msg<<std::endl;
}