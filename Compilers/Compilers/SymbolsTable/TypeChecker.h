// Автор: Фролов Николай.

// Описание: Визитор проверяющий AST на наличие семантических ошибок.

#pragma once

#include <Visitor.h>
#include <ClassDescriptor.h>
#include <MethodDescriptor.h>
#include <TypeIdentifier.h>
#include <ErrorsAggregator.h>
#include <SymbolsTable.h>
#include <set>
#include <vector>

class CTypeChecker : public IVisitor {
public:
	CTypeChecker( const SymbolsTable::CSymbolsTable& _symbolsTable )
		: symbolsTable( _symbolsTable )
	{ }

	SymbolsTable::CErrorsAggregator errors;

	virtual void Visit( const CExpBinOpExp& exp );
	virtual void Visit( const CUnMinExp& exp );
	virtual void Visit( const CExpWithIndex& exp );
	virtual void Visit( const CExpDotLength& exp );
	virtual void Visit( const CExpIdExpList& exp );
	virtual void Visit( const CExpIdVoidExpList& exp );
	virtual void Visit( const CIntegerLiteral& exp );
	virtual void Visit( const CTrue& exp );
	virtual void Visit( const CFalse& exp );
	virtual void Visit( const CId& exp );
	virtual void Visit( const CThis& exp );
	virtual void Visit( const CNewIntExpIndex& exp );
	virtual void Visit( const CNewId& exp );
	virtual void Visit( const CNotExp& exp );
	virtual void Visit( const CExpInBrackets& exp );
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

	mutable std::set<std::string> classesWithCycleExtends;
	mutable std::set<std::string> classesWithoutCycleExtends;
	mutable SymbolsTable::CTypeIdentifier lastType;

	const std::vector<SymbolsTable::CVariableDescriptor>* expectedArgs;
	const std::string* handlingMethodName;

	bool setLastVarTypeByIdentifier( const std::string& id ) const;

	const SymbolsTable::CMethodDescriptor* getMethodFromClassById( const SymbolsTable::CClassDescriptor* inClass, const std::string& id ) const;

	bool isClassCycled( const std::string& ) const;

	bool haveClassInTable( const std::string& ) const;

	bool inCycled( const std::string& ) const;

	bool inNotCycled( const std::string& ) const;
};