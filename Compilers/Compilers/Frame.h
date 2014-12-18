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

class CInFrame : public IAccess {
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
	CFrame( const std::string _name, const IRTree::IExp* _exp ) :
		Name( _name ), Exp( _exp ) {}

	// Зарезервированные регистры
	// FP нужен для того чтобы получать смещение для локальных переменных
	Temp::CTemp* FramePointer() const {
		return framePointer;
	}
	Temp::CTemp* ThisPointer() const {
		return thisPointer;
	}

	// Машинно зависимая информация
	static int WordSize() { return 4; }
			
	// Доступ к формальным параметрам
	const IAccess* GetFormal( std::string name ) const;
	void AddFormal( const std::string _name, const IAccess* _var );

	// Доступ к локальным переменным
	const IAccess* GetLocal(std::string name) const;
	void AddLocal( const std::string _name, const IAccess* _var );

	// Доступ к переменной (не известно какой local, formal или какой то другой)
	const IAccess* GetAccess( std::string _name ) const;

	// Корень IRTree для текущей функции
	const IRTree::IExp* Exp;
	// Задекорированное имя функции
	//	Имя_класса::имя_функции
	const std::string Name;

private:

	std::map<const std::string, const IAccess*> formals;
	std::map<const std::string, const IAccess*> locals;

	Temp::CTemp* framePointer;
	Temp::CTemp* thisPointer;
};

} // namespace Frame