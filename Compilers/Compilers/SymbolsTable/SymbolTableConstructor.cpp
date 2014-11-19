// Автор: Фролов Николай.

#include "SymbolTableConstructor.h"
#include "SymbolsTableUtils.h"
#include "iostream"
#include <cassert>
#include <common.h>

using namespace SymbolsTable;

void CSymbolTableConstructor::visit( const CProgram& program )
{
	program.pMainClass->accept( *this );
	if( program.pClassDeclList != 0 ) {
		program.pClassDeclList->accept( *this );
	}
}

void CSymbolTableConstructor::visit( const CMainClass& mainClass )
{
	curClass.Name = mainClass.id1;
	curClass.Methods.push_back( CMethodDescription( "main", CTypeIdentifier( "void" ) ) );
	symbolTable.AddClass( curClass );
	curClass.MakeZero();
}

void CSymbolTableConstructor::visit( const CClassDeclList& classDeclList )
{
	for( auto ptr = classDeclList.classDeclList.begin(); ptr != classDeclList.classDeclList.end(); ++ptr ) {
		( *ptr )->accept( *this );
	}
}

void CSymbolTableConstructor::visit( const CClassDecl& classDecl )
{
	curClass.Name = classDecl.classId;
	curClass.BaseClass = classDecl.parentId;
	if( classDecl.pVarDeclList != 0 ) {
		classDecl.pVarDeclList->accept( *this );
	}
	if( classDecl.pMethodDeclList != 0 ) {
		classDecl.pMethodDeclList->accept( *this );
	}
	if( symbolTable.Classes.find( classDecl.classId ) != symbolTable.Classes.end() ) {
		errors.AddError( ET_Redefinition, ErrorPosition( classDecl.classId ) );
	} else {
		symbolTable.AddClass( curClass );
	}
	curClass.MakeZero();
}


void CSymbolTableConstructor::visit( const CVarDeclList& varDeclList )
{
	for( auto ptr = varDeclList.varDeclList.begin(); ptr != varDeclList.varDeclList.end(); ++ptr ) {
		( *ptr )->accept( *this );
	}
}

void CSymbolTableConstructor::visit( const CVarDecl& varDecl )
{
	if( curMethod.IsZero() ) {
		if( HasSuchNameInScope( curClass.Fields, varDecl.id ) ) {
			errors.AddError( ET_Redefinition, ErrorPosition( curClass.Name, "", varDecl.id ) );
		}
		assert( curVariable.IsZero() );
		curVariable.Name = varDecl.id;
		varDecl.pType->accept( *this );
		curClass.Fields.push_back( curVariable );
		curVariable.MakeZero();
	} else {
		if( HasSuchNameInScope( curMethod.Locals, varDecl.id ) || HasSuchNameInScope( curMethod.Params, varDecl.id ) )
		{
			errors.AddError( ET_Redefinition, ErrorPosition( curClass.Name, curMethod.Name, varDecl.id ) );
		}
		assert( curVariable.IsZero() );
		curVariable.Name = varDecl.id;
		varDecl.pType->accept( *this );
		curMethod.Locals.push_back( curVariable );
		curVariable.MakeZero();
	}
}

void CSymbolTableConstructor::visit( const CType& type )
{
	if( curVariable.IsZero() ) {
		assert( !curMethod.IsZero() );
		curMethod.ReturnType = type.id;
	} else {
		curVariable.Type = type.id;
	}
}

void CSymbolTableConstructor::visit( const CMethodDeclList& methodDeclList )
{
	for( auto ptr = methodDeclList.methodDeclList.begin(); ptr != methodDeclList.methodDeclList.end(); ++ptr ) {
		( *ptr )->accept( *this );
	}
}

void CSymbolTableConstructor::visit( const CMethodDecl& methodDecl )
{
	if( HasSuchNameInScope( curClass.Fields, methodDecl.id ) || HasSuchNameInScope( curClass.Methods, methodDecl.id ) ) {
		errors.AddError( ET_Redefinition, ErrorPosition( curClass.Name, methodDecl.id ) );
	}
	curMethod.Name = methodDecl.id;
	methodDecl.pType->accept( *this );
	if( methodDecl.pFormalList != 0 ) {
		methodDecl.pFormalList->accept( *this );
	}
	if( methodDecl.pVarDeclList != 0 ) {
		methodDecl.pVarDeclList->accept( *this );
	}
	curClass.Methods.push_back( curMethod );
	curMethod.MakeZero();
}

void CSymbolTableConstructor::visit( const CFormalList& formalList )
{
	for( auto ptr = formalList.formalList.begin(); ptr != formalList.formalList.end(); ++ptr ) {
		curVariable.Name = ptr->second;
		ptr->first->accept( *this );
		curMethod.Params.push_back( curVariable );
		curVariable.MakeZero();
	}
}