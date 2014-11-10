#pragma once

#include <memory>
#include "Grammar.h"
#include "Visitor.h"

class CClassDecl : public IClassDecl {
public:
	CClassDecl( std::shared_ptr<IVarDeclList> _pVarDeclList, std::shared_ptr<IMethodDeclList> _pMethodDeclList ) :
		pVarDeclList( _pVarDeclList ),
		pMethodDeclList( _pMethodDeclList )
	{}

	std::shared_ptr<IVarDeclList> GetVarDeclList() { return pVarDeclList; }
	std::shared_ptr<IMethodDeclList> GetMethodDeclList() { return pMethodDeclList; }

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

private:
	std::shared_ptr<IVarDeclList> pVarDeclList;
	std::shared_ptr<IMethodDeclList> pMethodDeclList;
};