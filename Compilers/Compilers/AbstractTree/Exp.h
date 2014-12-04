// Описание: Классы, описывающие вершины AST, отвечающие конкретным выражениям.

#pragma once

#include "Grammar.h"
#include "Visitor.h"

class CExpBinOpExp : public IExp, public CLocationStorage {
public:
	CExpBinOpExp( IExp* _leftArg, char _operation, IExp* _rightArg, const CLocation& location ) 
		: CLocationStorage( location )
		, leftArg( _leftArg )
		, operation( _operation )
		, rightArg( _rightArg )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* LeftArg() const { return leftArg.get(); }

	const IExp* RightArg() const { return rightArg.get(); }

	char Operation() const { return operation; }

private:
	std::shared_ptr<IExp> leftArg;
	std::shared_ptr<IExp> rightArg;
	char operation;
};

class CUnMinExp : public IExp, public CLocationStorage {
public:
	CUnMinExp( IExp* _exp, const CLocation& location )
		: CLocationStorage( location )
		, exp( _exp )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return exp.get(); }

private:
	std::shared_ptr<IExp> exp;
};

class CExpWithIndex : public IExp, public CLocationStorage {
public:
	CExpWithIndex( IExp* _exp, IExp* _index, const CLocation& location ) 
		: CLocationStorage( location )
		, exp( _exp )
		, index( _index )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return exp.get(); }

	const IExp* Index() const { return index.get(); }

private:
	std::shared_ptr<IExp> exp;
	std::shared_ptr<IExp> index;
};

class CExpDotLength : public IExp, public CLocationStorage {
public:
	CExpDotLength( IExp* _exp, const CLocation& location )
		: CLocationStorage( location )
		, exp( _exp )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return exp.get(); }

private:
	std::shared_ptr<IExp> exp;
};

class CExpIdExpList : public IExp, public CLocationStorage {
public:
	CExpIdExpList( IExp* _exp, const std::string& _id, IExpList* _expList, const CLocation& location ) 
		: CLocationStorage( location )
		, exp( _exp )
		, id( _id )
		, expList( _expList )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return exp.get(); }

	const std::string& Id() const { return id; }

	const IExpList* ExpList() const { return expList.get(); }

private:
	std::shared_ptr<IExp> exp;
	std::string id;
	std::shared_ptr<IExpList> expList;
};

class CExpIdVoidExpList : public IExp, public CLocationStorage {
public:
	CExpIdVoidExpList( IExp* _exp, const std::string& _id, const CLocation& location )
		: CLocationStorage( location )
		, exp( _exp )
		, id( _id ) 
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return exp.get(); }

	const std::string& Id() const { return id; }

private:
	std::shared_ptr<IExp> exp;
	std::string id;
};

class CIntegerLiteral : public IExp, public CLocationStorage {
public:
	CIntegerLiteral( int _value, const CLocation& location ) 
		: CLocationStorage( location )
		, value( _value )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	int Value() const { return value; }

private:
	int value;
};

class CTrue : public IExp, public CLocationStorage {
public:
	CTrue( const CLocation& location ) : CLocationStorage( location )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }
};

class CFalse : public IExp, public CLocationStorage {
public:
	CFalse( const CLocation& location ) : CLocationStorage( location )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }
};

class CId : public IExp, public CLocationStorage {
public:
	CId( const std::string& _id, const CLocation& location )
		: CLocationStorage( location )
		, id( _id )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::string& Id() const { return id; }

private:
	std::string id;
};

class CThis : public IExp, public CLocationStorage {
public:
	CThis( const CLocation& location ) : CLocationStorage( location )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }
};

class CNewIntExpIndex : public IExp, public CLocationStorage {
public:
	CNewIntExpIndex( IExp* _exp, const CLocation& location )
		: CLocationStorage( location )
		, exp( _exp )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return exp.get(); }

private:
	std::shared_ptr<IExp> exp;
};

class CNewId : public IExp, public CLocationStorage {
public:
	CNewId( const std::string& _typeId, const CLocation& location )
		: CLocationStorage( location )
		, typeId( _typeId )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::string& TypeId() const { return typeId; }

private:
	std::string typeId;
};

class CNotExp : public IExp, public CLocationStorage {
public:
	CNotExp( IExp* _exp, const CLocation& location )
		: CLocationStorage( location )
		, exp( _exp )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return exp.get(); }

private:
	std::shared_ptr<IExp> exp;
};

class CExpInBrackets : public IExp, public CLocationStorage {
public:
	CExpInBrackets( IExp* _exp, const CLocation& location )
		: CLocationStorage( location )
		, exp( _exp )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return exp.get(); }

private:
	std::shared_ptr<IExp> exp;
};