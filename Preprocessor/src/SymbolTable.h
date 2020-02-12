#pragma once
#define TABSIZE 100
#include <vector>
class SymbolTable
{
	vector<Data> table;

	void add(char* name, int FirstIndex = -1, int SecondIndex = -1);
	int search(char* name, int FirstIndex = -1, int SecondIndex = -1);
};

class Data
{
	char* m_name;
	Data(char* name);
};

class Variable : public Data 
{
	double m_value;
	Variable(char* name);
};

class Array : public Data 
{
	std::vector<double> m_value;
	Array(char* name, double size);
};

class Matrix : public Data 
{
	std::vector<std::vector<double> > m_value;
	Matrix(char* name, double rows, double cols);
};
