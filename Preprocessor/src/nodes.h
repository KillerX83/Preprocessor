#pragma once
enum class NUMTYPE { INT = 0, REAL };
enum class NODETYPE { AST = 0, FOR, DEF, READ, VAR, ASN, LINE, STRING, NUM, SUM, SUB, MUL, DIV};
class ASTnode
{
public:
	double virtual Action();
};

class FORnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::FOR;
	char* m_id;
	ASTnode* m_FirstIndex;
	ASTnode* m_SecondIndex;

public:
	FORnode(char* id, ASTnode* FirstIndex, ASTnode* Secondindex);
	double Action() override;
};
class DEFnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::DEF;
	ASTnode* m_variable;
	NUMTYPE m_type;
	ASTnode* m_nextdef;

public:
	DEFnode(ASTnode* variable, NUMTYPE type, ASTnode* nextdef);
	double Action() override;
};
class READnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::READ;
	ASTnode* m_variable;
	ASTnode* m_nextread;

public:
	READnode(ASTnode* variable, ASTnode* nextread);
	double Action() override;
};

class VARnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::VAR;
	char* m_id;
	ASTnode* m_FirstIndex;
	ASTnode* m_SecondIndex;

public:
	VARnode(char* id, ASTnode* FirstIndex, ASTnode* SecondIndex);
	double Action() override;
};

class ASNnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::ASN;
	ASTnode* m_variable;
	ASTnode* m_value;

public:
	ASNnode(ASTnode* variable, ASTnode* value);
	double Action() override;
};

class LINEnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::LINE;
	char* m_str;

public:
	LINEnode(char* str);
	double Action() override;
};

class STRINGnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::STRING;
	char* m_str;

public:
	STRINGnode(char* str);
	double Action() override;
};

class NUMnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::NUM;
	double m_value;

public:
	NUMnode(double value);
	double Action() override;
};

class MATHnode : public ASTnode
{
public:
	double m_left;
	double m_right;
};

class SUMnode : public MATHnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::SUM;

public:
	SUMnode(double left, double right);
	double Action() override;
};

class SUBnode : public MATHnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::SUB;

public:
	SUBnode(double left, double right);
	double Action() override;
};

class PRODUCTnode : public MATHnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::SUM;

public:
	PRODUCTnode(double left, double right);
	double Action() override;
};

class DIVnode : public MATHnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::SUM;

public:
	DIVnode(double left, double right);
	double Action() override;
};