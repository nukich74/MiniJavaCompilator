// Автор: Николай Фролов

// Описание: Класс, аггрегирующий информацию о методах класса - его имени,
// возвращаемом значении, типах аргументов, локальных переменных.

#pragma once

#include <ItemDescriptor.h>
#include "VariableDescriptor.h"
#include <string>
#include <vector>

namespace SymbolsTable {
	class CMethodDescriptor : public CItemDescriptor {
	public:
		CMethodDescriptor( const std::string& name )
			: CItemDescriptor( name )
		{ }

		// Возвращаемое значение.
		CTypeIdentifier ReturnType;
		// Входные параметры метода.
		std::vector<CVariableDescriptor> Params;
		// Локальные переменные метода.
		std::vector<CVariableDescriptor> Locals;
	};
}