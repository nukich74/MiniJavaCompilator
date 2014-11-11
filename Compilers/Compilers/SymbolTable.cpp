// Автор: Николай Фролов

#include "SymbolTable.h"

void CSymbolTable::AddClass( const CClassDescription& newClass ) 
{ 
	if( Classes.find( newClass.Name ) != Classes.end() ) {
		Classes.insert( std::pair< std::string, CClassDescription>( newClass.Name, newClass ) );
	}
}