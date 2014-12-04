#include "PrettyPrinterVisitor.h"
#include <iostream>
#include <string>
#include <cassert>
#include <common.h>
#include <Visitor.h>

void CPrettyPrinterVisitor::Visit( const CExpBinOpExp& exp )
{
	exp.LeftArg()->Accept( *this );
	std::cout << " " <<  exp.Operation() << " ";
	exp.RightArg()->Accept( *this );
}

void CPrettyPrinterVisitor::Visit( const CUnMinExp& exp )
{
	std::cout << "-";
	exp.Exp()->Accept( *this );
}

void CPrettyPrinterVisitor::Visit( const CExpWithIndex& exp )
{
	exp.Exp()->Accept( *this );
	std::cout << "[";
	exp.Index()->Accept( *this );
	std::cout << "]";
}

void CPrettyPrinterVisitor::Visit( const CExpDotLength& exp )
{
	exp.Exp()->Accept( *this );
	std::cout << ".Length";
}

void CPrettyPrinterVisitor::Visit( const CExpIdExpList& exp )
{
	exp.Exp()->Accept( *this );
	std::cout << ".";
	std::cout << exp.Id();
	std::cout << "( ";
	exp.ExpList()->Accept( *this );
	std::cout << " )";
}

void CPrettyPrinterVisitor::Visit( const CExpIdVoidExpList& exp )
{
	exp.Exp()->Accept( *this );
	std::cout << ".";
	std::cout << exp.Id();
	std::cout << "()";
}

void CPrettyPrinterVisitor::Visit( const CIntegerLiteral& exp )
{
	std::cout << exp.Value();
}

void CPrettyPrinterVisitor::Visit( const CTrue& exp )
{
	std::cout << "true";
}

void CPrettyPrinterVisitor::Visit( const CFalse& exp )
{
	std::cout << "false";
}

void CPrettyPrinterVisitor::Visit( const CId& exp )
{
	std::cout << exp.Id();
}

void CPrettyPrinterVisitor::Visit( const CThis& exp )
{
	std::cout << "this";
}

void CPrettyPrinterVisitor::Visit( const CNewIntExpIndex& exp )
{
	std::cout << "new int[ ";
	exp.Exp()->Accept( *this );
	std::cout << " ]";
}
void CPrettyPrinterVisitor::Visit( const CNewId& exp )
{
	std::cout << "new " << exp.TypeId() << "()";
}

void CPrettyPrinterVisitor::Visit( const CNotExp& exp )
{
	std::cout << "!";
	exp.Exp()->Accept( *this );
}

void CPrettyPrinterVisitor::Visit( const CExpInBrackets& exp )
{
	std::cout << "( ";
	exp.Exp()->Accept( *this );
	std::cout << " )";
}

void CPrettyPrinterVisitor::Visit( const CProgram& program )
{
	program.MainClass()->Accept( *this );
	std::cout << std::endl;
	if( program.ClassDeclList() != 0 ) {
		program.ClassDeclList()->Accept( *this );
	}
}

void CPrettyPrinterVisitor::Visit( const CMainClass& mainClass )
{
	std::cout << "class "; 
	std::cout << mainClass.MainClassName();
	std::cout << " {" << std::endl << "static void main ( string[] ";
	std::cout << mainClass.StringName();
	std::cout << " )" << std::endl;
	std::cout << "{" << std::endl;
	if( mainClass.StatementList() != 0 ) {
		mainClass.StatementList()->Accept( *this );
	}
	std::cout << "}" << std::endl << "}";
}

void CPrettyPrinterVisitor::Visit( const CClassDeclList& classDeclList )
{
	for( const auto& clsDecl : classDeclList.ClassDeclList() ) {
		clsDecl->Accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::Visit( const CClassDecl& classDecl )
{
	std::cout << "class ";
	std::cout << classDecl.ClassId();
	if( classDecl.ParendId() != "" ) {
		std::cout << " extends " << classDecl.ParendId();
	}
	std::cout << " {" << std::endl;
	if( classDecl.VarDeclList() != 0 ) {
		classDecl.VarDeclList()->Accept( *this );
	}
	if( classDecl.MethodDeclList() != 0 ) {
		classDecl.MethodDeclList()->Accept( *this );
	}
	std::cout << "}";
}

void CPrettyPrinterVisitor::Visit( const CVarDeclList& varDeclList )
{
	for( const auto& decl : varDeclList.VarDeclList() ) {
		decl->Accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::Visit( const CVarDecl& varDecl )
{
	varDecl.VarType()->Accept( *this );
	std::cout << " ";
	std::cout << varDecl.VarName();
	std::cout << ";";
}

void CPrettyPrinterVisitor::Visit( const CMethodDeclList& methodDeclList )
{
	for( const auto& decl : methodDeclList.MethodDeclList() ) {
		decl->Accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::Visit( const CMethodDecl& methodDecl )
{
	methodDecl.ReturnedType()->Accept( *this );
	std::cout << " " << methodDecl.MethodName();
	std::cout << "( ";
	if( methodDecl.FormalList() != 0 ) {
		methodDecl.FormalList()->Accept( *this );
	}
	std::cout << " )" << std::endl << "{" << std::endl;
	if( methodDecl.VarDeclList() != 0 ) {
		methodDecl.VarDeclList()->Accept( *this );
	}
	if( methodDecl.StatementList() != 0 ) {
		methodDecl.StatementList()->Accept( *this );
	}
	if( methodDecl.ReturnedExp() != 0 ) {
		std::cout << "return ";
		methodDecl.ReturnedExp()->Accept( *this );
		std::cout << ";" << std::endl;
	}
	std::cout << "}";
}

void CPrettyPrinterVisitor::Visit( const CFormalList& formalList )
{
	for( auto ptr = formalList.FormalList().begin(); ptr != formalList.FormalList().end(); ++ptr ) {
		if( ptr != formalList.FormalList().begin() ) {
			std::cout << ", ";
		}
		ptr->first->Accept( *this );
		std::cout << " ";
		std::cout << ptr->second;
	}
}

void CPrettyPrinterVisitor::Visit( const CType& type )
{
	std::cout << type.TypeName();
}

void CPrettyPrinterVisitor::Visit( const CStatementList& statementList )
{
	for( const auto& decl : statementList.StatmentList() ) {
		decl->Accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::Visit( const CAssignStatement& assignStatement )
{
	std::cout << assignStatement.LeftId();
	if( assignStatement.IndexExp() != 0 ) {
		std::cout << "[";
		assignStatement.IndexExp()->Accept( *this );
		std::cout << "]";
	}
	std::cout << " = ";
	assignStatement.RightExp()->Accept( *this );
	std::cout << ";";
}

void CPrettyPrinterVisitor::Visit( const CPrintStatement& printStatement )
{
	std::cout << "System.out.println( ";
	printStatement.Exp()->Accept( *this );
	std::cout << " );";
}

void CPrettyPrinterVisitor::Visit( const CCurlyBraceStatement& curlyBraceStatement )
{
	std::cout << "{ " << std::endl;
	curlyBraceStatement.StatementList()->Accept( *this );
	std::cout << "}";
}

void CPrettyPrinterVisitor::Visit( const CIfStatement& ifStatement )
{
	std::cout << "if( ";
	ifStatement.Exp()->Accept( *this );
	std::cout << " )" << std::endl;
	ifStatement.IfStatement()->Accept( *this );
	std::cout << std::endl;
	if( ifStatement.ElseStatement() != 0 ) {
		std::cout << "else" << std::endl;
		ifStatement.ElseStatement()->Accept( *this );
	}
}

void CPrettyPrinterVisitor::Visit( const CWhileStatement& whileStatement )
{
	std::cout << "while( ";
	whileStatement.Exp()->Accept( *this );
	std::cout << " )" << std::endl;
	whileStatement.Statement()->Accept( *this );
}

void CPrettyPrinterVisitor::Visit( const CExpList& expList )
{
	for( const auto& decl : expList.ExpList() ) {
		decl->Accept( *this );
		std::cout << std::endl;
	}
}