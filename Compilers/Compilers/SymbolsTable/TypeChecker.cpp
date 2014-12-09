// Автор: Фролов Николай.

#include <TypeChecker.h>
#include <common.h>
#include <set>

using namespace SymbolsTable;

void CTypeChecker::Visit( const CProgram& program )
{
	program.MainClass()->Accept( *this );
	program.ClassDeclList()->Accept( *this );
}

void CTypeChecker::Visit( const CMainClass& mainClass )
{
	currentClass = &( symbolsTable.Classes().at( mainClass.MainClassName() ) );
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


void CTypeChecker::Visit( const CPrintStatement& printStatement )
{
	printStatement.Exp()->Accept( *this );
	if( lastType != BT_Int ) {
		// Ошибка - пытаемся печатать не int.
	}
}

void CTypeChecker::Visit( const CCurlyBraceStatement& curlyBraceStatement )
{
	curlyBraceStatement.StatementList()->Accept( *this );
}

void CTypeChecker::Visit( const CIfStatement& ifStatement )
{
	ifStatement.Exp()->Accept( *this );
	if( lastType != BT_Bool ) {
		// Ошибка - выражение в this не булево.
	}
	ifStatement.IfStatement()->Accept( *this );
	ifStatement.ElseStatement()->Accept( *this );
}

void CTypeChecker::Visit( const CWhileStatement& whileStatement )
{
	whileStatement.Exp()->Accept( *this );
	if( lastType != BT_Bool ) {
		// Ошибка - выражение в while не bool.
	}
	whileStatement.Statement()->Accept( *this );
}

void CTypeChecker::Visit( const CExpList& expList )
{
	for( auto& exp : expList.ExpList() ) {
		exp->Accept( *this );
	}
}

void CTypeChecker::Visit( const CExpBinOpExp& exp )
{
	if( exp.Operation() == '&' ) {
		exp.LeftArg()->Accept( *this );
		if( lastType != BT_Bool ) {
			// Ошибка - аргумент для И не булевский.
		}
		exp.RightArg()->Accept( *this );
		if( lastType != BT_Bool ) {
			// Ошибка - аргумент для И не булевский.
		}
		lastType = BT_Bool;
	} else {
		exp.LeftArg()->Accept( *this );
		if( lastType != BT_Int ) {
			// Ошибка - аргумент арифметической операции не int.
		}
		exp.RightArg()->Accept( *this );
		if( lastType != BT_Int ) {
			// Ошибка - аргумент арифметической операции не int.
		}
		lastType = BT_Int;
	}
}

void CTypeChecker::Visit( const CUnMinExp& exp )
{
	exp.Accept( *this );
	if( lastType != BT_Int ) {
		// Ошибка - применяем унарный минус не к целому числу.
	}
	lastType = BT_Int;
}

void CTypeChecker::Visit( const CExpWithIndex& exp )
{
	exp.Exp()->Accept( *this );
	if( lastType != BT_IntArr ) {
		// Ошибка - пытаемся взять индекс не у массива.
	}
	exp.Index()->Accept( *this );
	if( lastType != BT_Int ) {
		// Ошибка - индекс не целочисленный.
	}
	lastType = BT_Int;
}

void CTypeChecker::Visit( const CExpDotLength& exp )
{
	exp.Exp()->Accept( *this );
	if( lastType != BT_IntArr ) {
		// Ошибка - пытаемся узнать длину не у целочисленного массива.
	}
	lastType = BT_Int;
}

void CTypeChecker::Visit( const CExpIdExpList& exp )
{
	exp.Exp()->Accept( *this );
	if( symbolsTable.Classes().find( lastType.UserDefinedName ) == symbolsTable.Classes().end() ) {
		// Ошибка - не существует вызывающего класса.
	}
	const CClassDescriptor* callingClass = &symbolsTable.Classes().at( lastType.UserDefinedName );
}

void CTypeChecker::Visit( const CClassDeclList& classDeclList )
{
	for( auto& classDecl : classDeclList.ClassDeclList() ) {
		classDecl->Accept( *this );
	}
}

void CTypeChecker::Visit( const CClassDecl& classDecl )
{
	if( classDecl.ParendId() != "" ) {
		if( symbolsTable.Classes().find( classDecl.ParendId() ) == symbolsTable.Classes().end() ) {
			// Ошибка родительского класса не существует.
		} else {
			std::set<std::string> inheritCircleNames;
			const CClassDescriptor* tmp = &symbolsTable.Classes().at( classDecl.ClassId() );
			while( tmp->BaseClass != "" ) {
				if( inheritCircleNames.find( tmp->Name() ) != inheritCircleNames.end() ) {
					// Ошибка - повтор в цепи наследования.
					break;
				} else if( symbolsTable.Classes().find( tmp->BaseClass ) != symbolsTable.Classes().end() ) {
					inheritCircleNames.insert( tmp->Name() );
					tmp = &symbolsTable.Classes().at( tmp->BaseClass );
				}
			}
		}
	}
	currentClass = &( symbolsTable.Classes().at( classDecl.ClassId() ) );
	classDecl.VarDeclList()->Accept( *this );
	classDecl.MethodDeclList()->Accept( *this );
	currentClass = 0;
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