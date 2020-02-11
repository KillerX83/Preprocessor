// Preprocessor.cpp : Defines the entry point for the console application.
//


#include "ParseTree.h"

#include <iostream>

int main()
{
	CParseTree pt;

	pt.RunParser();

	std::cout << "Type any key"; char c = std::cin.get();

	return 0;
}