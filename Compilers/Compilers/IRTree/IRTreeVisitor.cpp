// Автор: Воротилов Владислав
// Визитор для построения дерева промежуточного представления


#include "IRTreeVisitor.h"
#include <Exp.h>
#include <iostream>
#include <string>
#include <cassert>
#include <common.h>
#include <Visitor.h>
#include "ExpConverter.h"

namespace Translate {

void CIRTreeVisitor::Visit( const CExpBinOpExp& exp )
{
	// Забираем правый и левый операнды
	exp.LeftArg()->Accept( *this );
	IRTree::IExp* first = lastReturnedExp;
	exp.RightArg()->Accept( *this );
	IRTree::IExp* second = lastReturnedExp;
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
	lastReturnedExp = new IRTree::CBinop( binOp, first, second );
}

void CIRTreeVisitor::Visit( const CUnMinExp& exp )
{
	// Как в лекциях заменяем на (0 - exp)
	IRTree::IExp* first = new IRTree::CConst( 0 );
	exp.Exp()->Accept( *this );
	IRTree::IExp* second = lastReturnedExp;
	lastReturnedExp = new IRTree::CBinop( IRTree::B_Minus, first, second );
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
#pragma message( "TODO Возможно здесь надо что-то делать" )
	// Это заголовок функции с возвращаемым типом
	exp.Exp()->Accept( *this );
	exp.ExpList()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CExpIdVoidExpList& exp )
{
#pragma message( "TODO Возможно здесь надо что-то делать" )
	// Заголовок функции без возвращаемого типа
	exp.Exp()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CIntegerLiteral& exp )
{
	lastReturnedExp = new IRTree::CConst( exp.Value() );
}

void CIRTreeVisitor::Visit( const CTrue& exp )
{
	// True у нас константа 1
	lastReturnedExp = new IRTree::CConst( 1 );
}

void CIRTreeVisitor::Visit( const CFalse& exp )
{
	// False у нас константа 0
	lastReturnedExp = new IRTree::CConst( 0 );
}

void CIRTreeVisitor::Visit( const CId& exp )
{
	// Здесь ничего делать не нужно, вся инфа о типах у таблицы символов, спросим у нее
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
	// Получаем lastReturnedExp и записываем туда конструкцию XOR c Const(0)
	exp.Exp()->Accept( *this );
	lastReturnedExp = new IRTree::CBinop( IRTree::B_Xor, new IRTree::CConst( 0 ), lastReturnedExp );
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
	// Запоминаем в каком мы классе
	// Чтобы в MethodDescriptor нужного класса записать IRTree*
	currentClass = &( symbolsTable.Classes().at( mainClass.MainClassName() ) );
	if( mainClass.StatementList() != 0 ) {
		mainClass.StatementList()->Accept( *this );
	}
	currentClass = 0;
	currentMethod = 0;
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
#pragma message( "TODO Возможно здесь надо что-то делать" )
	// Запоминаем в каком мы классе
	currentClass = &( symbolsTable.Classes( ).at( classDecl.ClassId( ) ) );
	if( classDecl.VarDeclList() != 0 ) {
		classDecl.VarDeclList()->Accept( *this );
	}
	if( classDecl.MethodDeclList() != 0 ) {
		classDecl.MethodDeclList()->Accept( *this );
	}
	currentClass = 0;
	currentMethod = 0;
}

void CIRTreeVisitor::Visit( const CVarDeclList& varDeclList )
{
#pragma message( "TODO Возможно здесь надо что-то делать" )
	// Здесь для IRTree ничего не нужно
	for( const auto& decl : varDeclList.VarDeclList() ) {
		decl->Accept( *this );
	}
}

void CIRTreeVisitor::Visit( const CVarDecl& varDecl )
{
#pragma message( "TODO Возможно здесь надо что-то делать" )
	varDecl.VarType()->Accept( *this );
}

void CIRTreeVisitor::Visit( const CMethodDeclList& methodDeclList )
{
#pragma message( "TODO Возможно здесь надо что-то делать" )
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
#pragma message( "TODO Возможно здесь надо что-то делать" )
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
#pragma message( "TODO Возможно здесь надо что-то делать" )
	std::cout << type.TypeName();
}

void CIRTreeVisitor::Visit( const CStatementList& statementList )
{
#pragma message( "TODO Возможно здесь надо что-то делать" )
	for( const auto& decl : statementList.StatmentList() ) {
		decl->Accept( *this );
		std::cout << std::endl;
	}
}

void CIRTreeVisitor::Visit( const CAssignStatement& assignStatement )
{
#pragma message( "TODO Возможно здесь надо что-то делать" )
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
#pragma message( "TODO Возможно здесь надо что-то делать" )
	std::cout << "System.out.println( ";
	printStatement.Exp()->Accept( *this );
	std::cout << " );";
}

void CIRTreeVisitor::Visit( const CCurlyBraceStatement& curlyBraceStatement )
{
#pragma message( "TODO Возможно здесь надо что-то делать" )
	// Возможно здесь надо что-то делать с frame pointer
	std::cout << "{ " << std::endl;
	curlyBraceStatement.StatementList()->Accept( *this );
	std::cout << "}";
}

void CIRTreeVisitor::Visit( const CIfStatement& ifStatement )
{
	ifStatement.Exp()->Accept( *this );
	IRTree::IExp* ifExpr = lastReturnedExp;
	Temp::CLabel* trueLabelTemp = new Temp::CLabel();
	Temp::CLabel* falseLabelTemp = new Temp::CLabel();
	Temp::CLabel* endLabelTemp = new Temp::CLabel();
	IRTree::CLabel* trueLabel = new IRTree::CLabel( trueLabelTemp );
	IRTree::CLabel* falseLabel = new IRTree::CLabel( falseLabelTemp );
	IRTree::CLabel* endLabel = new IRTree::CLabel( endLabelTemp );
	ifStatement.IfStatement()->Accept( *this );
	IRTree::IStm* trueStm = new IRTree::CSeq( trueLabel, lastReturnedStm, endLabel );
	IRTree::IStm* falseStm = 0;
	if( ifStatement.ElseStatement() != 0 ) {
		ifStatement.ElseStatement()->Accept( *this );
		falseStm = new IRTree::CSeq( falseLabel, lastReturnedStm, endLabel );
	}
	Translate::CExpConverter converter( ifExpr );
	lastReturnedStm = converter.ToConditional( trueLabelTemp, falseLabelTemp );
}

void CIRTreeVisitor::Visit( const CWhileStatement& whileStatement )
{
	Temp::CLabel* beforeConditionLabelTemp = new Temp::CLabel();
	Temp::CLabel* inLoopLabelTemp = new Temp::CLabel();
	Temp::CLabel* endLabelTemp = new Temp::CLabel();
	IRTree::CLabel* beforeConditionLabel = new IRTree::CLabel(new Temp::CLabel());
	IRTree::CLabel* inLoopLabel = new IRTree::CLabel(new Temp::CLabel());
	IRTree::CLabel* endLabel = new IRTree::CLabel(new Temp::CLabel());
	whileStatement.Exp()->Accept( *this );
	Translate::CExpConverter converter( lastReturnedExp );
	IRTree::IStm* whileStm = converter.ToConditional( inLoopLabelTemp, endLabelTemp );
	IRTree::IStm* conditionStm = new IRTree::CSeq( beforeConditionLabel, whileStm, inLoopLabel );
	whileStatement.Statement()->Accept( *this );
	lastReturnedStm = new IRTree::CSeq( conditionStm, lastReturnedStm, new IRTree::CJump( beforeConditionLabelTemp ), endLabel );
}

void CIRTreeVisitor::Visit( const CExpList& expList )
{
#pragma message( "Не ясно что делать" )
	for( const auto& decl : expList.ExpList() ) {
		decl->Accept( *this );
		std::cout << std::endl;
	}
}

} // namespace Translate