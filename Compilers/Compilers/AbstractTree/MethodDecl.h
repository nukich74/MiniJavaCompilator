// Описание: Класс, описывающий вершину AST, отвечающую описанию некоторого метода.

#pragma once

#include <memory>
#include <Grammar.h>
#include <Exp.h>
#include <Visitor.h>

class CMethodDecl : public IMethodDecl, public CLocationStorage {
public:
	CMethodDecl( IType* _pReturnedType, const std::string& _methodName, IFormalList* _pFormalList, IVarDeclList* _pVarDeclList,
				 IStatementList* _pStatementList, IExp* _pReturnedExp, const CLocation& location )
		: CLocationStorage( location )
		, methodName( _methodName )
		, pReturnedType( _pReturnedType )
		, pFormalList( _pFormalList )
		, pVarDeclList( _pVarDeclList )
		, pStatementList( _pStatementList )
		, pReturnedExp( _pReturnedExp )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IType* ReturnedType() const { return pReturnedType.get(); }

	const std::string& MethodName() const { return methodName; }

	const IFormalList* FormalList() const { return pFormalList.get(); }

	const IVarDeclList* VarDeclList() const { return pVarDeclList.get(); }

	const IStatementList* StatementList() const { return pStatementList.get(); }

	const IExp* ReturnedExp() const { return pReturnedExp.get(); }

private:
	std::shared_ptr<IType> pReturnedType;
	std::string methodName;
	std::shared_ptr<IFormalList> pFormalList;
	std::shared_ptr<IVarDeclList> pVarDeclList;
	std::shared_ptr<IStatementList> pStatementList;
	std::shared_ptr<IExp> pReturnedExp;
};