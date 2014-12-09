// Автор: Фролов Николай.

// Описание: Визитор проверяющий AST на наличие семантических ошибок.

#pragma once

#include <Visitor.h>
#include <ClassDescriptor.h>
#include <TypeIdentifier.h>
#include <SymbolsTable.h>

class CTypeChecker : public IVisitor {
public:
	CTypeChecker( const SymbolsTable::CSymbolsTable& _symbolsTable )
		: symbolsTable( _symbolsTable )
	{ }

	virtual void Visit( const CExpBinOpExp& exp );
	virtual void Visit( const CUnMinExp& exp );
	virtual void Visit( const CExpWithIndex& exp );
	virtual void Visit( const CExpDotLength& exp );
	virtual void Visit( const CExpIdExpList& exp );
	virtual void Visit( const CExpIdVoidExpList& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CIntegerLiteral& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CTrue& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CFalse& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CId& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CThis& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CNewIntExpIndex& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CNewId& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CNotExp& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CExpInBrackets& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CProgram& program );
	virtual void Visit( const CMainClass& mainClass );
	virtual void Visit( const CClassDeclList& classDeclList );
	virtual void Visit( const CClassDecl& classDecl );
	virtual void Visit( const CVarDeclList& varDeclList );
	virtual void Visit( const CVarDecl& varDecl );
	virtual void Visit( const CMethodDeclList& methodDeclList );
	virtual void Visit( const CMethodDecl& methodDecl );
	virtual void Visit( const CFormalList& formalList );
	virtual void Visit( const CType& type );
	virtual void Visit( const CStatementList& statementList );
	virtual void Visit( const CAssignStatement& assignStatement );
	virtual void Visit( const CPrintStatement& printStatement );
	virtual void Visit( const CCurlyBraceStatement& curlyBraceStatement );
	virtual void Visit( const CIfStatement& ifStatement );
	virtual void Visit( const CWhileStatement& whileStatement );
	virtual void Visit( const CExpList& expList );

private:
	const SymbolsTable::CSymbolsTable& symbolsTable;
	const SymbolsTable::CClassDescriptor* currentClass;
	const SymbolsTable::CMethodDescriptor* currentMethod;
	mutable SymbolsTable::CTypeIdentifier lastType;

	bool setLastTypeByIdentifier( const std::string& id ) const;
};