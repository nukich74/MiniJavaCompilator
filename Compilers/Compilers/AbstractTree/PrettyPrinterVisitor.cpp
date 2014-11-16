#include "PrettyPrinterVisitor.h"
#include <iostream>
#include <string>
#include <cassert>
#include "Visitor.h"

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
	exp.id->accept( *this );
	std::cout << "(";
	exp.expList->accept( *this );
	std::cout << ")";
}

void CPrettyPrinterVisitor::visit( CExpIdVoidExpList& exp )
{
	exp.exp->accept( *this );
	std::cout << ".";
	exp.id->accept( *this );
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
	std::cout << "new int[]";
	exp.exp->accept( *this );
}

void CPrettyPrinterVisitor::visit( CNotExp& exp )
{
	std::cout << "!";
	exp.accept( *this );
}

void CPrettyPrinterVisitor::visit( CExpInBrackets& exp )
{
	std::cout << "(";
	exp.accept( *this );
	std::cout << ")";
}

void CPrettyPrinterVisitor::visit( CProgram& program )
{
	program.pMainClass->accept( *this );
	program.pClassDeclList->accept( *this );
}

void CPrettyPrinterVisitor::visit( CMainClass& mainClass )
{
	std::cout << "class MainClass {";
	mainClass.pStatementList->accept( *this );
	std::cout << "};";
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
	classDecl.pId->accept( *this );
	std::cout << " {\n";
	classDecl.pMethodDeclList->accept( *this );
	std::cout << std::endl;
	classDecl.pVarDeclList->accept( *this );
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
	varDecl.pId->accept( *this );
	std::cout << std::endl;
}

void CPrettyPrinterVisitor::visit( CMethodDeclList& methodDeclList )
{
	for( const auto& decl : methodDeclList.methodDeclList ) {
		decl->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( CFormalList& formalList )
{
	for( const auto& decl : formalList.formalList ) {
		decl.first->accept( *this );
		std::cout << " ";
		decl.second->accept( *this );
		std::cout << std::endl;
	}
}

void CPrettyPrinterVisitor::visit( CType& type )
{
	if( type.type ==  SymbolsTable::BT_Int ) {
		std::cout << "int ";
	} else if( type.type ==  SymbolsTable::BT_IntArr ) {
		std::cout << "int[] ";
	} else if( type.type ==  SymbolsTable::BT_Bool ) {
		std::cout << "boolean ";
	} else if( type.type == SymbolsTable::BT_UserDefined ) {
		type.pId->accept( *this );
	} else {
		assert( false );
	}
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
	assignStatement.pId->accept( *this );
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
	// кто-нибудь объ€сните что за класс такой
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