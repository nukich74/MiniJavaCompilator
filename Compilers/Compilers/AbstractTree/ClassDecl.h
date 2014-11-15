#pragma once

#include <memory>
#include "Grammar.h"
#include "Exp.h"
#include "Visitor.h"

class CClassDecl : public IClassDecl {
public:
	CClassDecl( CId* _classPId, IVarDeclList* _pVarDeclList, IMethodDeclList* _pMethodDeclList, CId* _parrentPId ) :
		classPId( _classPId ),
		pVarDeclList( _pVarDeclList ),
		pMethodDeclList( _pMethodDeclList ),
		parrentPId( _parrentPId )
	{}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<CId> classPId;
	std::shared_ptr<IVarDeclList> pVarDeclList;
	std::shared_ptr<IMethodDeclList> pMethodDeclList;
	std::shared_ptr<CId> parrentPId;
};