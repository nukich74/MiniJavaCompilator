// Автор: Азат Давлетшин
// Описание: Реализации интерфейса IIRExp
#pragma once

#include <IRTree.h>
#include <Temp.h>
#include <IRHelpers.h>
#include <memory>

namespace IRTree
{

// Константное выражение
class CIRConst : public IIRExp {
public:
	CIRConst( int _value ) :
		value( _value )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	const int value;
};

// Метка для переходов
class CIRName : public IIRExp {
public:
	CIRName( const Temp::CLabel& _label ) :
		label( _label )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	const Temp::CLabel label;
};

// Временная переменная
class CIRTemp : public IIRExp {
public:
	CIRTemp( const Temp::CTemp& _temp ) :
		temp( _temp )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	const Temp::CTemp temp;
};

// Бинарный оператор
class CIRBinop : public IIRExp {
public:
	CIRBinop( TBinop _binop, const IIRExp* const _left, const IIRExp* const _right ) :
		binop( _binop ),
		left( _left ),
		right( _right )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}
	
	const TBinop binop;
	const std::shared_ptr<const IIRExp> left; 
	const std::shared_ptr<const IIRExp> right;
};

// Читаем значение из памяти, лежащее по адресу, который возвращает exp
class CIRMem : public IIRExp {
public:
	CIRMem( const IIRExp* const _exp ) :
		exp( _exp )
	{}

	const std::shared_ptr<const IIRExp> exp;
};

// Вызов функции по адресу func с аргументами args
class CIRCall : public IIRExp {
public:
	CIRCall( const IIRExp* const _func, const CIRExpList& _args ) :
		func( _func ),
		args( _args )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	const std::shared_ptr<const IIRExp> func;
	const CIRExpList args;
};

// Выполняет stm, затем вычисляет и возвращает exp
class CIREseq : public IIRExp {
public:
	CIREseq( const IIRStm* const _stm, const IIRExp* const _exp ) :
		stm( _stm ),
		exp( _exp )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	const std::shared_ptr<const IIRStm> stm;
	const std::shared_ptr<const IIRExp> exp;
};


}
