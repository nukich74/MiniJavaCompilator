// Автор: Николай Фролов.

// Описание: Класс реализующий визитор, строящий таблицу символов.

#pragma once

#include <Visitor.h>
#include <SymbolsTable.h>
#include <ErrorsAggregator.h>

class CSymbolTableConstructor : public IVisitor {
public:
	CSymbolTableConstructor() { }

	SymbolsTable::CSymbolsTable symbolTable;
	SymbolsTable::CErrorsAggregator errors;

	virtual void Visit( const CExpBinOpExp& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CUnMinExp& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CExpWithIndex& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CExpDotLength& exp ) { IVisitor::Visit( exp ); }
	virtual void Visit( const CExpIdExpList& exp ) { IVisitor::Visit( exp ); }
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
	virtual void Visit( const CStatementList& statementList ) { IVisitor::Visit( statementList ); }
	virtual void Visit( const CAssignStatement& assignStatement ) { IVisitor::Visit( assignStatement ); }
	virtual void Visit( const CPrintStatement& printStatement ) { IVisitor::Visit( printStatement ); }
	virtual void Visit( const CCurlyBraceStatement& curlyBraceStatement ) { IVisitor::Visit( curlyBraceStatement ); }
	virtual void Visit( const CIfStatement& ifStatement ) { IVisitor::Visit( ifStatement ); }
	virtual void Visit( const CWhileStatement& whileStatement ) { IVisitor::Visit( whileStatement ); }
	virtual void Visit( const CExpList& expList ) { IVisitor::Visit( expList ); }

private:
	// Текущий класс в котором мы находимся.
	SymbolsTable::CClassDescriptor* curClass;
	// Текущий метод в котором мы находимся.
	SymbolsTable::CMethodDescriptor* curMethod;
	// Текущая переменная, которую мы конструируем. 
	SymbolsTable::CVariableDescriptor* curVariable;

	template <class T>
	bool hasSuchNameInScope( const std::vector<T>& descriptors, const std::string& name )
	{
		for( auto& descriptor : descriptors ) {
			if( descriptor.Name() == name ) {
				return true;
			}
		}
		return false;
	}
};