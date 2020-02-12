#include "SymbolTable.h"


void SymbolTable::add(char* name, int FirstIndex, int SecondIndex)
{
	if (FirstIndex > 0)
	{
		if (SecondIndex > 0)
			table.push_back(new Matrix(name, FirstIndex, SecondIndex) );
		else 
			table.push_back(new Array(name, FirstIndex) );
	}
	else
		table.push_back(new Variable(name));
}

int SymbolTable::search(char* name, int FirstIndex /* = -1 */, int SecondIndex /* = -1 */)
{
	for (int i = 0; i < table.size(); i++)
	{
		if (table[i].m_name == name)
			return i;
	}
	return -1;
}