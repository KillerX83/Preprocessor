#include "nodes.h"
#include "SymbolTable.h"
#include "ParseTree.h"
#include <fstream>
extern SymbolTable table;
std::ifstream fin("resources/Data.pgs");
std::ofstream fout("resources/SandBox.gps");



double FORnode::Action()
{
	return 0.0;
}

double DEFnode::Action()
{

	static_cast<VARnode*>(m_Variable)->SetType(m_Type);
	SymbolTable::Add(static_cast<VARnode*>(m_Variable)->GetID(), static_cast<VARnode*>(m_Variable)->GetType(),
		static_cast<VARnode*>(m_Variable)->GetFirstIndex(), static_cast<VARnode*>(m_Variable)->GetSecondIndex());
	if (m_Nextdef != nullptr)
		m_Nextdef->Action();
	return 0.0;
}

double VARnode::Action()
{
	return SymbolTable::GetValue(m_Id, GetFirstIndex(), GetSecondIndex());
}

void VARnode::SetValue(double value)
{
	SymbolTable::SetValue(m_Id, value, GetFirstIndex(), GetSecondIndex());
}

double READnode::Action()
{
	double value;
	fin >> value;
	static_cast<VARnode*>(m_Variable)->SetValue(value);
	return 0.0;
}


LINEnode::LINEnode(const std::string& str, ASTnode* variable, ASTnode* nextline)
{
	m_Str = str;
	m_Variable = variable;
	m_Nextline = nextline;

}

double LINEnode::Action()
{
	fout << m_Str;
	if (m_Variable != nullptr)
		fout << m_Variable->Action();
	if (m_Nextline != nullptr)
		m_Nextline->Action();
	return 0.0;
}

double LISTnode::Action()
{
	m_Statement->Action();
	m_Nextlist->Action();
	return 0.0;
}

double NUMnode::Action()
{
	return m_Value;
}




// MATH
double SUBnode::Action()
{
	return 0.0;
}

double SUMnode::Action()
{
	return 0.0;
}

double PRODUCTnode::Action()
{
	return 0.0;
}

double DIVnode::Action()
{
	return 0.0;
}

