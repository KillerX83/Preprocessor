#pragma once

#include <vector>
#include <string>
#include <iostream>

#ifndef NUMtype
#define NUMtype
enum class NUMTYPE { NONE = 0, INT, REAL };
#endif



class Data
{
public:
	Data(std::string name, NUMTYPE type)
		: m_Name(name), m_Type(type) {}
	inline const std::string& GetName() { return m_Name; }
	inline NUMTYPE GetType() { return m_Type; }
	virtual ~Data() = default;

private:
	std::string m_Name;
	NUMTYPE m_Type;
};

class Variable : public Data 
{
public:
	Variable(std::string name, NUMTYPE type)
		: Data(name, type) {} 
	~Variable() = default;

	inline void SetValue(double value) { m_Value = value; }
	inline double GetValue() { return m_Value; }

private:
	double m_Value;
};

class Array : public Data 
{
public:
	Array(std::string name, NUMTYPE type, unsigned int size)
		: Data(name, type), m_Size(size) { m_Value.resize(size); }
	~Array() = default;

	inline void SetValue(double value, int firstIndex) { m_Value[firstIndex] = value; }
	inline double GetValue(int firstIndex) { return m_Value[firstIndex]; }
	inline unsigned int GetSize() { return m_Size; }

private:
	std::vector<double> m_Value;
	unsigned int m_Size;
};

class Matrix : public Data 
{
public:
	Matrix(std::string name, NUMTYPE type, unsigned int rows, unsigned int cols)
		: Data(name, type), m_Rows(rows), m_Cols(cols)
	{
		m_Value.resize(rows);
		for (int i = 0; i < rows; i++)
		{
			m_Value[i].resize(cols);
		}
	}
	~Matrix() = default;

	inline void SetValue(double value, int firstIndex, int secondIndex) { m_Value[firstIndex][secondIndex] = value; }
	inline double GetValue(int firstIndex, int secondIndex) { return m_Value[firstIndex][secondIndex]; }
	inline unsigned int GetRows() { return m_Rows; }
	inline unsigned int GetColumns() { return m_Cols; }

private:
	std::vector<std::vector<double> > m_Value;
	unsigned int m_Rows;
	unsigned int m_Cols;
};

class SymbolTable
{
public:
	static void Add(const std::string& name, NUMTYPE type, int firstIndex = -1, int secondIndex = -1);
	static void SetValue(const std::string& name, double value, int firstIndex = -1, int secondIndex = -1);
	static double GetValue(const std::string& name, int firstIndex = -1, int secondIndex = -1);
	static void Read(const std::string& name);
	static void SetInputFile(const std::string& name);
	static void Free();

private:
	static std::vector<Data*> s_Table;
	static std::ifstream s_Input;

};