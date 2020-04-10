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
	#include "ParseTree.h"
	#include "nodes.h"

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
	ASTnode* a;
	int intg;
	char* str;
	double dbl;
	NUMTYPE numtype;
}
	// attach TKN_ prefix to the user defined 
	// token type
%define api.token.prefix {TKN_}

%token	DEBUG_ON DEBUG_OFF
%token '#' '&'  ',' '\n' 
%token for next to read def
%token <str> identifier string
%token <intg> constantInt
%token <dbl> constantFloat
%token  <numtype> type;
%right '='
%left '+' '-'
%left '*' '/'
%type <a> statement line DefOp
%type <a> ReadOp expression list variable
	

%start program

%%
		//TODO: TreeFree
program: %empty
	| program statement { $2->Action(); }
	;
	
statement: '#' for identifier '=' expression to expression '\n' list  '\n' { $$ = new FORnode($3, $5, $7, $9); }
	| '#' def DefOp '\n'  { $$ = $3; }
	| '#' read ReadOp '\n' {$$ = $3; }
	| line {$$ = $1; }
	| '\n'
	;

line: string '&' variable line { $$ = new LINEnode($1, $3, $4); }
	| string '&' variable		{ $$ = new LINEnode($1, $3, NULL); }
	| string '\n'				{ $$ = new LINEnode($1, NULL, NULL); }
	| '&' variable line			{ $$ = new LINEnode("", $2, $3); }
	| '&' variable				{ $$ = new LINEnode("", $2, NULL); }
	;

DefOp: variable type		{ $$ = new DEFnode($1, $2, NULL); }
	| variable type ',' DefOp  { $$ = new DEFnode($1, $2, $4); }
	;

ReadOp: variable			{ $$ = new READnode($1, NULL); }
	| variable ',' ReadOp   { $$ = new READnode($1, $3); }
	;

expression: constantInt		{ $$ = new NUMnode($1, NUMTYPE::INT); }
	| constantFloat			{ $$ = new NUMnode($1, NUMTYPE::REAL); }
	| variable				{$$ = $1; }
	| expression '+' expression  { $$ = new SUMnode($1, $3);}
	| expression '-' expression	 { $$ = new SUBnode($1, $3); }
	| expression '*' expression	 { $$ = new PRODUCTnode($1, $3); }
	| expression '/' expression	 { $$ = new DIVnode($1, $3); }
	| '(' expression ')'		 { $$ = $2; }
	;

	// можно ли убрать связь list и for?
list: '#' next identifier				
	| statement list { $$ = new LISTnode($1, $2); }
	;

variable: identifier { $$ = new VARnode($1, NULL, NULL);}
	| identifier '(' expression ')' { $$ = new VARnode($1, $3, NULL);}
	| identifier '(' expression ',' expression ')' { $$ = new VARnode($1, $3, $5);}
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