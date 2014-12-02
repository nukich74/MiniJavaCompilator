// Автор: Воротилов Владислав
// Визитор для построения дерева промежуточного представления

#pragma once 
#include "Visitor.h"
#include "IRTree.h"

namespace Translate {

class CIRTreeVisitor : public IVisitor {
public:

	CIRTree

	virtual void visit(const CExpBinOpExp& exp);
	virtual void visit(const CUnMinExp& exp);
	virtual void visit(const CExpWithIndex& exp);
	virtual void visit(const CExpDotLength& exp);
	virtual void visit(const CExpIdExpList& exp);
	virtual void visit(const CExpIdVoidExpList& exp);
	virtual void visit(const CIntegerLiteral& exp);
	virtual void visit(const CTrue& exp);
	virtual void visit(const CFalse& exp);
	virtual void visit(const CId& exp);
	virtual void visit(const CThis& exp);
	virtual void visit(const CNewIntExpIndex& exp);
	virtual void visit(const CNewId& exp);
	virtual void visit(const CNotExp& exp);
	virtual void visit(const CExpInBrackets& exp);
	virtual void visit(const CProgram& program);
	virtual void visit(const CMainClass& mainClass);
	virtual void visit(const CClassDeclList& classDeclList);
	virtual void visit(const CClassDecl& classDecl);
	virtual void visit(const CVarDeclList& varDeclList);
	virtual void visit(const CVarDecl& varDecl);
	virtual void visit(const CMethodDeclList& methodDeclList);
	virtual void visit(const CMethodDecl& methodDecl);
	virtual void visit(const CFormalList& formalList);
	virtual void visit(const CType& type);
	virtual void visit(const CStatementList& statementList);
	virtual void visit(const CAssignStatement& assignStatement);
	virtual void visit(const CPrintStatement& printStatement);
	virtual void visit(const CCurlyBraceStatement& curlyBraceStatement);
	virtual void visit(const CIfStatement& ifStatement);
	virtual void visit(const CWhileStatement& whileStatement);
	virtual void visit(const CExpList& expList);
};

} // namespace Translate