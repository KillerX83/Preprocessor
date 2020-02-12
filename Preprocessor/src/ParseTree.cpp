#include "ParseTree.h"

#include "parser.h"
#include "lexer.h"

CParseTree::CParseTree()
{
}


CParseTree::~CParseTree()
{
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

void CParseTree::TreeFree(ASTnode* start)
{
}

ASTnode* CParseTree::newnode(int nodetype, ASTnode* left, ASTnode* right)
{
	return new ASTnode(nodetype, left, right);
}

ASTnode* CParseTree::newsym(const char* id, ASTnode* FirstIndex, ASTnode* Secondindex)
{
	return new SYMnode(id, FirstIndex, Secondindex);
}

ASTnode* CParseTree::newnum(double value)
{
	return new NUMnode(value);
}

ASTnode* CParseTree::newfor(const char* id, ASTnode* start, ASTnode* end, ASTnode* body)
{
	return new FORnode(id, start, end, body);
}

ASTnode* CParseTree::newread(ASTnode* variable, ASTnode* nextread)
{
	return new READnode(variable, nextread);
}

ASTnode* CParseTree::newdef(ASTnode* variable, ASTnode* nextdef)
{
	return new DEFnode(variable, nextdef);
}

ASTnode* CParseTree::newasn(ASTnode* variable, ASTnode* value)
{
	return new ASNnode(variable, value);
}

ASTnode* CParseTree::newclean(ASTnode* clean)
{
	return new CLEANnode(clean);
}




