#include "PrettyPrinterVisitor.h"
#include <iostream>
#include <string>
#include <cassert>
#include <common.h>
#include <Visitor.h>

void CPrettyPrinterVisitor::visit( const CExpBinOpExp& exp )
{
	exp.left->accept( *this );
	std::cout << " " <<  exp.operation << " ";
	exp.right->accept( *this );
}

void CPrettyPrinterVisitor::visit( const CUnMinExp& exp )
{
	std::cout << "-";
	exp.exp->accept( *this );
}

void CPrettyPrinterVisitor::visit( const CExpWithIndex& exp )
{
	exp.exp->accept( *this );
	std::cout << "[";
	exp.index->accept( *this );
	std::cout << "]";
}

void CPrettyPrinterVisitor::visit( const CExpDotLength& exp )
{
	exp.exp->accept( *this );
	std::cout << ".Length";
}

void CPrettyPrinterVisitor::visit( const CExpIdExpList& exp )
{
	exp.exp->accept( *this );
	std::cout << ".";
	std::cout << exp.id;
	std::cout << "( ";
	exp.expList->accept( *this );
	std::cout << " )";
}

void CPrettyPrinterVisitor::visit( const CExpIdVoidExpList& exp )
{
	exp.exp->accept( *this );
	std::cout << ".";
	std::cout << exp.id;
	std::cout << "()";
}

void CPrettyPrinterVisitor::visit( const CIntegerLiteral& exp )
{
	std::cout << exp.value;
}

void CPrettyPrinterVisitor::visit( const CTrue& exp )
{
	std::cout << "true";
}

void CPrettyPrinterVisitor::visit( const CFalse& exp )
{
	std::cout << "false";
}

void CPrettyPrinterVisitor::visit( const CId& exp )
{
	std::cout << exp.value;
}

void CPrettyPrinterVisitor::visit( const CThis& exp )
{
	std::cout << "this";
}

void CPrettyPrinterVisitor::visit( const CNewIntExpIndex& exp )
{
	std::cout << "new int[ ";
	exp.exp->accept( *this );
	std::cout << " ]";
}
void CPrettyPrinterVisitor::visit( const CNewId& exp )
{
	std::cout << exp.typeId;
}

void CPrettyPrinterVisitor::visit( const CNotExp& exp )
{
	std::cout << "!";
	exp.exp->accept( *this );
}

void CPrettyPrinterVisitor::visit( const CExpInBrackets& exp )
{
	std::cout << "( ";
	exp.exp->accept( *this );
	std::cout << " )";
}

void CPrettyPrinterVisitor::visit( const CProgram& program )
{
	program.pMainClass->accept( *this );
	std::cout << std::endl;
	if( program.pClassDeclList != 0 ) {
		program.pClassDeclList->accept( *this );
	}
}

void CPrettyPrinterVisitor::visit( const CMainClass& mainClass )
{
	std::cout << "class "; 
	std::cout << mainClass.id1;
	std::cout << " {" << std::endl << "static void main ( string[] ";
	std::cout << mainClass.id2;
	std::cout << " )" << std::endl;
	std::cout << "{" << std::endl;
	if( mainClass.pStatementList != 0 ) {
		mainClass.pStatementList->accept( *this );
	}
	std::cout << "}" << std::endl << "}";
}

void CPrettyPrinterVisitor::visit( const CClassDeclList& classDeclList )
{
	for( const auto& clsDecl : classDeclList.classDeclList ) {
		clsDecl->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( const CClassDecl& classDecl )
{
	std::cout << "class ";
	std::cout << classDecl.classId;
	if( classDecl.parentId != "" ) {
		std::cout << " extends " << classDecl.parentId;
	}
	std::cout << " {" << std::endl;
	if( classDecl.pVarDeclList != 0 ) {
		classDecl.pVarDeclList->accept( *this );
	}
	if( classDecl.pMethodDeclList != 0 ) {
		classDecl.pMethodDeclList->accept( *this );
	}
	std::cout << "}";
}

void CPrettyPrinterVisitor::visit( const CVarDeclList& varDeclList )
{
	for( const auto& decl : varDeclList.varDeclList ) {
		decl->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( const CVarDecl& varDecl )
{
	varDecl.pType->accept( *this );
	std::cout << " ";
	std::cout << varDecl.id;
	std::cout << ";";
}

void CPrettyPrinterVisitor::visit( const CMethodDeclList& methodDeclList )
{
	for( const auto& decl : methodDeclList.methodDeclList ) {
		decl->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( const CMethodDecl& methodDecl )
{
	methodDecl.pType->accept( *this );
	std::cout << " " << methodDecl.id;
	std::cout << "( ";
	if( methodDecl.pFormalList != 0 ) {
		methodDecl.pFormalList->accept( *this );
	}
	std::cout << " )" << std::endl << "{" << std::endl;
	if( methodDecl.pVarDeclList != 0 ) {
		methodDecl.pVarDeclList->accept( *this );
	}
	if( methodDecl.pStatementList != 0 ) {
		methodDecl.pStatementList->accept( *this );
	}
	if( methodDecl.pExp != 0 ) {
		std::cout << "return ";
		methodDecl.pExp->accept( *this );
		std::cout << ";" << std::endl;
	}
	std::cout << "}";
}

void CPrettyPrinterVisitor::visit( const CFormalList& formalList )
{
	for( auto ptr = formalList.formalList.begin(); ptr != formalList.formalList.end(); ++ptr ) {
		if( ptr != formalList.formalList.begin() ) {
			std::cout << ", ";
		}
		ptr->first->accept( *this );
		std::cout << " ";
		std::cout << ptr->second;
	}
}

void CPrettyPrinterVisitor::visit( const CType& type )
{
	std::cout << type.id;
}

void CPrettyPrinterVisitor::visit( const CStatementList& statementList )
{
	for( const auto& decl : statementList.statementList ) {
		decl->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( const CAssignStatement& assignStatement )
{
	std::cout << assignStatement.id;
	if( assignStatement.pExp1 != 0 ) {
		std::cout << "[";
		assignStatement.pExp1->accept( *this );
		std::cout << "]";
	}
	std::cout << " = ";
	assignStatement.pExp2->accept( *this );
	std::cout << ";";
}

void CPrettyPrinterVisitor::visit( const CPrintStatement& printStatement )
{
	std::cout << "System.out.println( ";
	printStatement.pExp->accept( *this );
	std::cout << " );";
}

void CPrettyPrinterVisitor::visit( const CCurlyBraceStatement& curlyBraceStatement )
{
	std::cout << "{ " << std::endl;
	curlyBraceStatement.pStatementList->accept( *this );
	std::cout << "}";
}

void CPrettyPrinterVisitor::visit( const CIfStatement& ifStatement )
{
	std::cout << "if( ";
	ifStatement.pExp->accept( *this );
	std::cout << " )" << std::endl;
	ifStatement.pStatement1->accept( *this );
	std::cout << std::endl;
	if( ifStatement.pStatement2 != 0 ) {
		std::cout << "else" << std::endl;
		ifStatement.pStatement2->accept( *this );
	}
}

void CPrettyPrinterVisitor::visit( const CWhileStatement& whileStatement )
{
	std::cout << "while( ";
	whileStatement.pExp->accept( *this );
	std::cout << " )" << std::endl;
	whileStatement.pStatement->accept( *this );
}

void CPrettyPrinterVisitor::visit( const CExpList& expList )
{
	for( const auto& decl : expList.expList ) {
		decl->accept( *this );
		std::cout << std::endl;
	}
}