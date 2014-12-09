// Автор: Воротилов Владислав
// Визитор для построения дерева промежуточного представления


#include "IRTreeVisitor.h"
#include <Exp.h>
#include <iostream>
#include <string>
#include <cassert>
#include <common.h>
#include <Visitor.h>

namespace Translate {

void CIRTreeVisitor::Visit( const CExpBinOpExp& exp )
{
	// Забираем правый и левый операнды
	exp.LeftArg()->Accept( *this );
	IRTree::IIRExp* first = lastReturnedExp;
	exp.RightArg()->Accept( *this );
	IRTree::IIRExp* second = lastReturnedExp;
	IRTree::TBinop binOp;
	switch( exp.Operation() ) {
		case '+':
			binOp = IRTree::B_Plus;
			break;
		case '-':
			binOp = IRTree::B_Minus;
			break;
		case '*':
			binOp = IRTree::B_Mul;
			break;
		default:
			assert( false );
	}
	lastReturnedExp = new IRTree::CIRBinop( binOp, first, second );
}

void CIRTreeVisitor::Visit( const CUnMinExp& exp )
{
	// Как в лекциях заменяем на (0 - exp)
	IRTree::IIRExp* first = new IRTree::CIRConst( 0 );
	exp.Exp()->Accept( *this );
	IRTree::IIRExp* second = lastReturnedExp;
	lastReturnedExp = new IRTree::CIRBinop( IRTree::B_Minus, first, second );
}

void CIRTreeVisitor::Visit( const CExpWithIndex& exp )
{
#pragma message( "TODO Здесь надо возвращать IRTree::IRName переменной" )
	exp.Exp()->Accept( *this );
	exp.Index()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CExpDotLength& exp )
{
#pragma message( "TODO Здесь надо возвращать IRTree::IRConst переменной тк длину возвращать нельзя" )
	exp.Exp()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CExpIdExpList& exp )
{
	// Это заголовок функции с возвращаемым типом
	exp.Exp()->Accept( *this );
	exp.ExpList()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CExpIdVoidExpList& exp )
{
	// Заголовок функции без возвращаемого типа
	exp.Exp()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CIntegerLiteral& exp )
{
	lastReturnedExp = new IRTree::CIRConst( exp.Value() );
}

void CIRTreeVisitor::Visit( const CTrue& exp )
{
	// True у нас константа 1
	lastReturnedExp = new IRTree::CIRConst( 1 );
}

void CIRTreeVisitor::Visit( const CFalse& exp )
{
	// False у нас константа 0
	lastReturnedExp = new IRTree::CIRConst( 0 );
}

void CIRTreeVisitor::Visit( const CId& exp )
{
#pragma message( "TODO Здесь надо возвращать IRTree::IRName переменной" )
	std::cout << exp.Id();
}

void CIRTreeVisitor::Visit( const CThis& exp )
{
#pragma message( "TODO Здесь надо возвращать IRTree::IRName переменной" )
	std::cout << "this";
}

void CIRTreeVisitor::Visit( const CNewIntExpIndex& exp )
{
#pragma message( "TODO Оператор new для int[] тут получаем количество необходимой памяти из lastReturnedExp выделяем и возвращаем Name" )
	exp.Exp()->Accept( *this );
}
void CIRTreeVisitor::Visit( const CNewId& exp )
{
#pragma message( "TODO Оператор new для любого типа тут нужен размер типа, выделяем и возвращаем Name" )
	std::cout << "new " << exp.TypeId() << "()";
}

void CIRTreeVisitor::Visit( const CNotExp& exp )
{
#pragma message( "TODO Получить lastReturnedExp и записать туда конструкцию с XOR c Const(0)" )
	exp.Exp()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CExpInBrackets& exp )
{
#pragma message( "TODO Здесь нужно чтобы тот кому выражение принадлежит забрал lastReturnedExp" )
	exp.Exp()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CProgram& program )
{
	// Здесь для IRTree ничего не нужно
	program.MainClass()->Accept( *this );
	if( program.ClassDeclList() != 0 ) {
		program.ClassDeclList()->Accept( *this );
	}
	
}

void CIRTreeVisitor::Visit( const CMainClass& mainClass )
{
	// Здесь для IRTree ничего не нужно
	if( mainClass.StatementList() != 0 ) {
		mainClass.StatementList()->Accept( *this );
	}
}

void CIRTreeVisitor::Visit( const CClassDeclList& classDeclList )
{
	// Здесь для IRTree ничего не нужно
	for( const auto& clsDecl : classDeclList.ClassDeclList() ) {
		clsDecl->Accept( *this );
	}
}

void CIRTreeVisitor::Visit( const CClassDecl& classDecl )
{
	// Здесь для IRTree ничего не нужно
	if( classDecl.VarDeclList() != 0 ) {
		classDecl.VarDeclList()->Accept( *this );
	}
	if( classDecl.MethodDeclList() != 0 ) {
		classDecl.MethodDeclList()->Accept( *this );
	}
}

void CIRTreeVisitor::Visit( const CVarDeclList& varDeclList )
{
	// Здесь для IRTree ничего не нужно
	for( const auto& decl : varDeclList.VarDeclList() ) {
		decl->Accept( *this );
	}
}

void CIRTreeVisitor::Visit( const CVarDecl& varDecl )
{
	// Здесь для IRTree ничего не нужно
	varDecl.VarType()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CMethodDeclList& methodDeclList )
{
	// Здесь для IRTree ничего не нужно
	for( const auto& decl : methodDeclList.MethodDeclList() ) {
		decl->Accept( *this );
	}
}

void CIRTreeVisitor::Visit( const CMethodDecl& methodDecl )
{
#pragma message( "TODO Здесь строится дерево для отдельной функции functions.push_back( new IRTree::CIRExp() )" )
	methodDecl.ReturnedType()->Accept( *this );
	if( methodDecl.FormalList() != 0 ) {
		methodDecl.FormalList()->Accept( *this );
	}
	if( methodDecl.VarDeclList() != 0 ) {
		methodDecl.VarDeclList()->Accept( *this );
	}
	if( methodDecl.StatementList() != 0 ) {
		methodDecl.StatementList()->Accept( *this );
	}
	if( methodDecl.ReturnedExp() != 0 ) {
		methodDecl.ReturnedExp()->Accept( *this );
	}
}

void CIRTreeVisitor::Visit( const CFormalList& formalList )
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

void CIRTreeVisitor::Visit( const CType& type )
{
	std::cout << type.TypeName();
}

void CIRTreeVisitor::Visit( const CStatementList& statementList )
{
	for( const auto& decl : statementList.StatmentList() ) {
		decl->Accept( *this );
		std::cout << std::endl;
	}
}

void CIRTreeVisitor::Visit( const CAssignStatement& assignStatement )
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

void CIRTreeVisitor::Visit( const CPrintStatement& printStatement )
{
	std::cout << "System.out.println( ";
	printStatement.Exp()->Accept( *this );
	std::cout << " );";
}

void CIRTreeVisitor::Visit( const CCurlyBraceStatement& curlyBraceStatement )
{
	std::cout << "{ " << std::endl;
	curlyBraceStatement.StatementList()->Accept( *this );
	std::cout << "}";
}

void CIRTreeVisitor::Visit( const CIfStatement& ifStatement )
{
	ifStatement.Exp()->Accept( *this );
	IRTree::IIRExp* ifExpr = lastReturnedExp;
	IRTree::CIRLabel* trueLabel = new IRTree::CIRLabel( new Temp::CLabel() );
	IRTree::CIRLabel* falseLabel = new IRTree::CIRLabel( new Temp::CLabel() );
	IRTree::CIRLabel* endLabel = new IRTree::CIRLabel( new Temp::CLabel() );
	ifStatement.IfStatement()->Accept( *this );
	IRTree::IIRStm* trueStm = new IRTree::CIRSeq( trueLabel, new IRTree::CIRSeq( lastReturnedStm, endLabel ) );
	IRTree::IIRStm* falseStm = 0;
	if( ifStatement.ElseStatement() != 0 ) {
		ifStatement.ElseStatement()->Accept( *this );
		falseStm = new IRTree::CIRSeq( falseLabel, new IRTree::CIRSeq( lastReturnedStm, endLabel ) );
	}
	// вызываем враппер 
	// lastReturnedStm = seq(wrapper.ToConditional, trueLabel, falseLabel)
}

void CIRTreeVisitor::Visit( const CWhileStatement& whileStatement )
{
	IRTree::CIRLabel* beforeConditionLabel = new IRTree::CIRLabel(new Temp::CLabel());
	IRTree::CIRLabel* inLoopLabel = new IRTree::CIRLabel(new Temp::CLabel());
	IRTree::CIRLabel* endLabel = new IRTree::CIRLabel(new Temp::CLabel());
	whileStatement.Exp()->Accept( *this );
	IRTree::IIRExp* whileExpr = lastReturnedExp;
	// Вместо whileExpr должен быть StmWrapper toConditional( inLoopLabel, endLabel)
	// jump перед inLoopLabel
	//IRTree::IIRStm* conditionStm = new IRTree::CIRSeq( beforeConditionLabel, new IRTree::CIRSeq( whileExpr, inLoopLabel ) );
	whileStatement.Statement()->Accept( *this );
	//lastReturnedStm = new IRTree::CIRSeq(conditionStm, new IRTree::CIRSeq(lastReturnedStm, endLabel));
}

void CIRTreeVisitor::Visit( const CExpList& expList )
{
#pragma message( "Здесь оборачиваем все ExpWrappero и строим для его ToExp Вложенные Seq" )
	for( const auto& decl : expList.ExpList() ) {
		decl->Accept( *this );
		std::cout << std::endl;
	}
}

} // namespace Translate