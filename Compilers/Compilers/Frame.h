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

std::string to_string( TRegisters registerType );

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

	CInFrame( int _number ) : number( _number ) {}

	virtual const IRTree::IExp* ToExp( const Frame::CFrame* frame ) const override;

private:
	
	// Порядковый номер локальной переменной
	const int number;

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

class CFormalParameterInStack : public IAccess {
public:
	CFormalParameterInStack( int _number ) : number( _number ) {}

	virtual const IRTree::IExp* ToExp( const Frame::CFrame* frame ) const;

private:

	// Порядковый номер аргумента, переданного как формальный параметр функции
	// Считать начинаем с 1
	// 0 резервируется для this который мы договорились передавать через стек
	const int number;

};

// Класс-контейнер с платформо-зависимой информацией о функции
class CFrame {
public:
	CFrame( const std::string _name ) :
		Name( _name ), ThisCounter( 0 ), LocalCounter( 0 ), 
		thisPointer( new Temp::CTemp( _name + "_thisPointer" ) ),
		returnValue( new Temp::CTemp( _name + "_returnValue" ) ) 
	{
		for( int i = 0; i < R_Count; ++i ) {
			registers.emplace_back( std::shared_ptr<const Temp::CTemp>( new const Temp::CTemp( to_string( static_cast< TRegisters >( i ) ) ) ) );
		}
	}

	// Зарезервированные регистры

	const Temp::CTemp* GetRegister( TRegisters registerType ) const
	{
		assert( registerType >= R_EAX && registerType < R_Count );
		return registers.at( registerType ).get();
	}

	// FP нужен для того чтобы получать смещение для локальных переменных внутри функции
	const Temp::CTemp* FramePointer() const {
		return GetRegister( R_EBP );
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

	// Доступ к переменной (не известно какой local, formal или какой-то другой)
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

	std::shared_ptr<const Temp::CTemp> thisPointer;
	std::shared_ptr<const Temp::CTemp> returnValue;
	std::vector< std::shared_ptr<const Temp::CTemp> > registers;
};

} // namespace Frame