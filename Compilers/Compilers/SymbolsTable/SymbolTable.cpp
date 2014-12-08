// Автор: Николай Фролов

#include "SymbolTable.h"

namespace SymbolsTable {
	// Добавление нового класса в таблицу.
	void CSymbolTable::AddClass( const CClassDescriptor& newClass ) 
	{ 
		if( classes.find( newClass.Name() ) == classes.end() ) {
			classes.insert( std::pair< std::string, CClassDescriptor>( newClass.Name(), newClass ) );
		}
	}
}