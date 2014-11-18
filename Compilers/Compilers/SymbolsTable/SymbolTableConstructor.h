// Автор: Николай Фролов.

// Описание: Класс реализующий визитор, строящий таблицу символов.

#pragma once

#include "Visitor.h"
#include "SymbolTable.h"

class CSymbolTableConstructor : public IVisitor {
public:
	CSymbolTableConstructor() { }

	SymbolsTable::CSymbolTable symbolTable;

	virtual void visit( CExpBinOpExp& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CUnMinExp& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CExpWithIndex& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CExpDotLength& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CExpIdExpList& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CExpIdVoidExpList& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CIntegerLiteral& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CTrue& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CFalse& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CId& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CThis& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CNewIntExpIndex& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CNewId& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CNotExp& exp ) { IVisitor::visit( exp ); }
	virtual void visit( CExpInBrackets& exp ) { IVisitor::visit( exp ); }
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
	virtual void visit( CStatementList& statementList ) { IVisitor::visit( statementList ); }
	virtual void visit( CAssignStatement& assignStatement ) { IVisitor::visit( assignStatement ); }
	virtual void visit( CPrintStatement& printStatement ) { IVisitor::visit( printStatement ); }
	virtual void visit( CCurlyBraceStatement& curlyBraceStatement ) { IVisitor::visit( curlyBraceStatement ); }
	virtual void visit( CIfStatement& ifStatement ) { IVisitor::visit( ifStatement ); }
	virtual void visit( CWhileStatement& whileStatement ) { IVisitor::visit( whileStatement ); }
	virtual void visit( CExpList& expList ) { IVisitor::visit( expList ); }

private:
	// Текущий класс в котором мы находимся.
	SymbolsTable::CClassDescription curClass;
	// Текущий метод в котором мы находимся. 0( IsZero == 0 ), если вне методов.
	SymbolsTable::CMethodDescription curMethod;
	// Текущая переменная, которую мы конструируем. 
	SymbolsTable::CVariableDescription curVariable;
};