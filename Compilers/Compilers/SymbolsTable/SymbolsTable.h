// Автор: Николай Фролов

// Описание: Класс представляет собой реализацию таблицы символов.

#pragma once

#include "ClassDescriptor.h"
#include <map>
#include <string>

namespace SymbolsTable {
	struct CSymbolsTable {
	public:
		const std::map< std::string, CClassDescriptor >& Classes() const { return classes; }

		// Добавление нового класса в таблицу.
		void AddClass( const CClassDescriptor& newClass );

	private:
		// Все определенные в программе классы.
		std::map< std::string, CClassDescriptor > classes;
	};
}