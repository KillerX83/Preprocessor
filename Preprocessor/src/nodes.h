#pragma once
extern enum class TYPE;
class ASTnode
{
public:
	ASTnode* m_left;
	ASTnode* m_rigth;
	int m_nodetype;

public:
	ASTnode(int nodetype, ASTnode* left, ASTnode* rigth);
	void virtual Action();
};

class FORnode : public ASTnode
{
public:
	const int m_nodetype = 'F';
	char* m_id;
	ASTnode* m_FirstIndex;
	ASTnode* m_SecondIndex;

public:
	FORnode(const char* id, ASTnode* FirstIndex, ASTnode* Secondindex);
	void Action() override;
};
class DEFnode : public ASTnode
{
public:
	const int m_nodetype = 'D';
	ASTnode* m_variable;
	TYPE m_type;
	ASTnode* m_nextdef;

public:
	DEFnode(ASTnode* variable, TYPE type, ASTnode* nextdef);
	void Action() override;
};
class READnode : public ASTnode
{
public:
	const int m_nodetype = 'R';
	ASTnode* m_variable;
	ASTnode* m_nextread;

public:
	READnode(ASTnode* variable, ASTnode* nextread);
	void Action() override;
};

class SYMnode : public ASTnode
{
public:
	const int m_nodetype = 'S';
	char* m_id;
	ASTnode* m_FirstIndex;
	ASTnode* m_SecondIndex;

public:
	SYMnode(char* id, ASTnode* FirstIndex, ASTnode* SecondIndex);
	void Action() override;
};

class ASNnode : public ASTnode
{
public:
	const int m_nodetype = 'A';
	ASTnode* m_variable;
	ASTnode* m_value;

public:
	ASNnode(ASTnode* variable, ASTnode* value);
	void Action() override;
};

class CLEANnode : public ASTnode
{
public:
	const int m_nodetype = 'C';
	char* m_str;

public:
	CLEANnode(char* str);
	void Action() override;
};

class NUMnode : public ASTnode
{
public:
	const int m_nodetype = 'N';
	double m_value;

public:
	NUMnode(double value);
	void Action() override;
};