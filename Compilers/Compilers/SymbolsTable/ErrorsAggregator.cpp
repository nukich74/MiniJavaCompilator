// Автор: Фролов Николай.

#include <ErrorsAggregator.h>
#include <iostream>
#include <cassert>

using namespace SymbolsTable;

const std::string CRedefinitionError::baseRedefinitionMessage = "Redefinition of ";

const std::string CUndefinedItemError::baseUndefinedItemMessage = "Undefined name of ";

const std::string CIncorrectType::baseIncorrectTypeMessage = "Incorrect type of expression ";

std::string CUndefinedItemError::itemName( CItemType itemType )
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
	}
}

void CErrorsAggregator::WriteErrors() const
{
	for( auto& error : semanticErrors ) {
		std::cout << error->What() << std::endl;
	}
}