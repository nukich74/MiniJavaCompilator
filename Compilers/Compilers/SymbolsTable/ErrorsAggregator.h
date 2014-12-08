// Автор: Николай Фролов.

// Описание: Класс агрегирует возникшие при построении таблицы символов ошибки.

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <Location.h>

namespace SymbolsTable {
	class CSemanticError {
	public:
		CSemanticError( const std::string& _errorMsg )
			: errorMsg( _errorMsg )
		{ }

		const std::string& What() const { return errorMsg; }

	protected:
		std::string errorMsg;
	};

	class CRedefinitionError: public CSemanticError {
	public:
		CRedefinitionError( const std::string& redefinedName, const CLocation& location )
			: CSemanticError( baseRedefinitionMessage )
		{
			errorMsg += redefinedName + " in positions " + std::to_string( location.startLine ) + ":" + std::to_string( location.startColumn )
				+ " - " + std::to_string( location.endLine ) + ":" + std::to_string( location.startColumn );
		}

	private:
		static const std::string baseRedefinitionMessage;
	};

	class CErrorsAggregator {
	public:
		void AddError( const std::shared_ptr<CSemanticError> newError ) { semanticErrors.push_back( newError ); }

		bool HasErrors() const { return !semanticErrors.empty(); }

		void WriteErrors() const;
	private:
		std::vector< std::shared_ptr<CSemanticError> > semanticErrors;
	};
}