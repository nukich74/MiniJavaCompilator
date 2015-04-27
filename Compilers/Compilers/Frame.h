#pragma once

#include <vector>
#include "IRExp.h"
#include <map>

namespace Frame {

enum TRegisters {
	R_EAX,
	R_EBX,
	R_EDX,
	R_ECX,
	R_EBP,
	R_ESI,
	R_EDI,
	R_ESP,

	R_Count
};

class CFrame;

// Интерфейс для переменной фрейма
class IAccess {
public:
	virtual const IRTree::IExp* ToExp( const Frame::CFrame* frame ) const = 0;
	virtual ~IAccess() {}
};

// для локальных переменных, которые лежат со смещением у FramePointer
class CInFrame : public IAccess {
public:

	CInFrame( int _offsetInWords ) : offsetInWords( _offsetInWords ) {}

	virtual const IRTree::IExp* ToExp( const Frame::CFrame* frame ) const override;

private:

	const int offsetInWords;

};

// Для полей класса, которые лежат по this
class CInObject : public IAccess {
public:

	CInObject( int _offsetInWords ) : offsetInWords( _offsetInWords ) {}

	virtual const IRTree::IExp* ToExp( const Frame::CFrame* frame ) const override;

private:

	const int offsetInWords;

};

class CInRegister : public IAccess {
public:

	virtual const IRTree::IExp* ToExp( const Frame::CFrame* frame ) const override
	{
		throw std::logic_error("The method or operation is not implemented.");
	}

};

// Класс-контейнер с платформо-зависимой информацией о функции
class CFrame {
public:
	CFrame( const std::string _name ) :
		Name( _name ), ThisCounter( 0 ), LocalCounter( 0 ), 
		framePointer( new Temp::CTemp( _name + "_FP" ) ), 
		thisPointer( new Temp::CTemp( _name + "_thisPointer" ) ),
		returnValue( new Temp::CTemp( _name + "_returnValue" ) ) {}

	// Зарезервированные регистры

	const Temp::CTemp* GetRegister( TRegisters registerType ) const;

	// FP нужен для того чтобы получать смещение для локальных переменных внутри функции
	const Temp::CTemp* FramePointer() const {
		return framePointer.get();
	}

	// this нужен чтобы получать смещения на поля объекта класса
	const Temp::CTemp* ThisPointer() const {
		return thisPointer.get();
	}

	const Temp::CTemp* ReturnValue() const {
		return returnValue.get();
	}

	// Машинно зависимая информация
	static int WordSize() { return 4; }
			
	// Доступ к формальным параметрам
	const IAccess* GetFormal( std::string name ) const;
	void AddFormal( const std::string _name, const IAccess* _var );

	// Доступ к локальным переменным
	const IAccess* GetLocal( std::string name ) const;
	void AddLocal( const std::string _name, const IAccess* _var );

	// Доступ к полям класса
	const IAccess* GetField( std::string name ) const;
	void AddField( const std::string _name, const IAccess* _var );

	// Доступ к переменной (не известно какой local, formal или какой то другой)
	const IAccess* GetAccess( std::string _name ) const;

	// Корень IRTree для текущей функции
	const IRTree::IStm* Stm;
	// Задекорированное имя функции
	//	Имя_класса__имя_функции
	const std::string Name;

	int ThisCounter;
	int LocalCounter;

private:

	std::map<const std::string, const IAccess* > formals;
	std::map<const std::string, const IAccess* > locals;
	std::map<const std::string, const IAccess* > fields;

	std::shared_ptr<const Temp::CTemp> framePointer;
	std::shared_ptr<const Temp::CTemp> thisPointer;
	std::shared_ptr<const Temp::CTemp> returnValue;
};

} // namespace Frame