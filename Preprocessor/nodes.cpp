#include "nodes.h"
#include "SymbolTable.h"

ASTnode::ASTnode(int nodetype, ASTnode* m_left, ASTnode* m_right)
{
	this->nodetype = nodetype;
	this->m_left = m_left;
	this->m_rigth = m_rigth;
}
