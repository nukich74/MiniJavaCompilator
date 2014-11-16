#pragma once

#include <memory>
#include <list>
#include <Grammar.h>
#include <Exp.h>
#include <Visitor.h>

class CAssignStatement : public IStatement {
public:
	CAssignStatement( std::string& _id, IExp* _pExp1, IExp* _pExp2 ) :
		id( _id ),
		pExp1( _pExp1 ),
		pExp2( _pExp2 )
		{}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::string id;
	std::shared_ptr<IExp> pExp1;
	std::shared_ptr<IExp> pExp2;
};

class CPrintStatement : public IStatement {
public:
	CPrintStatement( IExp* _pExp ) :
		pExp( _pExp ) {}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IExp> pExp;
};

class CCurlyBraceStatement : public IStatement {
public:
	CCurlyBraceStatement( IStatementList* _pStatementList ) :
		pStatementList( _pStatementList ) {}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IStatementList> pStatementList;
};

class CIfStatement : public IStatement {
public:
	CIfStatement( IExp* _pExp, IStatement* _pStatement1, IStatement* _pStatement2 ) :
		pExp( _pExp ),
		pStatement1( _pStatement1 ),
		pStatement2( _pStatement2 ) {}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IExp> pExp;
	std::shared_ptr<IStatement> pStatement1;
	std::shared_ptr<IStatement> pStatement2;
};

class CWhileStatement: public IStatement{
public:
	CWhileStatement( IExp* _pExp, IStatement* _pStatement ) :
		pExp( _pExp ),
		pStatement( _pStatement ) {}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IExp> pExp;
	std::shared_ptr<IStatement> pStatement;
};


