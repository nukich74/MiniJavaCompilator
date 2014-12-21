// Автор: Фролов Николай.

#include "SymbolTableConstructor.h"
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
	CClassDescriptor newClass( mainClass.MainClassName() );
	curClass = &newClass;
	CMethodDescriptor main( "main" );
	main.ReturnType = CTypeIdentifier( "void" );
	curClass->Methods.push_back( main );
	symbolTable.AddClass( *curClass );
	curClass = 0;
}

void CSymbolTableConstructor::Visit( const CClassDeclList& classDeclList )
{
	for( auto& classDecl : classDeclList.ClassDeclList() ) {
		classDecl->Accept( *this );
	}
}

void CSymbolTableConstructor::Visit( const CClassDecl& classDecl )
{
	CClassDescriptor newClass( classDecl.ClassId() );
	curClass = &newClass;
	curClass->BaseClass = classDecl.ParendId();
	if( classDecl.VarDeclList() != 0 ) {
		classDecl.VarDeclList()->Accept( *this );
	}
	if( classDecl.MethodDeclList() != 0 ) {
		classDecl.MethodDeclList()->Accept( *this );
	}
	if( symbolTable.Classes().find( classDecl.ClassId() ) != symbolTable.Classes().end() ) {
		std::shared_ptr<CRedefinitionError> classRedError( std::make_shared<CRedefinitionError>( classDecl.ClassId(), IT_Class, classDecl.Location() ) );
		errors.AddError( classRedError );
	} else {
		symbolTable.AddClass( *curClass );
	}
	curClass = 0;
}


void CSymbolTableConstructor::Visit( const CVarDeclList& varDeclList )
{
	for( auto& varDecl : varDeclList.VarDeclList() ) {
		varDecl->Accept( *this );
	}
}

void CSymbolTableConstructor::Visit( const CVarDecl& varDecl )
{
	if( curMethod == 0 ) {
		if( hasSuchNameInScope( curClass->Fields, varDecl.VarName() ) ) {
			std::shared_ptr<CRedefinitionError> varRedError( std::make_shared<CRedefinitionError>( varDecl.VarName(), IT_Variable, varDecl.Location() ) );
			errors.AddError( varRedError );
		}
		assert( curVariable == 0 );
		CVariableDescriptor newVar( varDecl.VarName() );
		curVariable = &newVar;
		varDecl.VarType()->Accept( *this );
		curClass->Fields.push_back( *curVariable );
		curVariable = 0;
	} else {
		if( hasSuchNameInScope( curMethod->Locals, varDecl.VarName() ) || hasSuchNameInScope( curMethod->Params, varDecl.VarName() ) ) {
			std::shared_ptr<CRedefinitionError> varRedError( std::make_shared<CRedefinitionError>( varDecl.VarName(), IT_Variable, varDecl.Location() ) );
			errors.AddError( varRedError );
		}
		assert( curVariable == 0 );
		CVariableDescriptor newVar( varDecl.VarName() );
		curVariable = &newVar;
		varDecl.VarType()->Accept( *this );
		curMethod->Locals.push_back( *curVariable );
		curVariable = 0;
	}
}

void CSymbolTableConstructor::Visit( const CType& type )
{
	if( curVariable == 0 ) {
		assert( curMethod != 0 );
		curMethod->ReturnType = type.TypeName();
	} else {
		curVariable->Type = type.TypeName();
	}
}

void CSymbolTableConstructor::Visit( const CMethodDeclList& methodDeclList )
{
	for( auto methodDecl : methodDeclList.MethodDeclList() ) {
		methodDecl->Accept( *this );
	}
}

void CSymbolTableConstructor::Visit( const CMethodDecl& methodDecl )
{
	if( hasSuchNameInScope( curClass->Fields, methodDecl.MethodName() ) || hasSuchNameInScope( curClass->Methods, methodDecl.MethodName() ) ) {
		std::shared_ptr<CRedefinitionError> methodRedError( std::make_shared<CRedefinitionError>( methodDecl.MethodName(), IT_Method, methodDecl.Location() ) );
		errors.AddError( methodRedError );
	}
	CMethodDescriptor newMethod( methodDecl.MethodName() );
	curMethod = &newMethod;
	methodDecl.ReturnedType()->Accept( *this );
	if( methodDecl.FormalList() != 0 ) {
		methodDecl.FormalList()->Accept( *this );
	}
	if( methodDecl.VarDeclList() != 0 ) {
		methodDecl.VarDeclList()->Accept( *this );
	}
	curClass->Methods.push_back( *curMethod );
	curMethod = 0;
}

void CSymbolTableConstructor::Visit( const CFormalList& formalList )
{
	for( auto& formalArg : formalList.FormalList() ) {
		if( hasSuchNameInScope( curMethod->Params, formalArg.second ) ) {
			std::shared_ptr<CRedefinitionError> varRedError( std::make_shared<CRedefinitionError>( formalArg.second, IT_Variable, formalList.Location() ) );
			errors.AddError( varRedError );
		}
		CVariableDescriptor newVar( formalArg.second );
		curVariable = &newVar;
		formalArg.first->Accept( *this );
		curMethod->Params.push_back( *curVariable );
		curVariable = 0;
	}
}