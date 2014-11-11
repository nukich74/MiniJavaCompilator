// Автор: Николай Фролов

// Описание: Класс, аггрегирующий информацию о методах класса - его имени,
// возвращаемом значении, типах аргументов, локальных переменных.

#pragma once

#include "FieldDescription.h"
#include <string>
#include <vector>

class CMethodDescription {
public:
	// Имя метода.
	std::string Name;
	// Возвращаемое значение.
	CTypeIdentifier ReturnType;
	// Входные параметры метода.
	std::vector<CFieldDescription> Params;
	// Локальные переменные метода.
	std::vector<CFieldDescription> Locals;

	CMethodDescription( const std::string& _Name, const CTypeIdentifier& _ReturnType )
		: Name( _Name )
		, ReturnType( _ReturnType )
	{ }
};