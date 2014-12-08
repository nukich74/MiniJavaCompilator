// Автор: Фролов Николай.

// Описание: Базовый класс для описаний.

#pragma once

#include <string>
namespace SymbolsTable {
	class CItemDescriptor {
	public:
		CItemDescriptor( const std::string& _name )
			: name( _name )
		{ }

		const std::string& Name() const { return name; }

	private:
		std::string name;
	};
}