#include "nodes.h"
#include "SymbolTable.h"
#include "ParseTree.h"

extern CParseTree pt;
ASTnode::ASTnode(int nodetype, ASTnode* left, ASTnode* rigth)
{
	m_left = left;
	m_rigth = rigth;
	m_nodetype = nodetype;
}

FORnode::FORnode(const char* id, ASTnode* FirstIndex, ASTnode* Secondindex)
{
	m_id = id;
	m_FirstIndex = FirstIndex;
	m_SecondIndex = Secondindex;
}

DEFnode::DEFnode(ASTnode* variable, TYPE type, ASTnode* nextdef)
{
	m_variable = variable;
	m_type = type;
	m_nextdef = nextdef;
}

READnode::READnode(ASTnode* variable, ASTnode* nextread)
{
	m_variable = variable;
	m_nextread = nextread;
}

CLEANnode::CLEANnode(char* str)
{
	m_str = str;
}

NUMnode::NUMnode(double value)
{
	m_value = value;
}

SYMnode::SYMnode(char* id, ASTnode* FirstIndex, ASTnode* SecondIndex)
{
	if (pt.table.search(id) == -1)
		pt.table.add(id, FirstIndex, SecondIndex);
	m_id = id;
	m_FirstIndex = FirstIndex;
	m_SecondIndex = SecondIndex;
}

ASNnode::ASNnode(ASTnode* variable, ASTnode* value)
{
	m_variable = variable;
	m_value = value;
}