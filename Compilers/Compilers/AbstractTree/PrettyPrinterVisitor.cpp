#include "PrettyPrinterVisitor.h"
#include <iostream>
#include <string>
#include <cassert>
#include <common.h>
#include <Visitor.h>

void CPrettyPrinterVisitor::visit( CExpBinOpExp& exp )
{
	exp.left->accept( *this );
	std::cout << exp.operation;
	exp.right->accept( *this );
}

void CPrettyPrinterVisitor::visit( CUnMinExp& exp )
{
	std::cout << "-";
	exp.exp->accept( *this );
}

void CPrettyPrinterVisitor::visit( CExpWithIndex& exp )
{
	exp.exp->accept( *this );
	std::cout << "[";
	exp.index->accept( *this );
	std::cout << "]";
}

void CPrettyPrinterVisitor::visit( CExpDotLength& exp )
{
	exp.exp->accept( *this );
	std::cout << ".Length";
}

void CPrettyPrinterVisitor::visit( CExpIdExpList& exp )
{
	exp.exp->accept( *this );
	std::cout << ".";
	std::cout << exp.id;
	std::cout << "(";
	exp.expList->accept( *this );
	std::cout << ")";
}

void CPrettyPrinterVisitor::visit( CExpIdVoidExpList& exp )
{
	exp.exp->accept( *this );
	std::cout << ".";
	std::cout << exp.id;
	std::cout << "()";
}

void CPrettyPrinterVisitor::visit( CIntegerLiteral& exp )
{
	std::cout << exp.value << ' ';
}

void CPrettyPrinterVisitor::visit( CTrue& exp )
{
	std::cout << " True ";
}

void CPrettyPrinterVisitor::visit( CFalse& exp )
{
	std::cout << " False ";
}

void CPrettyPrinterVisitor::visit( CId& exp )
{
	std::cout << exp.value;
	std::cout << ' ';
}

void CPrettyPrinterVisitor::visit( CThis& exp )
{
	std::cout << " this ";
}

void CPrettyPrinterVisitor::visit( CNewIntExpIndex& exp )
{
	std::cout << "new int[";
	exp.exp->accept( *this );
	std::cout << "]";
}
void CPrettyPrinterVisitor::visit( CNewId& exp )
{
	std::cout << exp.typeId;
}

void CPrettyPrinterVisitor::visit( CNotExp& exp )
{
	std::cout << "!";
	exp.exp->accept( *this );
}

void CPrettyPrinterVisitor::visit( CExpInBrackets& exp )
{
	std::cout << "(";
	exp.exp->accept( *this );
	std::cout << ")";
}

void CPrettyPrinterVisitor::visit( CProgram& program )
{
	program.pMainClass->accept( *this );
	if( program.pClassDeclList != 0 ) {
		program.pClassDeclList->accept( *this );
	}
}

void CPrettyPrinterVisitor::visit( CMainClass& mainClass )
{
	std::cout << "class "; 
	std::cout << mainClass.id1;
	std::cout << "{" << std::endl << "	static void main ( string[] ";
	std::cout << mainClass.id2;
	std::cout << " )" << std::endl;
	std::cout << "{" << std::endl;
	if( mainClass.pStatementList != 0 ) {
		mainClass.pStatementList->accept( *this );
	}
	std::cout << "}" << std::endl << "};";
}

void CPrettyPrinterVisitor::visit( CClassDeclList& classDeclList )
{
	for( const auto& clsDecl : classDeclList.classDeclList ) {
		clsDecl->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( CClassDecl& classDecl )
{
	std::cout << "class ";
	std::cout << classDecl.classId;
	std::cout << " {\n";
	if( classDecl.pVarDeclList != 0 ) {
		classDecl.pVarDeclList->accept( *this );
	}
	std::cout << std::endl;
	if( classDecl.pMethodDeclList != 0 ) {
		classDecl.pMethodDeclList->accept( *this );
	}
	std::cout << std::endl;
	std::cout << "};";
}

void CPrettyPrinterVisitor::visit( CVarDeclList& varDeclList )
{
	for( const auto& decl : varDeclList.varDeclList ) {
		decl->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( CVarDecl& varDecl )
{
	varDecl.pType->accept( *this );
	std::cout << " ";
	std::cout << varDecl.id;
	std::cout << std::endl;
}

void CPrettyPrinterVisitor::visit( CMethodDeclList& methodDeclList )
{
	for( const auto& decl : methodDeclList.methodDeclList ) {
		decl->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( CMethodDecl& methodDecl )
{
	methodDecl.pType->accept( *this );
	std::cout << methodDecl.id;
	if( methodDecl.pFormalList != 0 ) {
		methodDecl.pFormalList->accept( *this );
	}
	if( methodDecl.pVarDeclList != 0 ) {
		methodDecl.pVarDeclList->accept( *this );
	}
	if( methodDecl.pStatementList != 0 ) {
		methodDecl.pStatementList->accept( *this );
	}
	if( methodDecl.pExp != 0 ) {
		methodDecl.pExp->accept( *this );
	}
}

void CPrettyPrinterVisitor::visit( CFormalList& formalList )
{
	for( const auto& decl : formalList.formalList ) {
		decl.first->accept( *this );
		std::cout << " ";
		std::cout << decl.second;
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( CType& type )
{
	std::cout << type.id;
}

void CPrettyPrinterVisitor::visit( CStatementList& statementList )
{
	for( const auto& decl : statementList.statementList ) {
		decl->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( CAssignStatement& assignStatement )
{
	std::cout << assignStatement.id;
	if( assignStatement.pExp1 != 0 ) {
		std::cout << "[";
		assignStatement.pExp1->accept( *this );
		std::cout << "]";
	}
	std::cout << " = ";
	assignStatement.pExp2->accept( *this );
}

void CPrettyPrinterVisitor::visit( CPrintStatement& printStatement )
{
	std::cout << "System.out.println( ";
	printStatement.pExp->accept( *this );
	std::cout << " );";
}

void CPrettyPrinterVisitor::visit( CCurlyBraceStatement& curlyBraceStatement )
{
	curlyBraceStatement.pStatementList->accept( *this );
}

void CPrettyPrinterVisitor::visit( CIfStatement& ifStatement )
{
	std::cout << "if( ";
	ifStatement.pExp->accept( *this );
	std::cout << ") {\n";
	ifStatement.pStatement1->accept( *this );
	std::cout << "}\n";
	if( ifStatement.pStatement2 != 0 ) {
		std::cout << "else {\n";
		ifStatement.pStatement2->accept( *this );
		std::cout << "}\n";
	}
}

void CPrettyPrinterVisitor::visit( CWhileStatement& whileStatement )
{
	std::cout << "while( ";
	whileStatement.pExp->accept( *this );
	std::cout << ") {\n";
	whileStatement.pStatement->accept( *this );
	std::cout << "}\n";
}

void CPrettyPrinterVisitor::visit( CExpList& expList )
{
	for( const auto& decl : expList.expList ) {
		decl->accept( *this );
		std::cout << std::endl;
	}
}