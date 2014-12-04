// Описание: Классы, описывающие вершины AST, отвечающие различным операторам.

#pragma once

#include <memory>
#include <list>
#include <Grammar.h>
#include <Exp.h>
#include <Visitor.h>

class CAssignStatement : public IStatement, public CLocationStorage {
public:
	CAssignStatement( const std::string& _leftId, IExp* _pIndexExp, IExp* _pRightExp, const CLocation& location ) 
		: CLocationStorage( location )
		, leftId( _leftId )
		, pIndexExp( _pIndexExp )
		, pRightExp( _pRightExp )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::string& LeftId() const { return leftId; }

	const IExp* IndexExp() const { return pIndexExp.get(); }

	const IExp* RightExp() const { return pRightExp.get(); }

private:
	std::string leftId;
	std::shared_ptr<IExp> pIndexExp;
	std::shared_ptr<IExp> pRightExp;
};

class CPrintStatement : public IStatement, public CLocationStorage {
public:
	CPrintStatement( IExp* _pExp, const CLocation& location )
		: CLocationStorage( location )
		, pExp( _pExp )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return pExp.get(); }

private:
	std::shared_ptr<IExp> pExp;
};

class CCurlyBraceStatement : public IStatement, public CLocationStorage {
public:
	CCurlyBraceStatement( IStatementList* _pStatementList, const CLocation& location )
		: CLocationStorage( location )
		, pStatementList( _pStatementList )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IStatementList* StatementList() const { return pStatementList.get(); }

private:
	std::shared_ptr<IStatementList> pStatementList;
};

class CIfStatement : public IStatement, public CLocationStorage {
public:
	CIfStatement( IExp* _pExp, IStatement* _pIfStatement, IStatement* _pElseStatement, const CLocation& location )
		: CLocationStorage( location )
		, pExp( _pExp )
		, pIfStatement( _pIfStatement )
		, pElseStatement( _pElseStatement )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return pExp.get(); }

	const IStatement* IfStatement() const { return pIfStatement.get(); }

	const IStatement* ElseStatement() const { return pElseStatement.get(); }

private:
	std::shared_ptr<IExp> pExp;
	std::shared_ptr<IStatement> pIfStatement;
	std::shared_ptr<IStatement> pElseStatement;
};

class CWhileStatement: public IStatement, public CLocationStorage {
public:
	CWhileStatement( IExp* _pExp, IStatement* _pStatement, const CLocation& location )
		: CLocationStorage( location )
		, pExp( _pExp )
		, pStatement( _pStatement )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IExp* Exp() const { return pExp.get(); }

	const IStatement* Statement() const { return pStatement.get(); }

private:
	std::shared_ptr<IExp> pExp;
	std::shared_ptr<IStatement> pStatement;
};


