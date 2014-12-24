// Автор: Фролов Николай.

#include <TypeChecker.h>
#include <common.h>
#include <set>
#include <cassert>

using namespace SymbolsTable;

void CTypeChecker::Visit( const CProgram& program )
{
	program.MainClass()->Accept( *this );
	if( program.ClassDeclList() != 0 ) {
		program.ClassDeclList()->Accept( *this );
	}
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
			std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( assignStatement.LeftId(), IT_Variable, assignStatement.Location() ) );
			errors.AddError( undefIdentifierError );
			return;
		}
		CTypeIdentifier leftType = lastType;
		assignStatement.RightExp()->Accept( *this );
		CTypeIdentifier rightType = lastType;
		if( leftType != rightType ) {
			std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( rightType, leftType, assignStatement.Location() ) );
			errors.AddError( incorrectTypeError );
			return;
		}
	} else {
		assignStatement.IndexExp()->Accept( *this );
		if( lastType != BT_Int ) {
			std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Int, assignStatement.Location() ) );
			errors.AddError( incorrectTypeError );
			return;
		}
		if( !setLastVarTypeByIdentifier( assignStatement.LeftId() ) ) {
			std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( assignStatement.LeftId(), IT_Variable, assignStatement.Location() ) );
			return;
		}
		CTypeIdentifier leftType = lastType;
		if( leftType != BT_IntArr ) {
			std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_IntArr, assignStatement.Location() ) );
			return;
		}
		assignStatement.RightExp()->Accept( *this );
		if( lastType != BT_Int ) {
			std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Int, assignStatement.Location() ) );
		}
	}
}

void CTypeChecker::Visit( const CPrintStatement& printStatement )
{
	printStatement.Exp()->Accept( *this );
	if( lastType != BT_Int ) {
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Int, printStatement.Location() ) );
		errors.AddError( incorrectTypeError );
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
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Bool, ifStatement.Location() ) );
		errors.AddError( incorrectTypeError );
	}
	ifStatement.IfStatement()->Accept( *this );
	ifStatement.ElseStatement()->Accept( *this );
}

void CTypeChecker::Visit( const CWhileStatement& whileStatement )
{
	whileStatement.Exp()->Accept( *this );
	if( lastType != BT_Bool ) {
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Bool, whileStatement.Location() ) );
		errors.AddError( incorrectTypeError );
	}
	whileStatement.Statement()->Accept( *this );
}

void CTypeChecker::Visit( const CExpList& expList )
{
	auto currentArgs = expectedArgs;
	assert( currentArgs != 0 );
	if( currentArgs->size() != expList.ExpList().size() ) {
		std::shared_ptr<CIncorrectArguments> argumentsError( std::make_shared<CIncorrectArguments>( *handlingMethodName, expList.Location() ) );
		errors.AddError( argumentsError );
		return;
	}
	for( size_t i = 0; i < expList.ExpList().size(); ++i ) {
		expList.ExpList()[i]->Accept( *this );
		if( ( *currentArgs )[i].Type != lastType ) {
			std::shared_ptr<CIncorrectArguments> argumentsError( std::make_shared<CIncorrectArguments>( *handlingMethodName, expList.Location() ) );
			errors.AddError( argumentsError );
		}
	}
}

void CTypeChecker::Visit( const CExpBinOpExp& exp )
{
	if( exp.Operation() == '&' ) {
		exp.LeftArg()->Accept( *this );
		if( lastType != BT_Bool ) {
			std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Bool, exp.Location() ) );
			errors.AddError( incorrectTypeError );
			SetLastTypeCausedByError();
			return;
		}
		exp.RightArg()->Accept( *this );
		if( lastType != BT_Bool ) {
			std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Bool, exp.Location() ) );
			errors.AddError( incorrectTypeError );
			SetLastTypeCausedByError();
			return;
		}
		lastType = BT_Bool;
	} else {
		exp.LeftArg()->Accept( *this );
		if( lastType != BT_Int ) {
			std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Int, exp.Location() ) );
			errors.AddError( incorrectTypeError );
			SetLastTypeCausedByError();
			return;
		}
		exp.RightArg()->Accept( *this );
		if( lastType != BT_Int ) {
			std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Int, exp.Location() ) );
			errors.AddError( incorrectTypeError );
			SetLastTypeCausedByError();
			return;
		}
		if( exp.Operation() != '<' ) {
			lastType = BT_Int;
		} else {
			lastType = BT_Bool;
		}
	}
}

void CTypeChecker::Visit( const CUnMinExp& exp )
{
	exp.Accept( *this );
	if( lastType != BT_Int ) {
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Int, exp.Location() ) );
		errors.AddError( incorrectTypeError );
		SetLastTypeCausedByError();
		return;
	}
	lastType = BT_Int;
}

void CTypeChecker::Visit( const CExpWithIndex& exp )
{
	exp.Exp()->Accept( *this );
	if( lastType != BT_IntArr ) {
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_IntArr, exp.Location() ) );
		errors.AddError( incorrectTypeError );
		SetLastTypeCausedByError();
		return;
	}
	exp.Index()->Accept( *this );
	if( lastType != BT_Int ) {
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Int, exp.Location() ) );
		errors.AddError( incorrectTypeError );
		SetLastTypeCausedByError();
		return;
	}
	lastType = BT_Int;
}

void CTypeChecker::Visit( const CExpDotLength& exp )
{
	exp.Exp()->Accept( *this );
	if( lastType != BT_IntArr ) {
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_IntArr, exp.Location() ) );
		errors.AddError( incorrectTypeError );
		SetLastTypeCausedByError();
		return;
	}
	lastType = BT_Int;
}

void CTypeChecker::Visit( const CExpIdExpList& exp )
{
	exp.Exp()->Accept( *this );

	if( lastType.Base != BT_UserDefined ) {
		std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( exp.Id(), IT_Method, exp.Location() ) );
		errors.AddError( undefIdentifierError );
		SetLastTypeCausedByError();
		return;
	}

	const CMethodDescriptor* calledMethod = getMethodFromClassById( &symbolsTable.Classes().at( lastType.UserDefinedName ), exp.Id() );
	if( calledMethod == 0 ) {
		std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( exp.Id(), IT_Method, exp.Location() ) );
		errors.AddError( undefIdentifierError );
		SetLastTypeCausedByError();
		return;
	} else {
		expectedArgs = &calledMethod->Params;
		handlingMethodName = &exp.Id();
		exp.ExpList()->Accept( *this );
		handlingMethodName = 0;
		expectedArgs = 0;
		lastType = calledMethod->ReturnType;
	}
}

void CTypeChecker::Visit( const CExpIdVoidExpList& exp )
{
	exp.Exp()->Accept( *this );

	if( lastType.Base != BT_UserDefined ) {
		std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( exp.Id(), IT_Method, exp.Location() ) );
		errors.AddError( undefIdentifierError );
		SetLastTypeCausedByError();
		return;
	}

	const CMethodDescriptor* calledMethod = getMethodFromClassById( &symbolsTable.Classes().at( lastType.UserDefinedName ), exp.Id() );
	if( calledMethod == 0 ) {
		std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( exp.Id(), IT_Method, exp.Location() ) );
		errors.AddError( undefIdentifierError );
		SetLastTypeCausedByError();
		return;
	} else {
		expectedArgs = &calledMethod->Params;
		if( !expectedArgs->empty() ) {
			std::shared_ptr<CIncorrectArguments> argumentsError( std::make_shared<CIncorrectArguments>( exp.Id(), exp.Location() ) );
			errors.AddError( argumentsError );
			SetLastTypeCausedByError();
			return;
		}
		expectedArgs = 0;
		lastType = calledMethod->ReturnType;
	}
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
		std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( exp.Id(), IT_Variable, exp.Location() ) );
		errors.AddError( undefIdentifierError );
		SetLastTypeCausedByError();
		return;
	}
}

void CTypeChecker::Visit( const CNewIntExpIndex& exp )
{
	exp.Exp()->Accept( *this );
	if( lastType != BT_Int ) {
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Int, exp.Location() ) );
		errors.AddError( incorrectTypeError );
		SetLastTypeCausedByError();
		return;
	}
	lastType = BT_IntArr;
}

void CTypeChecker::Visit( const CNewId& exp )
{
	if( symbolsTable.Classes().find( exp.TypeId() ) == symbolsTable.Classes().end() ) {
		std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( exp.TypeId(), IT_Class, exp.Location() ) );
		errors.AddError( undefIdentifierError );
		SetLastTypeCausedByError();
		return;
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
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, BT_Bool, exp.Location() ) );
		errors.AddError( incorrectTypeError );
		SetLastTypeCausedByError();
		return;
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
			std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( classDecl.ParendId(), IT_Class, classDecl.Location() ) );
			errors.AddError( undefIdentifierError );
		} else {
			std::set<std::string> inheritCycleNames;
			const CClassDescriptor* tmp = &symbolsTable.Classes().at( classDecl.ClassId() );
			while( tmp->BaseClass != "" ) {
				if( inheritCycleNames.find( tmp->Name() ) != inheritCycleNames.end() ) {
					std::shared_ptr<CCycledClasses> cycleInheritionError( std::make_shared<CCycledClasses>( classDecl.ClassId(), classDecl.Location() ) );
					errors.AddError( cycleInheritionError );
					classesWithCycleExtends.insert( inheritCycleNames.begin(), inheritCycleNames.end() );
					break;
				} else if( symbolsTable.Classes().find( tmp->BaseClass ) != symbolsTable.Classes().end() ) {
					inheritCycleNames.insert( tmp->Name() );
					tmp = &symbolsTable.Classes().at( tmp->BaseClass );
				} else {
					classesWithoutCycleExtends.insert( inheritCycleNames.begin(), inheritCycleNames.end() );
					break;
				}
			}
			if( tmp->BaseClass == "" ) {
				classesWithoutCycleExtends.insert( inheritCycleNames.begin(), inheritCycleNames.end() );
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
		std::shared_ptr<CIncorrectType> incorrectTypeError( std::make_shared<CIncorrectType>( lastType, retType, methodDecl.Location() ) );
		errors.AddError( incorrectTypeError );
	}
	currentMethod = 0;
}

void CTypeChecker::Visit( const CType& type )
{
	CTypeIdentifier tmp = type.TypeName();
	if( tmp == BT_UserDefined 
		&& symbolsTable.Classes().find( tmp.UserDefinedName ) == symbolsTable.Classes().end() )
	{
		std::shared_ptr<CUndefinedItemError> undefIdentifierError( std::make_shared<CUndefinedItemError>( type.TypeName(), IT_Class, type.Location() ) );
		errors.AddError( undefIdentifierError );
		SetLastTypeCausedByError();
		return;
	}
	lastType = tmp;
}

void CTypeChecker::Visit( const CVarDeclList& varDeclList )
{
	for( auto& varDecl : varDeclList.VarDeclList() ) {
		varDecl->Accept( *this );
	}
}

void CTypeChecker::Visit( const CVarDecl& varDecl )
{
	varDecl.VarType()->Accept( *this );
}

void CTypeChecker::Visit( const CFormalList& formalList )
{
	for( auto& arg : formalList.FormalList() ) {
		arg.first->Accept( *this );
	}
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

const CMethodDescriptor* CTypeChecker::getMethodFromClassById( const CClassDescriptor* inClass, const std::string& id ) const
{
	for( auto& method : inClass->Methods ) {
		if( method.Name() == id ) {
			return &method;
		}
	}
	if( inClass->BaseClass != "" && !isClassCycled( inClass->Name() ) ) {
		while( inClass->BaseClass != "" ) {
			if( haveClassInTable( inClass->BaseClass ) ) {
				inClass = &symbolsTable.Classes().at( inClass->BaseClass );
				for( auto& method : inClass->Methods ) {
					if( method.Name() == id ) {
						return &method;
					}
				}
			} else {
				return 0;
			}
		}
	}
	return 0;
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