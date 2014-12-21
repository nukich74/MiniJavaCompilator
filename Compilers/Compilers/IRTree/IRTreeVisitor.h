// Автор: Воротилов Владислав
// Визитор для построения дерева промежуточного представления

#pragma once 
#include "Visitor.h"
#include "IRTree.h"
#include "IRExp.h"
#include "IRStm.h"
#include "IRHelpers.h"
#include <list>
#include <SymbolsTable.h>
#include "Frame.h"

using std::shared_ptr;
using std::string;
using std::vector;

namespace Translate {

class CIRTreeVisitor : public IVisitor {
public:

	CIRTreeVisitor( const SymbolsTable::CSymbolsTable& _symbolsTable ) : 
		currentFrame( 0 ), lastReturnedExp( 0 ), 
		lastReturnedStm( 0 ), lastReturnedAccess( 0 ),
		symbolsTable( _symbolsTable ) {}

	virtual void Visit( const CExpBinOpExp& exp );
	virtual void Visit( const CUnMinExp& exp );
	virtual void Visit( const CExpWithIndex& exp );
	virtual void Visit( const CExpDotLength& exp );
	virtual void Visit( const CExpIdExpList& exp );
	virtual void Visit( const CExpIdVoidExpList& exp );
	virtual void Visit( const CIntegerLiteral& exp );
	virtual void Visit( const CTrue& exp );
	virtual void Visit( const CFalse& exp );
	virtual void Visit( const CId& exp );
	virtual void Visit( const CThis& exp );
	virtual void Visit( const CNewIntExpIndex& exp );
	virtual void Visit( const CNewId& exp);
	virtual void Visit( const CNotExp& exp);
	virtual void Visit( const CExpInBrackets& exp);
	virtual void Visit( const CProgram& program);
	virtual void Visit( const CMainClass& mainClass);
	virtual void Visit( const CClassDeclList& classDeclList);
	virtual void Visit( const CClassDecl& classDecl);
	virtual void Visit( const CVarDeclList& varDeclList);
	virtual void Visit( const CVarDecl& varDecl);
	virtual void Visit( const CMethodDeclList& methodDeclList);
	virtual void Visit( const CMethodDecl& methodDecl);
	virtual void Visit( const CFormalList& formalList);
	virtual void Visit( const CType& type);
	virtual void Visit( const CStatementList& statementList);
	virtual void Visit( const CAssignStatement& assignStatement);
	virtual void Visit( const CPrintStatement& printStatement);
	virtual void Visit( const CCurlyBraceStatement& curlyBraceStatement);
	virtual void Visit( const CIfStatement& ifStatement);
	virtual void Visit( const CWhileStatement& whileStatement);
	virtual void Visit( const CExpList& expList);

private:
	// Каждой функции соответствует фрейм, его мы используем для поиска аргументов, типов и тд
	vector<shared_ptr<const Frame::CFrame> > functions;

	// Фрейм функции конструируемой в данный момент, создается при входе в функцию, добавляется в список при выходе
	shared_ptr<const Frame::CFrame> currentFrame;
	
	// Таблица символов для программы. Ее используем для конструирования фрейма при входе в функцию
	const SymbolsTable::CSymbolsTable& symbolsTable;

	// Нужно для того чтобы в CFrame записать правильно декорированное имя
	//	Имя декорируется className::functionName
	std::string className;

	shared_ptr<const IRTree::IExp> lastReturnedExp;
	shared_ptr<const IRTree::IStm> lastReturnedStm;
	shared_ptr<const Frame::IAccess> lastReturnedAccess;

};

} // namespace Translate