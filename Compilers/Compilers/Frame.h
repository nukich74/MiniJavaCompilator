#pragma once

#include <vector>
#include "IRExp.h"

namespace Frame {

// Интерфейс для переменной фрейма
class IAccess {
public:
	virtual IRTree::IExp* ToExp( const Temp::CTemp* framePtr ) = 0;
	virtual ~IAccess() {}
};

class CInStack : public IAccess {
public:

	virtual IRTree::IExp* ToExp(const Temp::CTemp* framePtr) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

};

class CInRegister : public IAccess {
public:

	virtual IRTree::IExp* ToExp(const Temp::CTemp* framePtr) override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

};

// Класс-контейнер с платформо-зависимой информацией о функции
class CFrame {
public:
	CFrame( const std::string _name ) :
		name( _name ) {}

	// Зарезервированные регистры
	Temp::CTemp* FramePointer() const;
	Temp::CTemp* ThisPointer() const;

	// Машинно зависимая информация
	int WordSize() { return 4; }
			
	// Доступ к формальным параметрам
	const IAccess* GetFormal( std::string name ) const;

	// Доступ к локальным переменным
	const IAccess* GetLocal(std::string name) const;

private:
	const std::string name;

	std::map<std::string, IAccess*> formals;
	std::map<std::string, IAccess*> locals;
};

} // namespace Frame