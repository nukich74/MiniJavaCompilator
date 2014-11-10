#pragma once

#include <memory>
#include "Grammar.h"
#include "Visitor.h"

class CMainClass : public IMainClass {
public:
	CMainClass( std::shared_ptr<IStatementList> _pStatementList ) :
		pStatementList( _pStatementList )
	{}

	std::shared_ptr<IStatementList> GetStatementList() { return pStatementList; }

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

private:
	std::shared_ptr<IStatementList> pStatementList;
};