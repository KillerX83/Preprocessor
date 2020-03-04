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

ASTnode* CParseTree::NewList(ASTnode* statement, ASTnode* nextlist)
{
	LISTnode* node = new LISTnode(statement, nextlist);
	return (ASTnode*)node;
}

ASTnode* CParseTree::NewVar(std::string id, ASTnode* FirstIndex, ASTnode* Secondindex)
{
	VARnode* node = new VARnode(id, FirstIndex, Secondindex);
	return (ASTnode*)node
}

ASTnode* CParseTree::NewNum(double value)
{
	NUMnode* node = new NUMnode(value);
	return (ASTnode*)node;
}

ASTnode* CParseTree::NewFor(std::string id, ASTnode* start, ASTnode* end, ASTnode* body)
{
	FORnode* node = new FORnode(id, start, end, body);
	return (ASTnode*)node;
}

ASTnode* CParseTree::NewRead(ASTnode* variable, ASTnode* nextread)
{
	READnode* node = new READnode(variable, nextread);
	return (ASTnode*)node;
}

ASTnode* CParseTree::NewDef(ASTnode* variable, NUMTYPE type, ASTnode* nextdef)
{
	DEFnode* node = new DEFnode(variable, type, nextread);
	return (ASTnode*)node;
}

ASTnode* CParseTree::NewLine(std::string str, ASTnode* variable, ASTnode* nextline)
{
	LINEnode* node = new LINEnode(str, variable, nextline);
	return (ASTnode*)node;
}

ASTnode* CParseTree::NewSum(ASTnode* left, ASTnode* right)
{
	SUMnode* node = new SUMnode(left, right);
	return (ASTnode*)node;
}

ASTnode* CParseTree::NewSub(ASTnode* left, ASTnode* right)
{
	SUBnode* node = new SUBnode(left, right);
	return (ASTnode*)node;
}

ASTnode* CParseTree::NewProduct(ASTnode* left, ASTnode* right)
{
	PRODUCTnode* node = new PRODUCTnode(left, right);
	return (ASTnode*)node;
}

ASTnode* CParseTree::NewDiv(ASTnode* left, ASTnode* right)
{
	DIVnode* node = new DIVnode(left, right);
	return (ASTnode*)node;
}

