// Описание: Класс, описывающий вершину AST, отвечающую набору операторов.

#pragma once

#include <memory>
#include <list>
#include "Grammar.h"
#include "Visitor.h"

class CStatementList : public IStatementList, public CLocationStorage {
public:
	CStatementList( CStatementList* pStatementList, IStatement* _pStatement, const CLocation& location ) : CLocationStorage( location )
	{
		if( pStatementList != 0 ) {
			statementList = pStatementList->statementList;
		}
		statementList.emplace_back( std::shared_ptr<IStatement>( _pStatement ) );
	}

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::list< std::shared_ptr<IStatement> >& StatmentList() const { return statementList; }

private:
	std::list< std::shared_ptr<IStatement> > statementList;
};