// Автор: Николай Фролов

// Описание: Класс, аггрегирующий информацию о переменной - ее имени и типе.

#include <string>
#include "TypeIdentifier.h"

struct CFieldDescription {
public:
	// Имя переменной.
	std::string Name;
	// Тип переменной.
	CTypeIdentifier Type;

};