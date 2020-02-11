#pragma once

struct ASTnode
{
	ASTnode* m_left;
	ASTnode* m_rigth;
	int nodetype;
};

struct FORnode
{
	const int nodetype = 'F';
	char* m_id;
	ASTnode* m_FirstIndex;
	ASTnode* m_SecondIndex;
};
struct DEFnode
{
	const int nodetype = 'D';
	ASTnode* m_variable;
	ASTnode* m_nextdef;
};
struct READnode
{
	const int nodetype = 'R';
	ASTnode* m_variable;
	ASTnode* m_nextread;
};

struct SYMnode
{
	const int nodetype = 'S';
	char* id;
	ASTnode* FirstIndex;
	ASTnode* SecondIndex;
};

struct ASNnode
{

};

struct CLEANnode
{

};