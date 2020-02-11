#pragma once

class ASTnode
{
private:

public:
	ASTnode(int nodetype, ASTnode* m_left, ASTnode* m_right);

	ASTnode* m_left;
	ASTnode* m_right;
	int nodetype;
};