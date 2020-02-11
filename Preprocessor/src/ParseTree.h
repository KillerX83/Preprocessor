#pragma once
#include <string>
#include "nodes.h"
#include <vector>

class CParseTree
{
public:
	CParseTree();
	~CParseTree();

	int RunParser(const std::string& filename = "");

	void TreeFree(ASTnode* start);

	ASTnode* newnode(int nodetype, ASTnode* left, ASTnode* right);
	ASTnode* newsym(const char* id, ASTnode* FirstIndex, ASTnode* Secondindex);
	ASTnode* newnum(double value);
	ASTnode* newfor(const char* id, ASTnode* start, ASTnode* end, ASTnode* body);
	ASTnode* newread(ASTnode* variable, ASTnode* nextread);
	ASTnode* newdef(ASTnode* variable, ASTnode* nextdef);
	ASTnode* newasn(ASTnode* variable, ASTnode*	value);
	ASTnode* newclean(ASTnode* clean);
};

