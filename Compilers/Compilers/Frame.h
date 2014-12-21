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

	// FP нужен для того чтобы получать смещение для локальных переменных внутри функции
	const Temp::CTemp* FramePointer() const {
		return framePointer.get();
	}

	// this нужен чтобы получать смещения на поля объекта класса
	const Temp::CTemp* ThisPointer() const {
		return thisPointer.get();
	}

	// Машинно зависимая информация
	static int WordSize() { return 4; }
			
	// Доступ к формальным параметрам
	std::shared_ptr<const IAccess> GetFormal( std::string name ) const;
	void AddFormal( const std::string _name, const IAccess* _var );

	// Доступ к локальным переменным
	std::shared_ptr<const IAccess> GetLocal( std::string name ) const;
	void AddLocal( const std::string _name, const IAccess* _var );

	// Доступ к переменной (не известно какой local, formal или какой то другой)
	std::shared_ptr<const IAccess> GetAccess( std::string _name ) const;

	// Корень IRTree для текущей функции
	std::shared_ptr<const IRTree::IExp> Exp;
	// Задекорированное имя функции
	//	Имя_класса::имя_функции
	const std::string Name;

private:

	std::map<const std::string, std::shared_ptr<const IAccess> > formals;
	std::map<const std::string, std::shared_ptr<const IAccess> > locals;

	std::shared_ptr<const Temp::CTemp> framePointer;
	std::shared_ptr<const Temp::CTemp> thisPointer;
};

} // namespace Frame