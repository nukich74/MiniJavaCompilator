// Автор: Николай Фролов.

// Описание: Класс агрегирует возникшие при построении таблицы символов ошибки.

#pragma once

#include <vector>
#include <string>
#include <cassert>

namespace SymbolsTable {
	enum ErrorType {
		ET_Redefinition
	};

	struct ErrorPosition {
	public:
		ErrorPosition( const std::string& _className, const std::string& _methodName = "", const std::string& _varName = "" )
		{ }
	private:
	};

	class CErrorsAggregator {
	public:
		std::vector<std::string> errors;

		void AddError( ErrorType type, ErrorPosition position );

		void WriteErrors() const;
	};
}