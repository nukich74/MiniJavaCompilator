#pragma once

#include <memory>
#include "Grammar.h"
#include "Visitor.h"

class CMainClass : public IMainClass {
public:
	CMainClass( IStatementList* _pStatementList ) :
		pStatementList( _pStatementList )
	{}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IStatementList> pStatementList;
};