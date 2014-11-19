// Автор: Фролов Николай.

// Описание: набор вспомогательных функий для построения таблицы символов.

#pragma once

#include <vector>

namespace SymbolsTable {
	// Проверяет есть ли в области видимости, описанной массивом данное имя.
	template <class T>
	bool HasSuchNameInScope( std::vector<T> descriptors, std::string name )
	{
		for( auto ptr = descriptors.begin() ; ptr != descriptors.end(); ++ptr ) {
			if( ptr->Name == name ) {
				return true;
			}
		}
		return false;
	}
}