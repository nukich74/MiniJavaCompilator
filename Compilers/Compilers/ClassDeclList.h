#pragma once

#include <memory>
#include <list>
#include "Grammar.h"
#include "Visitor.h"

class CClassDeclList : public IMainClass {
public:
	CClassDeclList( std::shared_ptr<IClassDecl> _pClassDecl ) { classDeclList.push_back( _pClassDecl ); }

	std::list< std::shared_ptr<IClassDecl> >& GetClassDeclList() { return classDeclList; }
	void PushBack( std::shared_ptr<IClassDecl> _pClassDecl ) { classDeclList.push_back( _pClassDecl ); }

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

private:
	std::list< std::shared_ptr<IClassDecl> > classDeclList;
};