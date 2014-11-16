#pragma once

#include <memory>
#include <Grammar.h>
#include <Exp.h>
#include <Visitor.h>

class CMethodDecl : public IMethodDecl {
public:
	CMethodDecl( IType* _pType, std::string& _id, IFormalList* _pFormalList, IVarDeclList* _pVarDeclList, IStatementList* _pStatementList,
		IExp* _pExp ) :
		id( _id ),
		pType( _pType ),
		pFormalList( _pFormalList ),
		pVarDeclList( _pVarDeclList ),
		pStatementList( _pStatementList ),
		pExp( _pExp )
	{}


	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IType> pType;
	std::string id;
	std::shared_ptr<IFormalList> pFormalList;
	std::shared_ptr<IVarDeclList> pVarDeclList;
	std::shared_ptr<IStatementList> pStatementList;
	std::shared_ptr<IExp> pExp;
};