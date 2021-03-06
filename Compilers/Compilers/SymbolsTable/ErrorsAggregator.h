// �����: ������� ������.

// ��������: ����� ���������� ��������� ��� ���������� ������� �������� ������.

#pragma once

#include <vector>
#include <string>
#include <memory>
#include <Location.h>
#include <TypeIdentifier.h>

namespace SymbolsTable {
	enum CItemType {
		IT_Variable,
		IT_Method,
		IT_Class
	};

	class CSemanticError {
	public:
		CSemanticError( const std::string& _errorMsg )
			: errorMsg( _errorMsg )
		{ }

		const std::string& What() const { return errorMsg; }

	protected:
		std::string errorMsg;

		static std::string itemName( CItemType itemType );
	};

	class CRedefinitionError : public CSemanticError {
	public:
		CRedefinitionError( const std::string& redefinedName, CItemType itemType,  const CLocation& location )
			: CSemanticError( baseRedefinitionMessage )
		{
			errorMsg += itemName( itemType ) + " " + redefinedName + " in positions " + location.ToString();
		}

	private:
		static const std::string baseRedefinitionMessage;
	};

	class CUndefinedItemError : public CSemanticError {
	public:
		CUndefinedItemError( const std::string& undefinedName, CItemType itemType, const CLocation& location )
			: CSemanticError( baseUndefinedItemMessage )
		{
			errorMsg += itemName( itemType ) + " " + undefinedName + " in positions " + location.ToString();
		}

	private:
		static const std::string baseUndefinedItemMessage;
	};

	class CIncorrectType : public CSemanticError {
	public:
		CIncorrectType( const SymbolsTable::CTypeIdentifier& takenType, const SymbolsTable::CTypeIdentifier& expectedType, const CLocation& location )
			: CSemanticError( baseIncorrectTypeMessage )
		{
			errorMsg += "in positions " + location.ToString() + ". Expected " + expectedType.ToString() + " instead of " + takenType.ToString();
		}

	private:
		static const std::string baseIncorrectTypeMessage;
	};

	class CIncorrectArguments : public CSemanticError {
	public:
		CIncorrectArguments( const std::string& functionName, const CLocation& location )
			: CSemanticError( baseIncorrectArgumentsMessage )
		{
			errorMsg += functionName + " in positions " + location.ToString();
		}
	private:
		static const std::string baseIncorrectArgumentsMessage;
	};

	class CCycledClasses : public CSemanticError {
	public:
		CCycledClasses( const std::string& className, const CLocation& location )
			: CSemanticError( baseCycledClassesMessage )
		{
			errorMsg += className + " in positions " + location.ToString();
		}
	private:
		static const std::string baseCycledClassesMessage;
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