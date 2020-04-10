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
};

