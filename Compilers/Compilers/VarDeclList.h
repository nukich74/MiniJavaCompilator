#pragma once

#include <memory>
#include <list>
#include "Grammar.h"
#include "Visitor.h"

class CVarDeclList : public IVarDeclList {
public:
	CVarDeclList( std::shared_ptr<IVarDecl> _pVarDecl ) { varDeclList.push_back( _pVarDecl ); }

	std::list< std::shared_ptr<IVarDecl> >& GetVarDeclList( ) { return varDeclList; }
	void PushBack( std::shared_ptr<IVarDecl> _pVarDecl ) { varDeclList.push_back( _pVarDecl ); }

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

private:
	std::list< std::shared_ptr<IVarDecl> > varDeclList;
};