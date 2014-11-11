#pragma once

#include <memory>
#include <list>
#include "Grammar.h"
#include "Visitor.h"

class CMethodDeclList : public IMethodDeclList {
public:
	CMethodDeclList( std::shared_ptr<IMethodDecl> _pMethodDecl ) { methodDeclList.push_back( _pMethodDecl ); }

	std::list< std::shared_ptr<IMethodDecl> >& GetMethodDeclList() { return methodDeclList; }
	void PushBack( std::shared_ptr<IMethodDecl> _pMethodDecl ) { methodDeclList.push_back( _pMethodDecl ); }

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

private:
	std::list< std::shared_ptr<IMethodDecl> > methodDeclList;
};