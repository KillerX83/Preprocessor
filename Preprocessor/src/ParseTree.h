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

	void SayHello(char* const msg) const;

	void copy_cstr(char** pTarget, const char* pSource);
	void copy_int(int& Target, const char* pSource);

	ASTnode* newnode(int nodetype, ASTnode* left, ASTnode* right);
};

