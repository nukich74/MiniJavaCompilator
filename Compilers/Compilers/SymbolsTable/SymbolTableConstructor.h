// Автор: Николай Фролов.

// Описание: Класс реализующий визитор, строящий таблицу символов.

#pragma once

#include "Visitor.h"
#include "SymbolTable.h"

class CSymbolTableConstructor : public IVisitor {
public:
	SymbolsTable::CSymbolTable symbolTable;

	virtual void visit( CExpBinOpExp& exp );
	virtual void visit( CUnMinExp& exp );
	virtual void visit( CExpWithIndex& exp );
	virtual void visit( CExpDotLength& exp );
	virtual void visit( CExpIdExpList& exp );
	virtual void visit( CExpIdVoidExpList& exp );
	virtual void visit( CIntegerLiteral& exp );
	virtual void visit( CTrue& exp );
	virtual void visit( CFalse& exp );
	virtual void visit( CId& exp );
	virtual void visit( CThis& exp );
	virtual void visit( CNewIntExpIndex& exp );
	virtual void visit( CNotExp& exp );
	virtual void visit( CExpInBrackets& exp );
	virtual void visit( CProgram& program );
	virtual void visit( CMainClass& mainClass );
	virtual void visit( CClassDeclList& classDeclList );
	virtual void visit( CClassDecl& classDecl );
	virtual void visit( CVarDeclList& varDeclList );
	virtual void visit( CVarDecl& varDecl );
	virtual void visit( CMethodDeclList& methodDeclList );
	virtual void visit( CMethodDecl& methodDecl );
	virtual void visit( CFormalList& formalList );
	virtual void visit( CType& type );
	virtual void visit( CStatementList& statementList );
	virtual void visit( CAssignStatement& assignStatement );
	virtual void visit( CPrintStatement& printStatement );
	virtual void visit( CCurlyBraceStatement& curlyBraceStatement );
	virtual void visit( CIfStatement& ifStatement );
	virtual void visit( CWhileStatement& whileStatement );
	virtual void visit( CExpList& expList );

private:
	// Текущий класс в котором мы находимся.
	SymbolsTable::CClassDescription curClass;
	// Текущий метод в котором мы находимся. 0( IsZero == 0 ), если вне методов.
	SymbolsTable::CMethodDescription curMethod;
	// Текущая переменная, которую мы конструируем. 
	SymbolsTable::CVariableDescription curVariable;
};