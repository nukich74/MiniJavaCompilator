// Автор: Николай Фролов.

// Описание: Класс реализующий визитор, строящий таблицу символов.

#pragma once

#include "Visitor.h"
#include "SymbolTable.h"

class CSymbolTableConstructor : public IVisitor {
public:
	CSymbolTableConstructor() { }

	SymbolsTable::CSymbolTable symbolTable;

	virtual void visit( const CExpBinOpExp& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CUnMinExp& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CExpWithIndex& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CExpDotLength& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CExpIdExpList& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CExpIdVoidExpList& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CIntegerLiteral& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CTrue& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CFalse& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CId& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CThis& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CNewIntExpIndex& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CNewId& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CNotExp& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CExpInBrackets& exp ) { IVisitor::visit( exp ); }
	virtual void visit( const CProgram& program );
	virtual void visit( const CMainClass& mainClass );
	virtual void visit( const CClassDeclList& classDeclList );
	virtual void visit( const CClassDecl& classDecl );
	virtual void visit( const CVarDeclList& varDeclList );
	virtual void visit( const CVarDecl& varDecl );
	virtual void visit( const CMethodDeclList& methodDeclList );
	virtual void visit( const CMethodDecl& methodDecl );
	virtual void visit( const CFormalList& formalList );
	virtual void visit( const CType& type );
	virtual void visit( const CStatementList& statementList ) { IVisitor::visit( statementList ); }
	virtual void visit( const CAssignStatement& assignStatement ) { IVisitor::visit( assignStatement ); }
	virtual void visit( const CPrintStatement& printStatement ) { IVisitor::visit( printStatement ); }
	virtual void visit( const CCurlyBraceStatement& curlyBraceStatement ) { IVisitor::visit( curlyBraceStatement ); }
	virtual void visit( const CIfStatement& ifStatement ) { IVisitor::visit( ifStatement ); }
	virtual void visit( const CWhileStatement& whileStatement ) { IVisitor::visit( whileStatement ); }
	virtual void visit( const CExpList& expList ) { IVisitor::visit( expList ); }

private:
	// Текущий класс в котором мы находимся.
	SymbolsTable::CClassDescription curClass;
	// Текущий метод в котором мы находимся. 0( IsZero == 0 ), если вне методов.
	SymbolsTable::CMethodDescription curMethod;
	// Текущая переменная, которую мы конструируем. 
	SymbolsTable::CVariableDescription curVariable;
};