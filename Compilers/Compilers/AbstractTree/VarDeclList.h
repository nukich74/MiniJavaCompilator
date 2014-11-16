#pragma once

#include <memory>
#include <list>
#include <Grammar.h>
#include <Visitor.h>

class CVarDeclList : public IVarDeclList {
public:
	CVarDeclList( CVarDeclList* pVarDeclList, IVarDecl* _pVarDecl )
	{
		if( pVarDeclList != 0 )
		{
			varDeclList = pVarDeclList->varDeclList;
		}
		varDeclList.push_back( std::shared_ptr<IVarDecl>( _pVarDecl ) );
	}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::list< std::shared_ptr<IVarDecl> > varDeclList;
};