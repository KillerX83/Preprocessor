// Preprocessor.cpp : Defines the entry point for the console application.
//

#ifdef _DEBUG
#include "MemoryLeakTracker.h"
#endif

#include "ParseTree.h"
#include "SymbolTable.h"

#include <iostream>

CParseTree pt;
extern std::ofstream fout;

int main(int argc, char* argv[])
{
	SymbolTable::Add("LENGTH", NUMTYPE::INT);
	SymbolTable::Add("RANDINIT", NUMTYPE::INT);
	SymbolTable::SetValue("LENGTH",atoi(argv[4])); // 1000 argv[4]
	SymbolTable::SetValue("RANDINIT", atoi(argv[5])); // 11 argv[5]
	SymbolTable::SetInputFile(argv[2]);	//argv[2]
	fout.open(argv[3]);			//argv[3]
	pt.RunParser(argv[1]);		//argv[1]


	return 0;
}