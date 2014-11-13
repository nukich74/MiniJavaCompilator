#include "PrettyPrinterVisitor.h"
#include <iostream>
#include <string>

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
	switch( type.type ) {
		case CType::T_INT:
			std::cout << "int ";
		case CType::T_INTARR:
			std::cout << "int[] ";
		case CType::T_BOOL:
			std::cout << "boolean ";
		case CType::T_ID:
		{
			type.pId->accept( *this );
		}
		default:
			//assert( false );
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

}

void CPrettyPrinterVisitor::visit( CPrintStatement& printStatement )
{

}

void CPrettyPrinterVisitor::visit( CCurlyBraceStatement& curlyBraceStatement )
{

}

void CPrettyPrinterVisitor::visit( CIfStatement& ifStatement )
{

}

void CPrettyPrinterVisitor::visit( CWhileStatement& whileStatement )
{

}

void CPrettyPrinterVisitor::visit( CExpList& expList )
{

}