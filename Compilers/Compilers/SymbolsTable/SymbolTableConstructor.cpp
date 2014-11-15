// Автор: Фролов Николай.

#include "SymbolTableConstructor.h"
#include "SymbolsTableUtils.h"
#include "iostream"
#include <cassert>

using namespace SymbolsTable;

void CSymbolTableConstructor::visit( CProgram& program )
{
	program.pMainClass->accept( *this );
	if( program.pClassDeclList != 0 ) {
		program.pClassDeclList->accept( *this );
	}
}

void CSymbolTableConstructor::visit( CMainClass& mainClass )
{
	curClass.Name = mainClass.pId->value;
	curClass.Methods.push_back( CMethodDescription( "main", CTypeIdentifier( "VOID" ) ) );
	symbolTable.AddClass( curClass );
	curClass.MakeZero();
}

void CSymbolTableConstructor::visit( CClassDeclList& classDeclList )
{
	for( auto ptr = classDeclList.classDeclList.begin(); ptr != classDeclList.classDeclList.end(); ++ptr ) {
		( *ptr )->accept( *this );
	}
}

void CSymbolTableConstructor::visit( CClassDecl& classDecl )
{
	curClass.Name = classDecl.classPId->value;
	if( classDecl.parrentPId != 0 ) {
		curClass.BaseClass = classDecl.parrentPId->value;
	}
	classDecl.pVarDeclList->accept( *this );
	classDecl.pMethodDeclList->accept( *this );
	symbolTable.AddClass( curClass );
	curClass.MakeZero();
}


void CSymbolTableConstructor::visit( CVarDeclList& varDeclList )
{
	for( auto ptr = varDeclList.varDeclList.begin(); ptr != varDeclList.varDeclList.end(); ++ptr ) {
		( *ptr )->accept( *this );
	}
}

void CSymbolTableConstructor::visit( CVarDecl& varDecl )
{
	if( curMethod.IsZero() ) {
		if( HasSuchNameInScope( curClass.Fields, varDecl.pId->value ) ) {
			// Redefinition error.
		} else {
			assert( curVariable.IsZero() );
			curVariable.Name = varDecl.pId->value;
			varDecl.pType->accept( *this );
			curClass.Fields.push_back( curVariable );
			curVariable.MakeZero();
		}
	} else {
		if( HasSuchNameInScope( curMethod.Locals, varDecl.pId->value ) 
			|| HasSuchNameInScope( curMethod.Params, varDecl.pId->value ) )
		{
			// Redefinition error.
		} else {
			assert( curVariable.IsZero() );
			curVariable.Name = varDecl.pId->value;
			varDecl.pType->accept( *this );
			curMethod.Locals.push_back( curVariable );
			curVariable.MakeZero();
		}
	}
}

void CSymbolTableConstructor::visit( CType& type )
{
	if( curVariable.IsZero() ) {
		assert( !curMethod.IsZero() );
		curMethod.ReturnType = type.pId->value;
	} else {
		curVariable.Type = type.pId->value;
	}
}

void CSymbolTableConstructor::visit( CMethodDeclList& methodDeclList )
{
	for( auto ptr = methodDeclList.methodDeclList.begin(); ptr != methodDeclList.methodDeclList.end(); ++ptr ) {
		( *ptr )->accept( *this );
	}
}

void CSymbolTableConstructor::visit( CMethodDecl& methodDecl )
{
	curMethod.Name = methodDecl.pId->value;
	methodDecl.pType->accept( *this );
	methodDecl.pFormalList->accept( *this );
	methodDecl.pVarDeclList->accept( *this );
	curClass.Methods.push_back( curMethod );
	curMethod.MakeZero();
}

void CSymbolTableConstructor::visit( CFormalList& formalList )
{
	for( auto ptr = formalList.formalList.begin(); ptr != formalList.formalList.end(); ++ptr ) {
		curVariable.Name = ptr->second->value;
		ptr->first->accept( *this );
		curMethod.Params.push_back( curVariable );
		curVariable.MakeZero();
	}
}