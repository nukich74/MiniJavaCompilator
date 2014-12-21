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
#include "IRExp.h"

using std::make_shared;

namespace Translate {

void CIRTreeVisitor::Visit( const CExpBinOpExp& exp )
{
	// Забираем правый и левый операнды
	exp.LeftArg()->Accept( *this );
	const IRTree::IExp* first = lastReturnedExp.get();
	exp.RightArg()->Accept( *this );
	const IRTree::IExp* second = lastReturnedExp.get();
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
	// Берем то что лежит по first, second и применяем бинарную операцию
	lastReturnedExp = make_shared<IRTree::IExp>( IRTree::CMem( new IRTree::CBinop( binOp, first, second ) ) );
}

void CIRTreeVisitor::Visit( const CUnMinExp& exp )
{
	// Как в лекциях заменяем на (0 - exp)
	const IRTree::IExp* first = new IRTree::CConst( 0 );
	exp.Exp()->Accept( *this );
	const IRTree::IExp* second = lastReturnedExp.get();
	// Аналогично binop
	lastReturnedExp = make_shared<IRTree::IExp>( new IRTree::CMem( new IRTree::CBinop( IRTree::B_Minus, first, second ) ) );
}

void CIRTreeVisitor::Visit( const CExpWithIndex& exp )
{
	exp.Exp()->Accept( *this );
	const IRTree::IExp* varExp = lastReturnedExp.get();
	exp.Index()->Accept( *this );
	const IRTree::IExp* indexExp = lastReturnedExp.get();
	IRTree::IExp* offset = new IRTree::CBinop( IRTree::B_Mul, new IRTree::CConst( Frame::CFrame::WordSize() ), new IRTree::CMem( indexExp ) );
	// Возвращаем адрес переменной
	lastReturnedExp = make_shared<IRTree::IExp>( new IRTree::CBinop( IRTree::B_Plus, varExp, offset ) );
}

void CIRTreeVisitor::Visit( const CExpDotLength& exp )
{
#pragma message( "TODO: Здесь надо возвращать IRTree::CConst переменной которую надо взять у SymbolTable" )
	// Во время компиляции уже известен размер каждого массива, он должен проверяться на корректность при валидации
	exp.Exp()->Accept( *this );
	const IRTree::IExp* varExp = lastReturnedExp.get();
	// Здесь будем запрашивать у фрейма длину
	// Пока сделаем константу 100500
	lastReturnedExp = make_shared<IRTree::IExp>( new IRTree::CConst( 100500 ) );
}

void CIRTreeVisitor::Visit( const CExpIdExpList& exp )
{
#pragma message( "TODO Возможно здесь надо что-то делать" )
	assert( currentFrame == 0 );
	//currentFrame = new Frame::CFrame( exp.Id() )
	// Больше ничего, всю остальную информацию уже знаем из таблицы символов
}

void CIRTreeVisitor::Visit( const CExpIdVoidExpList& exp )
{
#pragma message( "TODO Возможно здесь надо что-то делать" )
	// Заголовок функции без возвращаемого типа
	assert( currentFrame == 0 );
	//currentFrame = new Frame::CFrame( exp.Id() )
	// Больше ничего, всю остальную информацию уже знаем из таблицы символов
}

void CIRTreeVisitor::Visit( const CIntegerLiteral& exp )
{
	lastReturnedExp = make_shared<IRTree::IExp>( new IRTree::CConst( exp.Value() ) );
}

void CIRTreeVisitor::Visit( const CTrue& exp )
{
	// True у нас константа 1
	lastReturnedExp = make_shared<IRTree::IExp>( new IRTree::CConst( 1 ) );
}

void CIRTreeVisitor::Visit( const CFalse& exp )
{
	// False у нас константа 0
	lastReturnedExp = make_shared<IRTree::IExp>( new IRTree::CConst( 0 ) );
}

void CIRTreeVisitor::Visit( const CId& exp )
{
	// Найдем нужную инфу во фрейме
	lastReturnedAccess = currentFrame->GetAccess( exp.Id() );
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
	lastReturnedExp = make_shared<IRTree::IExp>(new IRTree::CBinop( IRTree::B_Xor, 
		new IRTree::CConst( 0 ), new IRTree::CMem( lastReturnedExp.get() ) ) );
}

void CIRTreeVisitor::Visit( const CExpInBrackets& exp )
{
#pragma message( "TODO Здесь нужно чтобы тот кому выражение принадлежит забрал lastReturnedExp" )
	// Строится exp list
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
	className = mainClass.MainClassName();
	if( mainClass.StatementList() != 0 ) {
		mainClass.StatementList()->Accept( *this );
	}
	className = "";
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
	className = classDecl.ClassId();
	if( classDecl.VarDeclList() != 0 ) {
		classDecl.VarDeclList()->Accept( *this );
	}
	if( classDecl.MethodDeclList() != 0 ) {
		classDecl.MethodDeclList()->Accept( *this );
	}
	className = "";
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
	// Здесь для IRTree ничего не нужно
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
	const IRTree::IExp* ifExpr = lastReturnedExp.get();
	Temp::CLabel* trueLabelTemp = new Temp::CLabel();
	Temp::CLabel* falseLabelTemp = new Temp::CLabel();
	Temp::CLabel* endLabelTemp = new Temp::CLabel();
	IRTree::CLabel* trueLabel = new IRTree::CLabel( trueLabelTemp );
	IRTree::CLabel* falseLabel = new IRTree::CLabel( falseLabelTemp );
	IRTree::CLabel* endLabel = new IRTree::CLabel( endLabelTemp );
	ifStatement.IfStatement()->Accept( *this );
	IRTree::IStm* trueStm = new IRTree::CSeq( trueLabel, lastReturnedStm.get(), endLabel );
	IRTree::IStm* falseStm = 0;
	if( ifStatement.ElseStatement() != 0 ) {
		ifStatement.ElseStatement()->Accept( *this );
		falseStm = new IRTree::CSeq( falseLabel, lastReturnedStm.get(), endLabel );
	}
	Translate::CExpConverter converter( ifExpr );
	lastReturnedStm = std::make_shared<IRTree::IStm>( converter.ToConditional( trueLabelTemp, falseLabelTemp ) );
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
	Translate::CExpConverter converter( lastReturnedExp.get() );
	const IRTree::IStm* whileStm = converter.ToConditional( inLoopLabelTemp, endLabelTemp );
	IRTree::IStm* conditionStm = new IRTree::CSeq( beforeConditionLabel, whileStm, inLoopLabel );
	whileStatement.Statement()->Accept( *this );
	lastReturnedStm = make_shared<IRTree::IStm>( new IRTree::CSeq( conditionStm, lastReturnedStm.get(), 
		new IRTree::CJump( beforeConditionLabelTemp ), endLabel ) );
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