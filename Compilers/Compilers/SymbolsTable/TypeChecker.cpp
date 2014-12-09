// Автор: Фролов Николай.

#include <TypeChecker.h>
#include <common.h>
#include <set>
#include <cassert>

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
		if( !setLastVarTypeByIdentifier( assignStatement.LeftId() ) ) {
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
		if( !setLastVarTypeByIdentifier( assignStatement.LeftId() ) ) {
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


// TODO!
void CTypeChecker::Visit( const CExpIdExpList& exp )
{
	exp.Exp()->Accept( *this );
	if( symbolsTable.Classes().find( lastType.UserDefinedName ) == symbolsTable.Classes().end() ) {
		// Ошибка - не существует вызывающего класса.
	}
	const CClassDescriptor* callingClass = &symbolsTable.Classes().at( lastType.UserDefinedName );
}

void CTypeChecker::Visit( const CIntegerLiteral& exp )
{
	lastType = BT_Int;
}

void CTypeChecker::Visit( const CTrue& exp )
{
	lastType = BT_Bool;
}

void CTypeChecker::Visit( const CFalse& exp )
{
	lastType = BT_Bool;
};

void CTypeChecker::Visit( const CId& exp )
{
	if( !setLastVarTypeByIdentifier( exp.Id() ) ) {
		// Ошибка - нет такой переменной.
	}
}

void CTypeChecker::Visit( const CNewIntExpIndex& exp )
{
	exp.Exp()->Accept( *this );
	if( lastType != BT_Int ) {
		// Ошибка - индекс не целочисленный
	}
	lastType = BT_IntArr;
}

void CTypeChecker::Visit( const CNewId& exp )
{
	if( symbolsTable.Classes().find( exp.TypeId() ) == symbolsTable.Classes().end() ) {
		// Ошибка - нет создаваемого класса.
	}
	lastType = exp.TypeId();
}

void CTypeChecker::Visit( const CThis& exp )
{
	lastType = currentClass->Name();
}

void CTypeChecker::Visit( const CNotExp& exp )
{
	exp.Exp()->Accept( *this );
	if( lastType != BT_Bool ) {
		// Ошибка - отрицание не к булевому значению.
	}
	lastType = BT_Bool;
}

void CTypeChecker::Visit( const CExpInBrackets& exp )
{
	exp.Exp()->Accept( *this );
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
	if( classDecl.VarDeclList() != 0 ) {
		classDecl.VarDeclList()->Accept( *this );
	}
	if( classDecl.MethodDeclList() != 0 ) {
		classDecl.MethodDeclList()->Accept( *this );
	}
	currentClass = 0;
}

void CTypeChecker::Visit( const CMethodDeclList& methodDeclList )
{
	for( auto& methodDecl : methodDeclList.MethodDeclList() ) {
		methodDecl->Accept( *this );
	}
}

void CTypeChecker::Visit( const CMethodDecl& methodDecl )
{
	for( auto& method : currentClass->Methods ) {
		if( methodDecl.MethodName() == method.Name() ) {
			currentMethod = &method;
			break;
		}
	}
	if( methodDecl.FormalList() != 0 ) {
		methodDecl.FormalList()->Accept( *this );
	}
	if( methodDecl.VarDeclList() != 0 ) {
		methodDecl.VarDeclList()->Accept( *this );
	}
	if( methodDecl.StatementList() != 0 ) {
		methodDecl.StatementList()->Accept( *this );
	}
	methodDecl.ReturnedExp()->Accept( *this );
	CTypeIdentifier retType = lastType;
	methodDecl.ReturnedType()->Accept( *this );
	if( lastType != retType ) {
		// Ошибка - возвращаемое значение имеет не тот тип.
	}
}

void CTypeChecker::Visit( const CType& type )
{
	lastType = type.TypeName();
	if( lastType == BT_UserDefined 
		&& symbolsTable.Classes().find( lastType.UserDefinedName ) == symbolsTable.Classes().end() )
	{
		// Ошибка - тип не определен.
	}
}

void CTypeChecker::Visit( const CVarDeclList& varDeclList )
{
	for( auto& varDecl : varDeclList.VarDeclList() ) {
		varDecl->Accept( *this );
	}
}

void CTypeChecker::Visit( const CVarDecl& varDecl )
{

}

void CTypeChecker::Visit( const CFormalList& formalList )
{

}

bool CTypeChecker::setLastVarTypeByIdentifier( const std::string& id ) const
{
	if( currentMethod != 0 ) {
		for( auto& local : currentMethod->Locals ) {
			if( local.Name() == id ) {
				lastType = local.Type;
				return true;
			}
		}

		for( auto& param : currentMethod->Params ) {
			if( param.Name() == id ) {
				lastType = param.Type;
				return true;
			}
		}
	}

	for( auto& field : currentClass->Fields ) {
		if( field.Name() == id ) {
			lastType = field.Type;
			return true;
		}
	}

	if( !isClassCycled( currentClass->Name() ) ) {
		CClassDescriptor curClass = *currentClass;
		while( curClass.BaseClass != "" ) {
			if( haveClassInTable( curClass.BaseClass ) ) {
				curClass = symbolsTable.Classes().at( curClass.BaseClass );
				for( auto& field : curClass.Fields ) {
					if( field.Name() == id ) {
						lastType = field.Type;
						return true;
					}
				}
			} else {
				return false;
			}
		}
	}
	return false;
}

bool CTypeChecker::inCycled( const std::string& name ) const
{
	return classesWithCycleExtends.find( name ) != classesWithCycleExtends.end();
}

bool CTypeChecker::inNotCycled( const std::string& name ) const
{
	return classesWithCycleExtends.find( name ) != classesWithCycleExtends.end();
}

bool CTypeChecker::haveClassInTable( const std::string& name ) const
{
	return symbolsTable.Classes().find( name ) != symbolsTable.Classes().end();
}

bool CTypeChecker::isClassCycled( const std::string& className ) const
{
	if( inCycled( className ) ) {
		return true;
	}
	if( inNotCycled( className ) ) {
		return false;
	}
	if( haveClassInTable( className ) ) {
		CClassDescriptor currentClass = symbolsTable.Classes().at( className );
		std::set<std::string> visitedClasses;
		visitedClasses.insert( className );
		while( currentClass.BaseClass != "" ) {
			if( haveClassInTable( currentClass.BaseClass ) ) {
				currentClass = symbolsTable.Classes().at( currentClass.BaseClass );
				if( inCycled( currentClass.Name() ) || visitedClasses.find( currentClass.Name() ) != visitedClasses.end() ) {
					classesWithCycleExtends.insert( visitedClasses.begin(), visitedClasses.end() );
					return true;
				}
				if( inNotCycled( currentClass.Name() ) ) {
					classesWithoutCycleExtends.insert( visitedClasses.begin(), visitedClasses.end() );
					return false;
				}
			} else {
				classesWithoutCycleExtends.insert( visitedClasses.begin(), visitedClasses.end() );
				return false;
			}
		}
		classesWithoutCycleExtends.insert( visitedClasses.begin(), visitedClasses.end() );
		return false;
	} else {
		// Не должны применять функцию к классам, которые не определены вообще.
		assert( false );
		return false;
	}
}