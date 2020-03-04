#pragma once

#include <vector>

enum class NUMTYPE { INT = 0, REAL };

class SymbolTable
{
	vector<Data> table;

	void add(std::string name, int FirstIndex = -1, int SecondIndex = -1);
	int search(std::string name, int FirstIndex = -1, int SecondIndex = -1);
};

class Data
{
	std::string m_name;
	NUMTYPE type;
	Data(std::string name, NUMTYPE type);
};

class Variable : public Data 
{
	double m_value;
	Variable(std::string name, NUMTYPE type);
};

class Array : public Data 
{
	std::vector<double> m_value;
	Array(std::string name, NUMTYPE type, double size);
};

class Matrix : public Data 
{
	std::vector<std::vector<double> > m_value;
	Matrix(std::string name, NUMTYPE type, double rows, double cols);
};
