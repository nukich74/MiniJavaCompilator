#pragma once

#include "Visitor.h"
#include "Grammar.h"

class CExpBinOpExp : public IExp {
public:
	CExpBinOpExp( IExp* _left, char op, IExp* _right ) 
		: left(_left), operation(op), right(_right) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> left;
	std::shared_ptr<IExp> right;
	char operation;
};

class CUnMinExp : public IExp {
public:
	CUnMinExp(IExp* _exp) : exp(_exp) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};

class CExpWithIndex : public IExp {
public:
	CExpWithIndex(IExp* _exp, IExp* _index) : exp(_exp), index(_index) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
	std::shared_ptr<IExp> index;
};

class CExpDotLength : public IExp {
public:
	CExpDotLength(IExp* _exp) : exp(_exp) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};

class CExpIdExpList : public IExp {
public:
	CExpIdExpList( IExp* _exp, IExp* _id, IExpList* _expList ) 
		: exp(_exp), id(_id), expList(_expList) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
	std::shared_ptr<IExp> id;
	std::shared_ptr<IExpList> expList;
};

class CExpIdVoidExpList : public IExp {
public:
	CExpIdVoidExpList(IExp* _exp, IExp* _id) : exp(_exp), id(_id) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
	std::shared_ptr<IExp> id;
};

class CIntegerLiteral : public IExp {
public:
	CIntegerLiteral(int _value) : value(_value) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	int value;
};

class CTrue : public IExp {
public:
	void accept(IVisitor& visitor) { visitor.visit(*this); }
	bool GetValue( ) { return true; };
};

class CFalse : public IExp {
public:
	void accept(IVisitor& visitor) { visitor.visit(*this); }
	bool GetValue( ) { return false; }
};

class CId : public IExp {
public:
	CId(std::string _value) : value(_value) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::string value;
};
//пока не понятно что тут должно быть
class CThis : public IExp {};

class CNewIntExpIndex : public IExp {
public:
	CNewIntExpIndex(std::shared_ptr<IExp> _exp) : exp(_exp) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};

class CNewId : public IExp {
public:
	CNewId(IType* _type) : type(_type) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IType> type;
};

class CNotExp : public IExp {
public:
	CNotExp(std::shared_ptr<IExp> _exp) : exp(_exp) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};

class CExpInBrackets : public IExp {
public:
	CExpInBrackets( std::shared_ptr<IExp> _exp ) : exp( _exp ) {}

	void accept(IVisitor& visitor) { visitor.visit(*this); }
	std::shared_ptr<IExp> exp;
};