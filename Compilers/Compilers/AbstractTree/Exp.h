#pragma once

#include "Grammar.h"
#include "Visitor.h"

class CExpBinOpExp : public IExp {
public:
	CExpBinOpExp( IExp* _left, char op, IExp* _right ) 
		: left(_left), operation(op), right(_right) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::shared_ptr<IExp> left;
	std::shared_ptr<IExp> right;
	char operation;
};

class CUnMinExp : public IExp {
public:
	CUnMinExp(IExp* _exp) : exp(_exp) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};

class CExpWithIndex : public IExp {
public:
	CExpWithIndex(IExp* _exp, IExp* _index) : exp(_exp), index(_index) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
	std::shared_ptr<IExp> index;
};

class CExpDotLength : public IExp {
public:
	CExpDotLength(IExp* _exp) : exp(_exp) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};

class CExpIdExpList : public IExp {
public:
	CExpIdExpList( IExp* _exp, const std::string& _id, IExpList* _expList ) 
		: exp(_exp), id(_id), expList(_expList) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
	std::string id;
	std::shared_ptr<IExpList> expList;
};

class CExpIdVoidExpList : public IExp {
public:
	CExpIdVoidExpList(IExp* _exp, const std::string& _id) : exp(_exp), id(_id) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
	std::string id;
};

class CIntegerLiteral : public IExp {
public:
	CIntegerLiteral(int _value) : value(_value) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	int value;
};

class CTrue : public IExp {
public:
	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	bool GetValue( ) { return true; };
};

class CFalse : public IExp {
public:
	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	bool GetValue( ) { return false; }
};

class CId : public IExp {
public:
	CId(std::string _value) : value(_value) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::string value;
};

class CThis : public IExp {
	void accept(IVisitor& visitor) const { visitor.visit( *this ); }
};

class CNewIntExpIndex : public IExp {
public:
	CNewIntExpIndex( IExp* _exp) : exp(_exp) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};

class CNewId : public IExp {
public:
	CNewId(const std::string& _typeId) : typeId( _typeId ) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::string typeId;
};

class CNotExp : public IExp {
public:
	CNotExp(IExp* _exp) : exp(_exp) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};

class CExpInBrackets : public IExp {
public:
	CExpInBrackets( IExp* _exp ) : exp( _exp ) {}

	void accept(IVisitor& visitor) const { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};