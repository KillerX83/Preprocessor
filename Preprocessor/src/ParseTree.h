#pragma once

#include <string>
#include "nodes.h"
#include <vector>
#include "SymbolTable.h"

class CParseTree
{
public:
	CParseTree();
	~CParseTree();

	int RunParser(const std::string& filename = "");

	void TreeFree(ASTnode* start);

	ASTnode* newnode(int nodetype, ASTnode* left, ASTnode* right);
	ASTnode* newsym(char* id, ASTnode* FirstIndex, ASTnode* Secondindex);
	ASTnode* newnum(double value);
	ASTnode* newfor(char* id, ASTnode* start, ASTnode* end, ASTnode* body);
	ASTnode* newread(ASTnode* variable, ASTnode* nextread);
	ASTnode* newdef(ASTnode* variable, ASTnode* nextdef);
	ASTnode* newasn(ASTnode* variable, ASTnode*	value);
	ASTnode* newclean(ASTnode* clean);

	SymbolTable table;
};

