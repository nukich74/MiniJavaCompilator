// Автор: Фролов Николай.

#include <ErrorsAggregator.h>
#include <iostream>
#include <cassert>

using namespace SymbolsTable;

const std::string CRedefinitionError::baseRedefinitionMessage = "Redefinition of ";

const std::string CUndefinedItemError::baseUndefinedItemMessage = "Undefined name of ";

const std::string CIncorrectType::baseIncorrectTypeMessage = "Incorrect type of expression ";

const std::string CIncorrectArguments::baseIncorrectArgumentsMessage = "Incorrect arguments in call of method ";

const std::string CCycledClasses::baseCycledClassesMessage = "Cycled using of inheritance in class ";

std::string CSemanticError::itemName( CItemType itemType )
{
	switch( itemType ) {
		case IT_Variable:
			return "Variable";
		case IT_Method:
			return "Method";
		case IT_Class:
			return "Class";
		default:
			assert( false );
			return "AntiWarning";
	}
}

void CErrorsAggregator::WriteErrors() const
{
	for( auto& error : semanticErrors ) {
		std::cout << error->What() << std::endl;
	}
}