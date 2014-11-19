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
			: className( _className )
			, methodName( _methodName )
			, varName( _varName )
		{ }

		std::string GetPosition() const
		{
			if( className == "" ) {
				assert( false );
			} else {
				if( methodName != "" && varName != "" ) {
					return "class " + className + " method " + methodName + " variable defenition of " + varName;
				} else if( varName != "" ) {
					return "class " + className + " field definition of " + varName;
				} else if( methodName != "" ) {
					return "class " + className + " method definition of" + methodName;
				} else {
					return "class " + className;
				}
			}
		}

	private:
		std::string className;
		std::string methodName;
		std::string varName;
	};

	class CErrorsAggregator {
	public:
		std::vector<std::string> errors;

		void AddError( ErrorType type, ErrorPosition position );

		void WriteErrors() const;
	};
}