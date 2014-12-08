// Автор: Фролов Николай.

#include <TypeChecker.h>
#include <common.h>

using namespace SymbolsTable;

void CTypeChecker::Visit( const CProgram& program )
{
	program.MainClass()->Accept( *this );
	program.ClassDeclList()->Accept( *this );
}

void CTypeChecker::Visit( const CMainClass& mainClass )
{
	// currentClass = &( symbolsTable.Classes()[mainClass.MainClassName()] );
	currentMethod = &currentClass->Methods[0];
	mainClass.StatementList()->Accept( *this );
	currentMethod = 0;
	currentClass = 0;
}

void CTypeChecker::Visit( const CStatementList& statementList )
{
	for( auto& statement : statementList.StatmentList() ) {
		statement->Accept( *this );
	}
}

void CTypeChecker::Visit( const CAssignStatement& assignStatement )
{
	if( assignStatement.IndexExp() == 0 ) {
		if( !setLastTypeByIdentifier( assignStatement.LeftId() ) ) {
			// Ошибка - правая часть неопределена.
			return;
		}
		CTypeIdentifier leftType = lastType;
		assignStatement.RightExp()->Accept( *this );
		CTypeIdentifier rightType = lastType;
		if( leftType != rightType ) {
			// Ошибка - разные типы в равенстве.
			return;
		}
	} else {
		assignStatement.IndexExp()->Accept( *this );
		if( lastType != BT_IntArr ) {
			// Ошибка - индекс не является целочисленным.
			return;
		}
		if( !setLastTypeByIdentifier( assignStatement.LeftId() ) ) {
			// Ошибка - правая часть не определена.
			return;
		}
		CTypeIdentifier leftType = lastType;
		if( leftType != BT_IntArr ) {
			// Ошибка - пытаемся индексировать не массив int.
			return;
		}
		assignStatement.RightExp()->Accept( *this );
		if( lastType != BT_Int ) {
			// Ошибка - пытаемся элементу массива int присвоить не int.
		}
	}
}

void CTypeChecker::Visit( const CClassDeclList& classDeclList )
{
	for( auto& classDecl : classDeclList.ClassDeclList() ) {
		classDecl->Accept( *this );
	}
}

bool CTypeChecker::setLastTypeByIdentifier( const std::string& id ) const
{
	if( currentMethod != 0 ) {
		for( auto& localVariable : currentMethod->Locals ) {
			if( localVariable.Name() == id ) {
				lastType = localVariable.Type;
				return true;
			}
		}
		for( auto& paramVariable : currentMethod->Params ) {
			if( paramVariable.Name() == id ) {
				lastType = paramVariable.Type;
				return true;
			}
		}
	}
	if( currentClass != 0 ) {
		for( auto& fieldVariable : currentClass->Fields ) {
			if( fieldVariable.Name() == id ) {
				lastType = fieldVariable.Type;
				return true;
			}
		}
	}
	return false;
}