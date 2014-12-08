// Автор: Фролов Николай.

#include <ErrorsAggregator.h>
#include <iostream>
#include <cassert>

using namespace SymbolsTable;

const std::string CRedefinitionError::baseRedefinitionMessage = "Error. Redefinition of ";

void CErrorsAggregator::WriteErrors() const
{
	for( auto& error : semanticErrors ) {
		std::cout << error->What() << std::endl;
	}
}