// Автор: Николай Фролов

#include "SymbolTable.h"

namespace SymbolsTable {
	// Добавление нового класса в таблицу.
	void CSymbolTable::AddClass( const CClassDescription& newClass ) 
	{ 
		if( Classes.find( newClass.Name ) != Classes.end() ) {
			Classes.insert( std::pair< std::string, CClassDescription>( newClass.Name, newClass ) );
		}
	}
}