#include "nodes.h"
#include "SymbolTable.h"
#include "ParseTree.h"
#include <fstream>
extern SymbolTable table;
std::ofstream fout;



double FORnode::Action()
{
	for (int i = static_cast<int>(m_StartValue->Action()); i <= static_cast<int>(m_EndValue->Action()); i++)
	{
		SymbolTable::SetValue(m_Id, i);
		m_Body->Action();
	}

	return 0.0;
}

void FORnode::Free()
{
	if (m_Body != nullptr)
	{
		m_Body->Free();
		delete m_Body;
	}
	
	if (m_EndValue != nullptr)
	{
		m_EndValue->Free();
		delete m_EndValue;
	}
	
	if (m_StartValue != nullptr)
	{
		m_StartValue->Free();
		delete m_StartValue;
	}
	
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

void DEFnode::Free()
{
	if (m_Nextdef != nullptr)
	{
		m_Nextdef->Free();
		delete m_Nextdef;
	}
	
	if (m_Variable != nullptr)
	{
		m_Variable->Free();
		delete m_Variable;
	}
	
}

double VARnode::Action()
{
	return SymbolTable::GetValue(m_Id, GetFirstIndex(), GetSecondIndex());
}

void VARnode::Free()
{
}

void VARnode::SetValue(double value)
{
	SymbolTable::SetValue(m_Id, value, GetFirstIndex(), GetSecondIndex());
}

double READnode::Action()
{
	SymbolTable::Read(static_cast<VARnode*>(m_Variable)->GetID());
	return 0.0;
}


void READnode::Free()
{
	if (m_Variable != nullptr)
	{
		m_Variable->Free();
		delete m_Variable;
	}
	
}

LINEnode::LINEnode(const std::string& str, ASTnode* variable, ASTnode* nextline)
{
	m_Nodetype = NODETYPE::LINE;
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

void LINEnode::Free()
{
	if (m_Nextline != nullptr)
	{
		m_Nextline->Free();
		delete m_Nextline;
	}
	
	if (m_Variable != nullptr)
	{
		m_Variable->Free();
		delete m_Variable;
	}
	
}

double LISTnode::Action()
{
	if (m_Statement != nullptr)
		m_Statement->Action();
	if (m_Nextlist != nullptr)
		m_Nextlist->Action();
	return 0.0;
}

void LISTnode::Free()
{
	if (m_Nextlist != nullptr)
	{
		m_Nextlist->Free();
		delete m_Nextlist;
	}
	
}

double NUMnode::Action()
{
	return m_Value;
}




void NUMnode::Free()
{
}

// MATH
double SUBnode::Action()
{
	return m_Left->Action() - m_Right->Action();
}

void SUBnode::Free()
{
	if (m_Left != nullptr)
	{
		m_Left->Free();
		delete m_Left;
	}

	if (m_Right != nullptr)
	{
		m_Right->Free();
		delete m_Right;
	}
}

double SUMnode::Action()
{
	return m_Left->Action() + m_Right->Action();
}

void SUMnode::Free()
{
	if (m_Left != nullptr)
	{
		m_Left->Free();
		delete m_Left;
	}

	if (m_Right!= nullptr)
	{
		m_Right->Free();
		delete m_Right;
	}
}

double PRODUCTnode::Action()
{
	return m_Left->Action() * m_Right->Action();
}

void PRODUCTnode::Free()
{
	if (m_Left != nullptr)
	{
		m_Left->Free();
		delete m_Left;
	}

	if (m_Right != nullptr)
	{
		m_Right->Free();
		delete m_Right;
	}
}

double DIVnode::Action()
{
	return m_Left->Action() / m_Right->Action();
}

void DIVnode::Free()
{
	if (m_Left != nullptr)
	{
		m_Left->Free();
		delete m_Left;
	}

	if (m_Right != nullptr)
	{
		m_Right->Free();
		delete m_Right;
	}
}

