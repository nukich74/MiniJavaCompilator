// Автор: Николай Фролов

// Описание: Класс представляет собой реализацию таблицы символов.

#include "ClassDescription.h"
#include <map>
#include <string>

struct CSymbolTable {
public:
	// Все определенные в программе классы.
	std::map< std::string, CClassDescription > Classes;

	// Добавление нового класса в таблицу.
	void AddClass( const CClassDescription& newClass );
};