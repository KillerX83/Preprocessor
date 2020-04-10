// Preprocessor.cpp : Defines the entry point for the console application.
//


#include "ParseTree.h"
#include "SymbolTable.h"

#include <iostream>

CParseTree pt;


int main()
{

	pt.RunParser("resources/Demon.pgs");

	std::cout << "Type any key"; char c = std::cin.get();

	return 0;
}