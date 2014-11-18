#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>

class CMainClass : public IMainClass {
public:
	CMainClass( const std::string& _id1, const std::string& _id2, IStatementList* _pStatementList ) :
		id1( _id1 ),
		id2( _id2 ),
		pStatementList( _pStatementList )
	{}

	void accept( IVisitor& visitor ) const { visitor.visit( *this ); }

	std::shared_ptr<IStatementList> pStatementList;
	std::string id1;
	std::string id2;
};