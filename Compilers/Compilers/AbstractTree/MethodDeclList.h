#pragma once

#include <memory>
#include <list>
#include "Grammar.h"
#include "Visitor.h"

class CMethodDeclList : public IMethodDeclList {
public:
	CMethodDeclList( CMethodDeclList* pMethodDeclList, IMethodDecl* _pMethodDecl ) 
	{ 
		if( pMethodDeclList != 0 )
		{
			methodDeclList = pMethodDeclList->methodDeclList;
		}
		methodDeclList.push_back( std::shared_ptr<IMethodDecl>( _pMethodDecl ) ); 
	}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::list< std::shared_ptr<IMethodDecl> > methodDeclList;
};