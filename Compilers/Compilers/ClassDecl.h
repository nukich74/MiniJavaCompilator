#pragma once

#include <memory>
#include "Grammar.h"
#include "Exp.h"
#include "Visitor.h"

class CClassDecl : public IClassDecl {
public:
	CClassDecl( CId* _pId, IVarDeclList* _pVarDeclList, IMethodDeclList* _pMethodDeclList ) :
		pId( _pId ),
		pVarDeclList( _pVarDeclList ),
		pMethodDeclList( _pMethodDeclList )
	{}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<CId> pId;
	std::shared_ptr<IVarDeclList> pVarDeclList;
	std::shared_ptr<IMethodDeclList> pMethodDeclList;
};