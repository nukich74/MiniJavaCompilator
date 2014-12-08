// Автор: Николай Фролов

#include "SymbolsTable.h"

namespace SymbolsTable {
	// Добавление нового класса в таблицу.
	void CSymbolsTable::AddClass( const CClassDescriptor& newClass ) 
	{ 
		if( classes.find( newClass.Name() ) == classes.end() ) {
			classes.insert( std::pair< std::string, CClassDescriptor>( newClass.Name(), newClass ) );
		}
	}
}