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
	#include "nodes.h"
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
	double dbl;
	ASTnode* node;
	enum class TYPE { INTG=0, DBL} ;
}
	// attach TKN_ prefix to the user defined 
	// token type
%define api.token.prefix {TKN_}

%token	DEBUG_ON DEBUG_OFF
%token '#' '&'  ',' '\n' CleanString for next to
%token <cstr> identifier
%token <dbl>  constant
%token <TYPE> type
%right '='
%left '+' '-'
%left '*' '/'
%type<node> statement expression def read 
%type<node> list variable value CleanString

	// for parser debugging and tracing use
	//%printer { fprintf(yyoutput, "--- %s", $$); } <cstr>

	// for destructors' to call when parser' stack unwinding
	// these routines are called only when error recovery by bison
	//%destructor { std::cout<<$$<<" is deleted"; delete[] $$; $$ = nullptr;  } <cstr>

%start program

%%

program: %empty
	| program statement { $2->GenCode; cParseTree.TreeFree($2); }
	;
	
statement: CleanString { $$ = pParseTree.newclean($1); }
	| '#' for identifier '=' expression to expression '\n' list '#' next { $$ = pParseTree.newfor($3, $5, $7, $9); }
	| '#' def '\n' { $$ = $2; }
	| '#' read '\n' { $$ = $2; }
	;

def: variable type { $$ = pParseTree.newdef($1, NULL); }
	| variable type ',' def { $$ = pParseTree.newdef($1, $2); }
	;

read: variable { $$ = pParseTree.newread($1, NULL); }
	| variable ',' read { $$ = pParseTree.newread($1, $3); }
	;

expression: value	{ $$ = $1 }
	| variable		{ $$ = $1 }
	| expression '+' expression { $$ = pParseTree.newnode('+', $1, $3); }
	| expression '-' expression	{ $$ = pParseTree.newnode('-', $1, $3); }
	| expression '*' expression	{ $$ = pParseTree.newnode('*', $1, $3); }
	| expression '/' expression	{ $$ = pParseTree.newnode('/', $1, $3); }
	| '(' expression ')'		{ $$ = $2; }
	| variable '=' expression { $$ = pParseTree.newasn('=', $1, $3); }
	;

list: %empty { $$ = NULL; }
	| statement list { 
		if ($2 == NULL)
			$$ = $1;
			else
			$$ = pParseTree.newnode('L', $1, $2);
		}
	;
value: constant	{ $$ = pParseTree.newnum($1); }
	| '&' variable  { $$ = $2; }
	;

variable: identifier { $$ = pParseTree.newref($1, NULL, NULL); }
	| identifier '(' expression ')' { $$ = pParseTree.newref($1, $3, NULL); }
	| identifier '(' expression ',' expression ')' { $$ = pParseTree.newref($1, $3, $5); }
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