// Автор: Николай Фролов

// Описание: Класс, аггрегирующий информацию о классе - его методах, полях, базовых классах.

#pragma once

#include "MethodDescription.h"
#include <string>
#include <vector>

namespace SymbolsTable {
	class CClassDescription {
	public:
		// Имя класса.
		std::string Name;
		// Информация о методах.
		std::vector<CMethodDescription> Methods;
		// Информация о полях.
		std::vector<CVariableDescription> Fields;
		// Базовый класс. - Если отсутствует, то пустая строка.
		std::string BaseClass;

		explicit CClassDescription( const std::string& _Name )
			: Name( _Name )
		{ }

		bool IsZero() const { return Name == ""; }

		void MakeZero() { Name = ""; Fields.clear(); Methods.clear(); BaseClass = ""; }
	};
}