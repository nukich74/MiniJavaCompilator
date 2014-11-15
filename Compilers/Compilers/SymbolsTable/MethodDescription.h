// Автор: Николай Фролов

// Описание: Класс, аггрегирующий информацию о методах класса - его имени,
// возвращаемом значении, типах аргументов, локальных переменных.

#pragma once

#include "VariableDescription.h"
#include <string>
#include <vector>

namespace SymbolsTable {
	class CMethodDescription {
	public:

		// Имя метода.
		std::string Name;
		// Возвращаемое значение.
		CTypeIdentifier ReturnType;
		// Входные параметры метода.
		std::vector<CVariableDescription> Params;
		// Локальные переменные метода.
		std::vector<CVariableDescription> Locals;

		CMethodDescription( const std::string& _Name, const CTypeIdentifier& _ReturnType )
			: Name( _Name )
			, ReturnType( _ReturnType )
		{ }

		// Превратить в невалидный объект.
		void MakeZero() { Name = ""; Params.clear(); Locals.clear(); }

		bool IsZero() const { return Name == ""; }
	};
}