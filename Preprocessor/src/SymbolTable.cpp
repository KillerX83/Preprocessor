#include "SymbolTable.h"
#include <fstream>

std::vector<Data*> SymbolTable::s_Table;
std::ifstream SymbolTable::s_Input;

void SymbolTable::Add(const std::string& name, NUMTYPE type, int firstIndex /*= -1*/, int secondIndex /*= -1*/)
{
	if (firstIndex == -1 && secondIndex == -1)
	{
		s_Table.push_back(new Variable(name, type));
	}
	else if (firstIndex != -1 && secondIndex == -1)
	{
		s_Table.push_back(new Array(name, type, firstIndex));
	}
	else if (firstIndex != -1 && secondIndex != -1)
	{
		s_Table.push_back(new Matrix(name, type, firstIndex, secondIndex));
	}
	else
	{
		std::cout << "SymbolTable::Add(Impossible)" << std::endl;
	}

}

void SymbolTable::SetValue(const std::string& name, double value, int firstIndex, int secondIndex)
{
	for (int i = 0; i < s_Table.size(); i++)
	{
		if (s_Table[i]->GetName() == name)
		{
			if (s_Table[i]->GetType() == NUMTYPE::INT)
				value = static_cast<int>(value);
			if (firstIndex == -1 && secondIndex == -1)
			{
				static_cast<Variable*>(s_Table[i])->SetValue(value);
			}
			else if (firstIndex != -1 && secondIndex == -1)
			{
				static_cast<Array*>(s_Table[i])->SetValue(value, firstIndex);
			}
			else if (firstIndex != -1 && secondIndex != -1)
			{
				static_cast<Matrix*>(s_Table[i])->SetValue(value, firstIndex, secondIndex);
			}
			else
			{
				std::cout << "SymbolTable::SetValue(Impossible)" << std::endl;
			}
		}
	}
}

double SymbolTable::GetValue(const std::string& name, int firstIndex /*= -1*/, int secondIndex /*= -1*/)
{
	for (int i = 0; i < s_Table.size(); i++)
	{
		if (s_Table[i]->GetName() == name)
		{
			if (firstIndex == -1 && secondIndex == -1)
			{
				return static_cast<Variable*>(s_Table[i])->GetValue();
			}
			else if (firstIndex != -1 && secondIndex == -1)
			{
				return static_cast<Array*>(s_Table[i])->GetValue(firstIndex - 1);
			}
			else if (firstIndex != -1 && secondIndex != -1)
			{
				return static_cast<Matrix*>(s_Table[i])->GetValue(firstIndex - 1, secondIndex - 1);
			}
			else
			{
				std::cout << "SymbolTable::GetValue(Impossible)" << std::endl;
			}
		}
	}
}

void SymbolTable::Read(const std::string& name)
{
	for (unsigned int i = 0; i < s_Table.size(); i++)
	{
		if (s_Table[i]->GetName() == name)
		{
			if (dynamic_cast<Variable*>(s_Table[i]))
			{
				double value;
				s_Input >> value;
				static_cast<Variable*>(s_Table[i])->SetValue(value);
			}
			else if (dynamic_cast<Array*>(s_Table[i]))
			{
				Array* var = static_cast<Array*>(s_Table[i]);
				double value;
				for (int i = 0; i < var->GetSize(); i++)
				{
					s_Input >> value;
					var->SetValue(value, i);
				}
			}
			else if (dynamic_cast<Matrix*>(s_Table[i]))
			{
				Matrix* var = static_cast<Matrix*>(s_Table[i]);
				double value;
				for (int i = 0; i < var->GetRows(); i++)
				{
					for (int j = 0; j < var->GetColumns(); j++)
					{
						s_Input >> value;
						var->SetValue(value, i, j);
					}
				}
			}
			else
			{
				std::cout << "SymbolTable::Read(Impossible)" << std::endl;
			}
		}
	}
}

void SymbolTable::SetInputFile(const std::string& name)
{
	s_Input.open(name);
}

void SymbolTable::Free()
{
	for (int i = 0; i < s_Table.size(); i++)
	{
		if (s_Table[i] != nullptr)
		{
			delete s_Table[i];
		}
	}
	s_Table.clear();
}

