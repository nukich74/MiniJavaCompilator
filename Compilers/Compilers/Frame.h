#pragma once

#include <MethodDescription.h>
#include <vector>

namespace Frame
{
// Переменная фрейма
class IAccess {
public:
	virtual ~IAccess() {}
};

// Класс-контейнер с платформо-зависимой информацией о функции
class CFrame {
public:
	CFrame( const SymbolsTable::CMethodDescription* _name ) :
		name( _name )
	{
		formals.resize( name->Params.size(), 0 );
		locals.resize( name->Locals.size(), 0 );
	}
			
	// Доступ к формальным параметрам
	int FormalsCount() const { return formals.size(); }
	const IAccess* Formal( size_t index ) const { return formals[index]; }

	// Доступ к локальным переменным
	int LocalsCount() const { return locals.size(); }
	const IAccess* Local( size_t index ) const { return locals[index]; }

private:
	const SymbolsTable::CMethodDescription* const name;
	std::vector<IAccess*> formals;
	std::vector<IAccess*> locals;
};
}