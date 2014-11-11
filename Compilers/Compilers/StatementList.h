#pragma once

#include <memory>
#include <list>
#include "Grammar.h"
#include "Visitor.h"

class CStatementList : public IStatementList {
public:
	CStatementList( CStatementList* pStatementList, IStatement* _pStatement )
	{
		if( pStatementList != 0 )
		{
			statementList = pStatementList->statementList;
		}
		statementList.push_back( std::shared_ptr<IStatement>( _pStatement ) );
	}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::list< std::shared_ptr<IStatement> > statementList;
};