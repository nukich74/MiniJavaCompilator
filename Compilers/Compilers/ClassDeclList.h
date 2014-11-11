#pragma once

#include <memory>
#include <list>
#include "Grammar.h"
#include "Visitor.h"

class CClassDeclList : public IClassDeclList {
public:
	CClassDeclList( IClassDecl* _pClassDecl ) { classDeclList.push_back( std::shared_ptr<IClassDecl>( _pClassDecl ) ); }

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::list< std::shared_ptr<IClassDecl> > classDeclList;
};