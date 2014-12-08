// Автор: Николай Фролов

// Описание: Класс, аггрегирующий информацию о переменной - ее имени и типе.

#pragma once

#include <string>
#include <TypeIdentifier.h>
#include <ItemDescriptor.h>

namespace SymbolsTable {
	class CVariableDescriptor: public CItemDescriptor {
	public:
		CVariableDescriptor( const std::string& name )
			: CItemDescriptor( name )
		{ }

		// Тип переменной.
		CTypeIdentifier Type;
	};
}