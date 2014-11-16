#pragma once

#include <memory>
#include "Grammar.h"
#include "Visitor.h"

class CMainClass : public IMainClass {
public:
	CMainClass( CId* _pId1, CId* _pid2, IStatementList* _pStatementList ) :
		pId1( _pId1 ),
		pId2( _pid2 ),
		pStatementList( _pStatementList )
	{}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IStatementList> pStatementList;
	std::shared_ptr<CId> pId1;
	std::shared_ptr<CId> pId2;
};