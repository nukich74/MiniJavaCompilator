// Автор: Воротилов Владислав
// Визитор для построения дерева промежуточного представления


#include "IRForestBuilder.h"
#include <Exp.h>
#include <iostream>
#include <string>
#include <stack>
#include <cassert>
#include <common.h>
#include <Visitor.h>
#include "ExpConverter.h"
#include "IRExp.h"
#include "StmConverter.h"

namespace Translate {

void CIRForestBuilder::Visit( const CExpBinOpExp& exp )
{
	// Забираем правый и левый операнды
	exp.LeftArg()->Accept( *this );
	const IRTree::IExp* first = lastReturnedExp;
	exp.RightArg()->Accept( *this );
	const IRTree::IExp* second = lastReturnedExp;
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
		case '/':
			binOp = IRTree::B_Division;
			break;
		case '^':
			binOp = IRTree::B_Xor;
			break;
		case '<':
			binOp = IRTree::B_Less;
			break;
		case '>':
			binOp = IRTree::B_Greater;
			break;
		case '&':
			binOp = IRTree::B_And;
			break;
		default:
			assert( false );
	}
	// Берем то что лежит по first, second и применяем бинарную операцию
	lastReturnedExp = new IRTree::CMem( new IRTree::CBinop( binOp, first, second ) ) ;
}

void CIRForestBuilder::Visit( const CUnMinExp& exp )
{
	// Как в лекциях заменяем на (0 - exp)
	const IRTree::IExp* first = new IRTree::CConst( 0 );
	exp.Exp()->Accept( *this );
	const IRTree::IExp* second = lastReturnedExp;
	// Аналогично binop
	lastReturnedExp = new IRTree::CMem( new IRTree::CBinop( IRTree::B_Minus, first, second ) );
}

void CIRForestBuilder::Visit( const CExpWithIndex& exp )
{
	exp.Exp()->Accept( *this );
	const IRTree::IExp* varExp = lastReturnedExp;
	lastReturnedExp = nullptr;
	exp.Index()->Accept( *this );
	const IRTree::IExp* indexExp = new IRTree::CBinop( IRTree::B_Plus, new IRTree::CMem( lastReturnedExp ), new IRTree::CConst( 1 ) );
	lastReturnedExp = nullptr;
	IRTree::IExp* offset = new IRTree::CBinop( IRTree::B_Mul, new IRTree::CConst( Frame::CFrame::WordSize() ), indexExp );
	// Возвращаем адрес переменной
	lastReturnedExp =  new IRTree::CBinop( IRTree::B_Plus, varExp, offset );
}

void CIRForestBuilder::Visit( const CExpDotLength& exp )
{
	// Во время компиляции уже известен размер каждого массива, он должен проверяться на корректность при валидации
	exp.Exp()->Accept( *this );
	const IRTree::IExp* varExp = lastReturnedExp;
	lastReturnedExp = nullptr;
	const IRTree::IExp* lengthCommandRW = new IRTree::CBinop( IRTree::B_Plus, varExp, new IRTree::CConst( 0 ) );
	// Создаем временную переменную
	const Temp::CTemp* lengthTemp = new Temp::CTemp();
	const IRTree::CTemp* tempVar = new IRTree::CTemp( *lengthTemp );
	// Копируем значение туда
	const IRTree::CMove* movingCommand = new IRTree::CMove( tempVar, lengthCommandRW );
	// Возвращаем адрес переменной
	lastReturnedExp = new IRTree::CEseq( movingCommand, tempVar );
}

void CIRForestBuilder::Visit( const CExpIdExpList& exp )
{
	// Вычисляем выражение к которому надо применить метод
	exp.Exp()->Accept( *this );
	const IRTree::IExp* exprToBeCalled = lastReturnedExp;
	lastReturnedExp = nullptr;
	// Это просто метод который надо вызвать
	std::string methodName = exp.Id();
	Temp::CLabel* functionLabel = new Temp::CLabel( methodName );
	IRTree::CName* functionName = new IRTree::CName( functionLabel );
	const IRTree::CExpList* args;
	if( exp.ExpList() != 0 ) {
		exp.ExpList()->Accept( *this );
		args = lastReturnedExpList;
	}
	else {
		args = new IRTree::CExpList( nullptr, nullptr );
	}
#pragma message( "TODO Здесь все сложнее чем сейчас сделано" )
	Temp::CTemp* returned = new Temp::CTemp();
	const IRTree::CTemp* returnedTemp = new IRTree::CTemp( *returned );
	// Только если функция возвращает значени иначе просто будет stm
	lastReturnedExp = new IRTree::CEseq(new IRTree::CMove( returnedTemp, new IRTree::CCall( functionName, *lastReturnedExpList ) ), returnedTemp );
	lastReturnedExpList = nullptr;

}

void CIRForestBuilder::Visit( const CExpIdVoidExpList& exp )
{
	// Вызов функции без аргументов
	// Вычисляем выражение к которому надо применить метод
	exp.Exp()->Accept( *this );
	const IRTree::IExp* exprToBeCalled = lastReturnedExp;
	lastReturnedExp = nullptr;
	// Это просто метод который надо вызвать
	std::string methodName = exp.Id();
	Temp::CLabel* functionLabel = new Temp::CLabel( methodName );
	IRTree::CName* functionName = new IRTree::CName( functionLabel );
	const IRTree::CExpList* args = new IRTree::CExpList( nullptr, nullptr );
#pragma message( "TODO Здесь все сложнее чем сейчас сделано" )
	Temp::CTemp* returned = new Temp::CTemp();
	const IRTree::CTemp* returnedTemp = new IRTree::CTemp( *returned );
	// Только если функция возвращает значени иначе просто будет stm
	lastReturnedExp = new IRTree::CEseq( new IRTree::CMove( returnedTemp, new IRTree::CCall( functionName, *lastReturnedExpList ) ), returnedTemp );
	lastReturnedExpList = nullptr;
}

void CIRForestBuilder::Visit( const CIntegerLiteral& exp )
{
	lastReturnedExp = new IRTree::CConst( exp.Value() );
}

void CIRForestBuilder::Visit( const CTrue& exp )
{
	// True у нас константа 1
	lastReturnedExp = new IRTree::CConst( 1 );
}

void CIRForestBuilder::Visit( const CFalse& exp )
{
	// False у нас константа 0
	lastReturnedExp = new IRTree::CConst( 0 );
}

void CIRForestBuilder::Visit( const CId& exp )
{
	// Найдем нужную инфу во фрейме
	lastReturnedExp = currentFrame->GetAccess( exp.Id() )->ToExp( currentFrame );
}

void CIRForestBuilder::Visit( const CThis& exp )
{
	lastReturnedExp = new IRTree::CTemp( *currentFrame->ThisPointer() );
}

void CIRForestBuilder::Visit( const CNewIntExpIndex& exp )
{
#pragma message( "TODO Здесь все сложнее чем сейчас сделано" )
	exp.Exp()->Accept( *this );
	const IRTree::IExp* lengthOfArrray = lastReturnedExp;
	lastReturnedExp = nullptr;
	const IRTree::IExp* lengthDeFacto = new IRTree::CMem( new IRTree::CBinop( IRTree::B_Plus, lengthOfArrray, new IRTree::CConst( 1 ) ) );
	// Выделяем память
	Temp::CLabel* mallocLabel = new Temp::CLabel( "malloc" );
	const IRTree::CName* mallocName = new IRTree::CName( mallocLabel );
	const IRTree::CCall* mallocCall = new IRTree::CCall( mallocName, *( new IRTree::CExpList( lengthDeFacto, nullptr ) ) );
	Temp::CTemp* resultTemp = new Temp::CTemp();
	const IRTree::CTemp* tempTemp = new IRTree::CTemp( *resultTemp );
	// Проставляем память нулями
	const IRTree::CCall* memSetCall = nullptr;
	const IRTree::CSeq* mallocMoveMemset = new IRTree::CSeq( new IRTree::CMove( tempTemp, mallocCall ), 
		new IRTree::CMove( tempTemp, lengthOfArrray ) , new IRTree::CExp( memSetCall ) );
	lastReturnedExp = new IRTree::CEseq( mallocMoveMemset, tempTemp );
}
void CIRForestBuilder::Visit( const CNewId& exp )
{
#pragma message( "TODO Здесь все сложнее чем сейчас сделано" )
	// Выделяем память
	Temp::CLabel* mallocLabel = new Temp::CLabel( "malloc" );
	// По хорошему здесь надо посчитать сколько всего полей у класса и выделить столько машинных слов
	const IRTree::CName* mallocName = new IRTree::CName( mallocLabel );
	const IRTree::CCall* mallocCall = new IRTree::CCall( mallocName, *(new IRTree::CExpList( new IRTree::CConst( 100500 ), nullptr ) ) );
	Temp::CTemp* resultTemp = new Temp::CTemp();
	const IRTree::CTemp* tempTemp = new IRTree::CTemp( *resultTemp );
	// Проставляем память нулями
	const IRTree::CCall* memSetCall = nullptr;
	const IRTree::CSeq* mallocMoveMemset = new IRTree::CSeq( new IRTree::CMove( tempTemp, mallocCall ), new IRTree::CExp( memSetCall ) );
	lastReturnedExp = new IRTree::CEseq( mallocMoveMemset, tempTemp );

}

void CIRForestBuilder::Visit( const CNotExp& exp )
{
	// Получаем lastReturnedExp и записываем туда конструкцию XOR c Const(0)
	exp.Exp()->Accept( *this );
	lastReturnedExp = new IRTree::CBinop( IRTree::B_Xor, 
		new IRTree::CConst( 0 ), new IRTree::CMem( lastReturnedExp ) );
}

void CIRForestBuilder::Visit( const CExpInBrackets& exp )
{
	// Здесь все и так нормально, тут сохраняется lastReturnedExp
	exp.Exp()->Accept( *this );
}

void CIRForestBuilder::Visit( const CProgram& program )
{
	// Здесь для IRTree ничего не нужно
	program.MainClass()->Accept( *this );
	if( program.ClassDeclList() != 0 ) {
		program.ClassDeclList()->Accept( *this );
	}
	
}

void CIRForestBuilder::Visit( const CMainClass& mainClass )
{
	// Запоминаем в каком мы классе
	className = mainClass.MainClassName();
	// У main нет никаких переменных, потому что такая грамматика
	//	Программу можно будет начать если сделать временный объект какого нибудь класса
	//	например System.out.println( new Pr1() );
	currentFrame = new Frame::CFrame( className + ":main" );
	if( mainClass.StatementList() != 0 ) {
		mainClass.StatementList()->Accept( *this );
	}
	currentFrame->Stm = lastReturnedStm;
	lastReturnedStm = nullptr;
	lastReturnedExp = nullptr;
	Methods.push_back( currentFrame );
	// Очищаем инфу о текущем фрейме
	currentFrame = 0;
	className = "";
}

void CIRForestBuilder::Visit( const CClassDeclList& classDeclList )
{
	// Здесь для IRTree ничего не нужно
	for( const auto& clsDecl : classDeclList.ClassDeclList() ) {
		clsDecl->Accept( *this );
	}
}

void CIRForestBuilder::Visit( const CClassDecl& classDecl )
{
	// Запоминаем в каком мы классе
	className = classDecl.ClassId();
	if( classDecl.VarDeclList() != 0 ) {
		classDecl.VarDeclList()->Accept( *this );
	}
	if( classDecl.MethodDeclList() != 0 ) {
		classDecl.MethodDeclList()->Accept( *this );
	}
	lastReturnedExp = nullptr;
	lastReturnedStm = nullptr;
	className = "";
}

void CIRForestBuilder::Visit( const CVarDeclList& varDeclList )
{
	// Здесь для IRTree ничего не нужно
	for( const auto& decl : varDeclList.VarDeclList() ) {
		decl->Accept( *this );
	}
}

void CIRForestBuilder::Visit( const CVarDecl& varDecl )
{
	// Здесь для IRTree ничего не нужно
	varDecl.VarType()->Accept( *this );
}

void CIRForestBuilder::Visit( const CMethodDeclList& methodDeclList )
{
	// Здесь для IRTree ничего не нужно
	for( const auto& decl : methodDeclList.MethodDeclList() ) {
		decl->Accept( *this );
	}
}


void CIRForestBuilder::Visit( const CMethodDecl& methodDecl )
{
	// Все это мы игнорируем, это есть у теблицы символоа
	methodDecl.ReturnedType()->Accept( *this );
	if( methodDecl.FormalList() != 0 ) {
		methodDecl.FormalList()->Accept( *this );
	}
	if( methodDecl.VarDeclList() != 0 ) {
		methodDecl.VarDeclList()->Accept( *this );
	}
	// Строим фрейм
	currentFrame = new Frame::CFrame( className + ":" + methodDecl.MethodName() );
	std::vector<const SymbolsTable::CClassDescriptor*> classNames;
	const SymbolsTable::CClassDescriptor* currentClass = &symbolsTable.Classes().at( className );
	while( currentClass != nullptr ) {
		classNames.push_back( currentClass );
		if( !currentClass->BaseClass.empty() ) {
			currentClass = &( symbolsTable.Classes().at( currentClass->BaseClass ) );
		} else {
			currentClass = nullptr;
		}
	}
	// Добавляем поля класса к фрейму symbolsTable.Classes().at( className )
	for( int i = classNames.size() - 1; i >= 0; i-- ) {
		for( const auto& field : classNames.at( i )->Fields ) {
			currentFrame->AddField( field.Name(), new Frame::CInObject( currentFrame->ThisCounter ) );
			currentFrame->ThisCounter++;
		}
	}
	// Добавил костыль, ибо не компилится - в ClassDecsriptor методы и переменные хранятся в массивах а не map.
	// Если не конструкция вам не по душе можете выделить в отдельный метод, либо развлечься иным способом.
	const std::vector<SymbolsTable::CVariableDescriptor>* params = nullptr;
	const std::vector<SymbolsTable::CVariableDescriptor>* locals = nullptr;
	for( auto& method : symbolsTable.Classes( ).at( className ).Methods ) {
		if( method.Name() == methodDecl.MethodName() ) {
			params = &method.Params;
			locals = &method.Locals;
			break;
		}
	}
	
	// Добавляем параметры функции фрейму
	for( const auto& field : *params ) {
		currentFrame->AddField( field.Name(), new Frame::CInFrame( currentFrame->LocalCounter ) );
		currentFrame->LocalCounter++;
	}
	// Добавляем локальные переменные фрейму
	for( const auto& field : *locals ) {
		currentFrame->AddField( field.Name(), new Frame::CInFrame( currentFrame->LocalCounter ) );
		currentFrame->LocalCounter++;
	}
	if( methodDecl.StatementList() != 0 ) {
		methodDecl.StatementList()->Accept( *this );
		// после этой строки есть сам код
	}
	if( methodDecl.ReturnedExp() != 0 ) {
		// Это обрабатываем как возвращаемое значение, оно проставляется return 
		// Переносим lastReturnedValue в регистр если оно было
		methodDecl.ReturnedExp()->Accept( *this );
		if( lastReturnedExp != nullptr ) {
			if( lastReturnedStm != nullptr ) {
				lastReturnedStm = new IRTree::CSeq( lastReturnedStm, new IRTree::CMove( new IRTree::CTemp( *currentFrame->ReturnValue() ), lastReturnedExp ) );
			} else {
				lastReturnedStm = new IRTree::CMove( new IRTree::CTemp( *currentFrame->ReturnValue() ), lastReturnedExp);
			}
			
		}
	}
	currentFrame->Stm = lastReturnedStm;
	Methods.push_back( currentFrame );
	currentFrame = nullptr;
	lastReturnedStm = nullptr;
	lastReturnedExp = nullptr;
}

void CIRForestBuilder::Visit( const CFormalList& formalList )
{
	// Эта инфа у таблицы символов
	// Нам тут делать нечего
	for( auto ptr = formalList.FormalList().begin(); ptr != formalList.FormalList().end(); ++ptr ) {
		ptr->first->Accept( *this );
	}
}

void CIRForestBuilder::Visit( const CType& type )
{
	// Здесь для IRTree ничего не нужно
	// Все у таблицы символов
}

void CIRForestBuilder::Visit( const CStatementList& statementList )
{
	// Предполагается что есть хоть какие то statement
	//assert( statementList.StatmentList().size() > 0 );
	const IRTree::IStm* listOfStm = nullptr;
	// Выполняем первый
	statementList.StatmentList().front()->Accept( *this );
	listOfStm = lastReturnedStm;
	lastReturnedStm = nullptr;
	lastReturnedExp = nullptr;
	if( statementList.StatmentList().size() == 1 ) {
		lastReturnedStm = listOfStm;
		return;
	} else {
		auto iter = statementList.StatmentList().begin();
		iter++;
		// начинаем после прервого!
		for( ; iter != statementList.StatmentList().end(); iter++ ) {
			(*iter)->Accept( *this );
			const IRTree::IStm* statementToAdd = 0;
			if( lastReturnedStm == 0 ) {
				// Нам нужны только IStm потому юзаем конвертер
				Translate::CExpConverter converter( lastReturnedExp );
				statementToAdd = converter.ToStm();
			} else {
				statementToAdd = lastReturnedStm;
			}
			listOfStm = new IRTree::CSeq( listOfStm, statementToAdd );
			lastReturnedStm = nullptr;
			lastReturnedExp = nullptr;
		}
		lastReturnedStm = listOfStm;
	}
}

void CIRForestBuilder::Visit( const CAssignStatement& assignStatement )
{
	const IRTree::IExp* leftExp = currentFrame->GetAccess( assignStatement.LeftId() )->ToExp( currentFrame );
	if( assignStatement.IndexExp() != 0 ) {
		assignStatement.IndexExp()->Accept( *this );
		const IRTree::IExp* index = new IRTree::CMem( new IRTree::CBinop( IRTree::B_Plus, lastReturnedExp, new IRTree::CConst( 1 ) ) );
		leftExp = new IRTree::CMem( new IRTree::CBinop( IRTree::B_Plus, leftExp, index ) );
	}
	assignStatement.RightExp()->Accept( *this );
	const IRTree::IExp* rightExp = lastReturnedExp;
	lastReturnedExp = nullptr;
	lastReturnedStm = new IRTree::CMove( leftExp, rightExp );
}

void CIRForestBuilder::Visit( const CPrintStatement& printStatement )
{
	// Вычисляем то что надо напечатать
	printStatement.Exp()->Accept( *this );
	const IRTree::IExp* exprForPrint = lastReturnedExp;
	lastReturnedExp = nullptr;
	lastReturnedStm = nullptr;
	// Вызываем функцию
	Temp::CLabel* funcName = new Temp::CLabel( "System.out.println" );
	const IRTree::CName* funcNameTree = new IRTree::CName( funcName );
	const IRTree::CExpList* args = new IRTree::CExpList( exprForPrint, nullptr );
	const IRTree::IExp* funcCall = new IRTree::CCall( funcNameTree, *args );
	lastReturnedStm = new IRTree::CExp( funcCall );
}

void CIRForestBuilder::Visit( const CCurlyBraceStatement& curlyBraceStatement )
{
	// Здесь ничего делать не нужно, это обрамление из фигурных скобок для StatementList
	curlyBraceStatement.StatementList()->Accept( *this );
}

void CIRForestBuilder::Visit( const CIfStatement& ifStatement )
{
	ifStatement.Exp()->Accept( *this );
	const IRTree::IExp* ifExpr = lastReturnedExp;
	lastReturnedExp = nullptr;
	lastReturnedStm = nullptr;
	Temp::CLabel* trueLabelTemp = new Temp::CLabel();
	Temp::CLabel* falseLabelTemp = new Temp::CLabel();
	Temp::CLabel* endLabelTemp = new Temp::CLabel();
	IRTree::CLabel* trueLabel = new IRTree::CLabel( trueLabelTemp );
	IRTree::CLabel* falseLabel = new IRTree::CLabel( falseLabelTemp );
	IRTree::CLabel* endLabel = new IRTree::CLabel( endLabelTemp );
	ifStatement.IfStatement()->Accept( *this );
	IRTree::IStm* trueStm = new IRTree::CSeq( trueLabel, lastReturnedStm, endLabel );
	lastReturnedExp = nullptr;
	lastReturnedStm = nullptr;
	IRTree::IStm* falseStm = 0;
	if( ifStatement.ElseStatement() != 0 ) {
		ifStatement.ElseStatement()->Accept( *this );
		falseStm = new IRTree::CSeq( falseLabel, lastReturnedStm, endLabel );
		lastReturnedExp = nullptr;
		lastReturnedStm = nullptr;
	}
	Translate::CExpConverter converter( ifExpr );
	// Предполагается что ToConditional правильно обрабатывает если второй аргумент 0
	lastReturnedStm = new IRTree::CSeq( converter.ToConditional( trueLabelTemp, falseLabelTemp ), trueStm, falseStm );
}

void CIRForestBuilder::Visit( const CWhileStatement& whileStatement )
{
	Temp::CLabel* beforeConditionLabelTemp = new Temp::CLabel();
	Temp::CLabel* inLoopLabelTemp = new Temp::CLabel();
	Temp::CLabel* endLabelTemp = new Temp::CLabel();
	IRTree::CLabel* beforeConditionLabel = new IRTree::CLabel(new Temp::CLabel());
	IRTree::CLabel* inLoopLabel = new IRTree::CLabel(new Temp::CLabel());
	IRTree::CLabel* endLabel = new IRTree::CLabel(new Temp::CLabel());
	whileStatement.Exp()->Accept( *this );
	Translate::CExpConverter converter( lastReturnedExp );
	const IRTree::IStm* whileStm = converter.ToConditional( inLoopLabelTemp, endLabelTemp );
	lastReturnedExp = nullptr;
	lastReturnedStm = nullptr;
	IRTree::IStm* conditionStm = new IRTree::CSeq( beforeConditionLabel, whileStm, inLoopLabel );
	whileStatement.Statement()->Accept( *this );
	lastReturnedStm = new IRTree::CSeq( conditionStm, lastReturnedStm, 
		new IRTree::CJump( beforeConditionLabelTemp ), endLabel );
	lastReturnedExp = nullptr;
}

void CIRForestBuilder::Visit( const CExpList& expList )
{
	const IRTree::CExpList* irExpList = nullptr;
	for( const auto& decl : expList.ExpList() ) {
		decl->Accept( *this );
		irExpList = new IRTree::CExpList( lastReturnedExp, irExpList );
	}
	lastReturnedExpList = irExpList;
}

} // namespace Translate