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

	ASTnode* NewList(ASTnode* statement, ASTnode* nextlist);
	ASTnode* NewVar(std::string id, ASTnode* FirstIndex, ASTnode* Secondindex);
	ASTnode* NewNum(double value);
	ASTnode* NewFor(std::string id, ASTnode* start, ASTnode* end, ASTnode* body);
	ASTnode* NewRead(ASTnode* variable, ASTnode* nextread);
	ASTnode* NewDef(ASTnode* variable, NUMTYPE type, ASTnode* nextdef);
	ASTnode* NewLine(std::string str, ASTnode* variable, ASTnode* nextline);
	ASTnode* NewSum(ASTnode* left, ASTnode* right);
	ASTnode* NewSub(ASTnode* left, ASTnode* right);
	ASTnode* NewProduct(ASTnode* left, ASTnode* right);
	ASTnode* NewDiv(ASTnode* left, ASTnode* right);

	SymbolTable table;
};

