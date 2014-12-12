// Автор: Николай Фролов.

// Описание: Класс агрегирует возникшие при построении таблицы символов ошибки.

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <Location.h>
#include <TypeIdentifier.h>

namespace SymbolsTable {
	class CSemanticError {
	public:
		CSemanticError( const std::string& _errorMsg )
			: errorMsg( _errorMsg )
		{ }

		const std::string& What() const { return errorMsg; }

	protected:
		std::string errorMsg;

		static std::string locationString( const CLocation& location ) { return std::to_string( location.startLine ) + ":" + std::to_string( location.startColumn )	+ " - " + std::to_string( location.endLine ) + ":" + std::to_string( location.startColumn ); }
	};

	class CRedefinitionError : public CSemanticError {
	public:
		CRedefinitionError( const std::string& redefinedName, const CLocation& location )
			: CSemanticError( baseRedefinitionMessage )
		{
			errorMsg += redefinedName + " in positions " + locationString( location );
		}

	private:
		static const std::string baseRedefinitionMessage;
	};

	enum CItemType {
		IT_Variable,
		IT_Method,
		IT_Class
	};

	class CUndefinedItemError : public CSemanticError {
	public:
		CUndefinedItemError( const std::string& undefinedName, CItemType itemType, const CLocation& location )
			: CSemanticError( baseUndefinedItemMessage )
		{
			errorMsg += itemName( itemType ) + " " + undefinedName + " in positions " + locationString( location );
		}

	private:
		static const std::string baseUndefinedItemMessage;

		static std::string itemName( CItemType itemType );
	};

	class CIncorrectType : public CSemanticError {
	public:
		CIncorrectType( const SymbolsTable::CTypeIdentifier& takenType, const SymbolsTable::CTypeIdentifier& expectedType, const CLocation& location )
			: CSemanticError( baseIncorrectTypeMessage )
		{
			errorMsg += "in positions " + locationString( location ) + ". Expected " + expectedType.toString() + " instead of " + takenType.toString();
		}

	private:
		static const std::string baseIncorrectTypeMessage;
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