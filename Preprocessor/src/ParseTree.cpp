#include "ParseTree.h"

#include "parser.h"
#include "lexer.h"

CParseTree::CParseTree()
{
}


CParseTree::~CParseTree()
{
}

void CParseTree::SayHello(char* const msg) const
{
	std::cout << "Msg from CParseTree: " << msg << std::endl;
}
int CParseTree::RunParser(const std::string& filename)
{
	int rlt;

	try
	{
		yyscan_t scanner;

		FILE *in = nullptr;  errno_t er;

		if (filename != "")
			er = fopen_s(&in, filename.c_str(), "r");
		else
			in = stdin;

		yylex_init_extra(this, &scanner);
		yyset_in(in, scanner);

		rlt = yyparse(scanner, this);

		yylex_destroy(scanner);

		if (in != nullptr)
		{
			fclose(in);
			in = nullptr;
		}
	}
	catch (std::exception&)
	{

	}

	return rlt;
}


void CParseTree::copy_cstr(char** pTarget, const char* pSource)
{
	size_t size = strlen(pSource) + 1;
	*pTarget = new char[size];
	strcpy_s(*pTarget, size, pSource);
}

void CParseTree::copy_int(int& Target, const char* pSource)
{
	Target = atoi(pSource);
}
