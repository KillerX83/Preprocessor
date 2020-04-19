// Preprocessor.cpp : Defines the entry point for the console application.
//


#include "ParseTree.h"
#include "SymbolTable.h"

#include <iostream>

CParseTree pt;
extern std::ofstream fout;

int main(int argc, char* argv[])
{
	SymbolTable::Add("LENGTH", NUMTYPE::INT);
	SymbolTable::Add("RANDINIT", NUMTYPE::INT);
	SymbolTable::SetValue("LENGTH", 6); // 1000 argv[4]
	SymbolTable::SetValue("RANDINIT", 1000); // 11 argv[5]
	SymbolTable::SetInputFile("resources/Data.pgs");	//argv[2]
	fout.open("resources/SandBox.gps");			//argv[3]
	pt.RunParser("resources/SandBox.pgs");		//argv[1]


	return 0;
}