// Автор: Фролов Николай.

#include <ErrorsAggregator.h>
#include <iostream>
#include <cassert>

using namespace SymbolsTable;

void CErrorsAggregator::AddError( ErrorType type, ErrorPosition position )
{
	std::string msg;
	switch( type ) {
		case ET_Redefinition:
			msg += "Redefinition of ";
			break;
		default:
			assert( false );
	}
	errors.push_back( msg );
}

void CErrorsAggregator::WriteErrors() const
{
	for( int i = 0; i < static_cast<int>( errors.size() ); ++i ) {
		std::cout << errors[i] << std::endl;
	}
}