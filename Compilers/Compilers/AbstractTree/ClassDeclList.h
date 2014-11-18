#pragma once

#include <memory>
#include <list>
#include <Grammar.h>
#include <Visitor.h>

class CClassDeclList : public IClassDeclList {
public:
	CClassDeclList( CClassDeclList* pClassDeclList, IClassDecl* _pClassDecl )
	{
		if( pClassDeclList != 0 )
		{
			classDeclList = pClassDeclList->classDeclList;
		}
		classDeclList.push_back( std::shared_ptr<IClassDecl>( _pClassDecl ) );
	}

	void accept( IVisitor& visitor ) const { visitor.visit( *this ); }

	std::list< std::shared_ptr<IClassDecl> > classDeclList;
};