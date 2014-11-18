// Автор: Николай Фролов

// Описание: Класс, аггрегирующий информацию о переменной - ее имени и типе.

#pragma once

#include <string>
#include "TypeIdentifier.h"

namespace SymbolsTable {
	struct CVariableDescription {
	public:
		CVariableDescription() { }

		// Имя переменной.
		std::string Name;
		// Тип переменной.
		CTypeIdentifier Type;

		void MakeZero() { Name = ""; }

		bool IsZero() const { return Name == ""; }
	};
}