#pragma once
#define TABSIZE 100
class SymbolTable
{
	struct item {
		char* name;
		double value;
	};

	item table[TABSIZE];
};

