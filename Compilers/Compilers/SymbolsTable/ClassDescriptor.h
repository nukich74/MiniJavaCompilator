// Автор: Николай Фролов

// Описание: Класс, аггрегирующий информацию о классе - его методах, полях, базовых классах.

#pragma once

#include <MethodDescriptor.h>
#include <ItemDescriptor.h>
#include <string>
#include <vector>

namespace SymbolsTable {
	class CClassDescriptor: public CItemDescriptor  {
	public:
		explicit CClassDescriptor( const std::string& name )
			: CItemDescriptor( name )
		{ }

		// Информация о методах.
		std::vector<CMethodDescriptor> Methods;
		// Информация о полях.
		std::vector<CVariableDescriptor> Fields;
		// Базовый класс. - Если отсутствует, то пустая строка.
		std::string BaseClass;
	};
}