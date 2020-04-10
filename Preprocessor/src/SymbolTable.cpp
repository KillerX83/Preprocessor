#include "SymbolTable.h"

std::vector<Data*> SymbolTable::m_Table = std::vector<Data*>();

void SymbolTable::Add(const std::string& name, NUMTYPE type, int firstIndex /*= -1*/, int secondIndex /*= -1*/)
{
	if (firstIndex == -1 && secondIndex == -1)
	{
		m_Table.push_back(new Variable(name, type));
	}
	else if (firstIndex != -1 && secondIndex == -1)
	{
		m_Table.push_back(new Array(name, type, firstIndex));
	}
	else if (firstIndex != -1 && secondIndex != -1)
	{
		m_Table.push_back(new Matrix(name, type, firstIndex, secondIndex));
	}
	else
	{
		std::cout << "SymbolTable::Add(Impossible)" << std::endl;
	}

}

void SymbolTable::SetValue(const std::string& name, double value, int firstIndex, int secondIndex)
{
	for (int i = 0; i < m_Table.size(); i++)
	{
		if (m_Table[i]->GetName() == name)
		{
			if (m_Table[i]->GetType() == NUMTYPE::INT)
				value = static_cast<int>(value);
			if (firstIndex == -1 && secondIndex == -1)
			{
				static_cast<Variable*>(m_Table[i])->SetValue(value);
			}
			else if (firstIndex != -1 && secondIndex == -1)
			{
				static_cast<Array*>(m_Table[i])->SetValue(value, firstIndex);
			}
			else if (firstIndex != -1 && secondIndex != -1)
			{
				static_cast<Matrix*>(m_Table[i])->SetValue(value, firstIndex, secondIndex);
			}
			else
			{
				std::cout << "SymbolTable::SetValue(Impossible)" << std::endl;
			}
		}
	}
}

int SymbolTable::GetValue(const std::string& name, int firstIndex /*= -1*/, int secondIndex /*= -1*/)
{
	for (int i = 0; i < m_Table.size(); i++)
	{
		if (m_Table[i]->GetName() == name)
		{
			if (firstIndex == -1 && secondIndex == -1)
			{
				return static_cast<Variable*>(m_Table[i])->GetValue();
			}
			else if (firstIndex != -1 && secondIndex == -1)
			{
				return static_cast<Array*>(m_Table[i])->GetValue(firstIndex);
			}
			else if (firstIndex != -1 && secondIndex != -1)
			{
				return static_cast<Matrix*>(m_Table[i])->GetValue(firstIndex, secondIndex);
			}
			else
			{
				std::cout << "SymbolTable::GetValue(Impossible)" << std::endl;
			}
		}
	}
}
