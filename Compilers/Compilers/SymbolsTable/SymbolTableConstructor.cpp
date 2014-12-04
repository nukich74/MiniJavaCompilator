// Автор: Фролов Николай.

#include "SymbolTableConstructor.h"
#include "SymbolsTableUtils.h"
#include "iostream"
#include <cassert>
#include <common.h>

using namespace SymbolsTable;

void CSymbolTableConstructor::Visit( const CProgram& program )
{
	program.MainClass()->Accept( *this );
	if( program.ClassDeclList() != 0 ) {
		program.ClassDeclList()->Accept( *this );
	}
}

void CSymbolTableConstructor::Visit( const CMainClass& mainClass )
{
	curClass.Name = mainClass.MainClassName();
	curClass.Methods.push_back( CMethodDescription( "main", CTypeIdentifier( "void" ) ) );
	symbolTable.AddClass( curClass );
	curClass.MakeZero();
}

void CSymbolTableConstructor::Visit( const CClassDeclList& classDeclList )
{
	for( auto ptr = classDeclList.ClassDeclList().begin(); ptr != classDeclList.ClassDeclList().end(); ++ptr ) {
		( *ptr )->Accept( *this );
	}
}

void CSymbolTableConstructor::Visit( const CClassDecl& classDecl )
{
	curClass.Name = classDecl.ClassId();
	curClass.BaseClass = classDecl.ParendId();
	if( classDecl.VarDeclList() != 0 ) {
		classDecl.VarDeclList()->Accept( *this );
	}
	if( classDecl.MethodDeclList() != 0 ) {
		classDecl.MethodDeclList()->Accept( *this );
	}
	if( symbolTable.Classes.find( classDecl.ClassId() ) != symbolTable.Classes.end() ) {
		errors.AddError( ET_Redefinition, ErrorPosition( classDecl.ClassId() ) );
	} else {
		symbolTable.AddClass( curClass );
	}
	curClass.MakeZero();
}


void CSymbolTableConstructor::Visit( const CVarDeclList& varDeclList )
{
	for( auto ptr = varDeclList.VarDeclList().begin(); ptr != varDeclList.VarDeclList().end(); ++ptr ) {
		( *ptr )->Accept( *this );
	}
}

void CSymbolTableConstructor::Visit( const CVarDecl& varDecl )
{
	if( curMethod.IsZero() ) {
		if( HasSuchNameInScope( curClass.Fields, varDecl.VarName() ) ) {
			errors.AddError( ET_Redefinition, ErrorPosition( curClass.Name, "", varDecl.VarName() ) );
		}
		assert( curVariable.IsZero() );
		curVariable.Name = varDecl.VarName();
		varDecl.VarType()->Accept( *this );
		curClass.Fields.push_back( curVariable );
		curVariable.MakeZero();
	} else {
		if( HasSuchNameInScope( curMethod.Locals, varDecl.VarName() ) || HasSuchNameInScope( curMethod.Params, varDecl.VarName() ) )
		{
			errors.AddError( ET_Redefinition, ErrorPosition( curClass.Name, curMethod.Name, varDecl.VarName() ) );
		}
		assert( curVariable.IsZero() );
		curVariable.Name = varDecl.VarName();
		varDecl.VarType()->Accept( *this );
		curMethod.Locals.push_back( curVariable );
		curVariable.MakeZero();
	}
}

void CSymbolTableConstructor::Visit( const CType& type )
{
	if( curVariable.IsZero() ) {
		assert( !curMethod.IsZero() );
		curMethod.ReturnType = type.TypeName();
	} else {
		curVariable.Type = type.TypeName();
	}
}

void CSymbolTableConstructor::Visit( const CMethodDeclList& methodDeclList )
{
	for( auto ptr = methodDeclList.MethodDeclList().begin(); ptr != methodDeclList.MethodDeclList().end(); ++ptr ) {
		( *ptr )->Accept( *this );
	}
}

void CSymbolTableConstructor::Visit( const CMethodDecl& methodDecl )
{
	if( HasSuchNameInScope( curClass.Fields, methodDecl.MethodName() ) || HasSuchNameInScope( curClass.Methods, methodDecl.MethodName() ) ) {
		errors.AddError( ET_Redefinition, ErrorPosition( curClass.Name, methodDecl.MethodName() ) );
	}
	curMethod.Name = methodDecl.MethodName();
	methodDecl.ReturnedType()->Accept( *this );
	if( methodDecl.FormalList() != 0 ) {
		methodDecl.FormalList()->Accept( *this );
	}
	if( methodDecl.VarDeclList() != 0 ) {
		methodDecl.VarDeclList()->Accept( *this );
	}
	curClass.Methods.push_back( curMethod );
	curMethod.MakeZero();
}

void CSymbolTableConstructor::Visit( const CFormalList& formalList )
{
	for( auto ptr = formalList.FormalList().begin(); ptr != formalList.FormalList().end(); ++ptr ) {
		curVariable.Name = ptr->second;
		ptr->first->Accept( *this );
		curMethod.Params.push_back( curVariable );
		curVariable.MakeZero();
	}
}