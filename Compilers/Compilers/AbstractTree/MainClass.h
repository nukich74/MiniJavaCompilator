#pragma once

#include <memory>
#include "Grammar.h"
#include "Visitor.h"

class CMainClass : public IMainClass {
public:
	CMainClass( CId* _pId, IStatementList* _pStatementList ) :
		pId( _pId ),
		pStatementList( _pStatementList )
	{}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IStatementList> pStatementList;
	std::shared_ptr<CId> pId;
};