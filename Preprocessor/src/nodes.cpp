#include "nodes.h"
#include "SymbolTable.h"
#include "ParseTree.h"
#include <fstream>
extern SymbolTable table;
std::ifstream fin("resources/Data.pgs");
std::ofstream fout("resources/SandBox.gps");



double FORnode::Action()
{
	for (int i = static_cast<int>(m_StartValue->Action()); i < static_cast<int>(m_EndValue->Action()); i++)
	{
		SymbolTable::SetValue(m_Id, i);
		m_Body->Action();
	}

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
	if (m_Statement != nullptr)
		m_Statement->Action();
	if (m_Nextlist != nullptr)
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
	return m_Left->Action() - m_Right->Action();
}

double SUMnode::Action()
{
	return m_Left->Action() + m_Right->Action();
}

double PRODUCTnode::Action()
{
	return m_Left->Action() * m_Right->Action();
}

double DIVnode::Action()
{
	return m_Left->Action() / m_Right->Action();
}

