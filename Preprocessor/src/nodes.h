#pragma once

#include <string>
#include <fstream>



#ifndef NUMtype
#define NUMtype
enum class NUMTYPE { NONE = 0, INT, REAL };
#endif

enum class NODETYPE { AST = 0, FOR, DEF, READ, VAR, ASN, LINE, LIST, STRING, NUM, SUM, SUB, MUL, DIV };


class ASTnode
{
public:
	virtual ~ASTnode() = default;

	double virtual Action() { return 0.0; }
	
};

class FORnode : public ASTnode
{
public:
	FORnode(const std::string& id, ASTnode* startValue , ASTnode* endValue, ASTnode* body)
		: m_Id(id), m_StartValue(startValue), m_EndValue(endValue), m_Body(body) { }

	double Action() override;

private:
	const NODETYPE m_Nodetype = NODETYPE::FOR;
	std::string m_Id;
	ASTnode* m_StartValue;
	ASTnode* m_EndValue;
	ASTnode* m_Body;
};
class DEFnode : public ASTnode
{
public:
	DEFnode(ASTnode* variable, NUMTYPE type, ASTnode* nextdef) :
		m_Variable(variable), m_Type(type), m_Nextdef(nextdef) {}

	double Action() override;

private:
	const NODETYPE m_Nodetype = NODETYPE::DEF;
	ASTnode* m_Variable;
	NUMTYPE m_Type;
	ASTnode* m_Nextdef;
};
class READnode : public ASTnode
{
public:
	READnode(ASTnode* variable, ASTnode* nextread) :
		m_Variable(variable), m_Nextread(nextread) {}

	double Action() override;
	

private:
	const NODETYPE m_Nodetype = NODETYPE::READ;
	ASTnode* m_Variable;
	ASTnode* m_Nextread;
};

class VARnode : public ASTnode
{
public:
	VARnode(const std::string& id, ASTnode* FirstIndex, ASTnode* SecondIndex) 
		: m_Id(id), m_FirstIndex(FirstIndex), m_SecondIndex(SecondIndex) {}

	inline NUMTYPE GetType() { return m_Type; }
	inline void SetType(NUMTYPE type) { m_Type = type; }
	inline void SetValue(double value);
	inline const std::string& GetID() { return m_Id; }
	inline double GetFirstIndex() { if (m_FirstIndex == nullptr) return -1; return m_FirstIndex->Action(); }
	inline double GetSecondIndex() { if (m_SecondIndex == nullptr) return -1; return m_SecondIndex->Action(); }

	double Action() override;
	
private:
	const NODETYPE m_Nodetype = NODETYPE::VAR;
	NUMTYPE m_Type = NUMTYPE::NONE;
	std::string m_Id;
	ASTnode* m_FirstIndex;
	ASTnode* m_SecondIndex;
};



class LINEnode : public ASTnode
{
public:
	LINEnode(const std::string& str, ASTnode* variable, ASTnode* nextline);

	double Action() override;

private:
	const NODETYPE m_Nodetype = NODETYPE::LINE;
	std::string m_Str;
	ASTnode* m_Variable;
	ASTnode* m_Nextline;
};

class LISTnode : public ASTnode
{
public:
	LISTnode(ASTnode* statement, ASTnode* nextlist) 
		: m_Statement(statement), m_Nextlist(nextlist) {}

	double Action() override;

private:
	const NODETYPE m_Nodetype = NODETYPE::LIST;
	ASTnode* m_Statement;
	ASTnode* m_Nextlist;
};
class NUMnode : public ASTnode
{
public:
	NUMnode(double value, NUMTYPE type) : 
		m_Value(value), m_Type(type) {
		if (m_Type == NUMTYPE::INT) m_Value = static_cast<int>(m_Value); }

	double Action() override;
	
private:
	const NODETYPE m_Nodetype = NODETYPE::NUM;
	double m_Value;
	NUMTYPE m_Type;
};


class SUMnode : public ASTnode
{
public:
	SUMnode(ASTnode* left, ASTnode* right)
		: m_Left(left), m_Right(right) {}

	double Action() override;

private:
	const NODETYPE m_nodetype = NODETYPE::SUM;
	ASTnode* m_Left;
	ASTnode* m_Right;

};

class SUBnode : public ASTnode
{
public:
	SUBnode(ASTnode* left, ASTnode* right) 
		: m_Left(left), m_Right(right) {}
	double Action() override;

private:
	const NODETYPE m_nodetype = NODETYPE::SUB;
	ASTnode* m_Left;
	ASTnode* m_Right;

};

class PRODUCTnode : public ASTnode
{
public:
	PRODUCTnode(ASTnode* left, ASTnode* right) 
		: m_Left(left), m_Right(right) {}

	double Action() override;

private:
	const NODETYPE m_nodetype = NODETYPE::SUM;
	ASTnode* m_Left;
	ASTnode* m_Right;

};

class DIVnode : public ASTnode
{
public:
	DIVnode(ASTnode* left, ASTnode* right) 
		: m_Left(left), m_Right(right) {}

	double Action() override;

private:
	const NODETYPE m_nodetype = NODETYPE::SUM;
	ASTnode* m_Left;
	ASTnode* m_Right;
};