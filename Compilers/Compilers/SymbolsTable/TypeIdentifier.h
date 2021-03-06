﻿// Автор: Николай Фролов.

// Описание: Структура, отвечающая за организацию хранения типа данных.

#pragma once

#include <string>

namespace SymbolsTable {

	// Стандартные типы.
	enum BaseTypes {
		BT_Int,
		BT_Bool,
		BT_IntArr,
		BT_UserDefined
	};

	struct CTypeIdentifier {
	public:
		// Данное значение определяет является ли тип стандартным.
		BaseTypes Base;
		// Если тип не стандартный, то здесь имя класса.
		std::string UserDefinedName;

		CTypeIdentifier() { }

		CTypeIdentifier( const std::string& typeName );

		CTypeIdentifier( BaseTypes type )
			: Base( type )
		{ }

		std::string ToString() const;

		bool operator == ( const CTypeIdentifier& rhs ) const;

		bool operator != ( const CTypeIdentifier& rhs ) const;

		bool operator == ( const BaseTypes& rhs ) const;

		bool operator != ( const BaseTypes& rhs ) const;
	};
}