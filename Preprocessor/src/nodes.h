#pragma once
enum class NUMTYPE { INT = 0, REAL };
enum class NODETYPE { AST = 0, FOR, DEF, READ, VAR, ASN, LINE, LIST, STRING, NUM, SUM, SUB, MUL, DIV };
class ASTnode
{
public:
	double virtual Action() = 0;
};

class FORnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::FOR;
	std::string m_id;
	ASTnode* m_FirstIndex;
	ASTnode* m_SecondIndex;
	ASTnode* m_body;

public:
	FORnode(std::string id, ASTnode* FirstIndex, ASTnode* Secondindex, ASTnode* body) : m_id(id),
		m_FirstIndex(FirstIndex), m_SecondIndex(Secondindex),
		m_body(body) { }
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
	DEFnode(ASTnode* variable, NUMTYPE type, ASTnode* nextdef) :
		m_variable(variable), m_type(type), m_nextdef(nextdef) {}
	double Action() override;
};
class READnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::READ;
	ASTnode* m_variable;
	ASTnode* m_nextread;

public:
	READnode(ASTnode* variable, ASTnode* nextread) :
		m_variable(variable), m_nextread(nextread) {}
	double Action() override;
};

class VARnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::VAR;
	std::string m_id;
	ASTnode* m_FirstIndex;
	ASTnode* m_SecondIndex;

public:
	VARnode(std::string id, ASTnode* FirstIndex, ASTnode* SecondIndex) : m_id(id), m_FirstIndex(FirstIndex), m_SecondIndex(SecondIndex) {}
	double Action() override;
};



class LINEnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::LINE;
	std::string m_str;
	ASTnode* m_variable;
	ASTnode* m_nextline;

public:
	LINEnode(std::string str, ASTnode* variable, ASTnode* nextline) : m_str(str), m_variable(variable), m_nextline(nextline) {}
	double Action() override;
};

class LISTnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::LIST;
	ASTnode* m_statement;
	ASTnode* m_nextlist;
public:
	LISTnode(ASTnode* statement, ASTnode* nextlist) : m_statement(statement), m_nextlist(nextlist) {}
	double Action() override;
};
class NUMnode : public ASTnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::NUM;
	double m_value;

public:
	NUMnode(double value) : m_value(value) {}
	double Action() override;
};

class MATHnode : public ASTnode
{
public:
	ASTnode* m_left;
	ASTnode* m_right;
};

class SUMnode : public MATHnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::SUM;

public:
	SUMnode(ASTnode* left, ASTnode* right) : m_left(left),
		m_right(right) {}
	double Action() override;
};

class SUBnode : public MATHnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::SUB;

public:
	SUBnode(ASTnode* left ASTnode* right) : m_left(left),
		m_right(right) {}
	double Action() override;
};

class PRODUCTnode : public MATHnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::SUM;

public:
	PRODUCTnode(ASTnode* left, ASTnode* right) : m_left(left),
		m_right(right) {}
	double Action() override;
};

class DIVnode : public MATHnode
{
public:
	const NODETYPE m_nodetype = NODETYPE::SUM;

public:
	DIVnode(ASTnode* left, ASTnode* right) : m_left(left), m_right(right) {}
	double Action() override;
};