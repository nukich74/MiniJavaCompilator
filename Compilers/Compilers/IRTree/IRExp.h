// Автор: Азат Давлетшин
// Описание: Реализации интерфейса IIRExp
#pragma once

#include <IRTree.h>
#include <Temp.h>
#include <IRHelpers.h>
#include <memory>

namespace IRTree {

// Константное выражение
class CConst : public IExp {
public:
	CConst( int _value ) :
		value( _value )
	{}

	virtual void Accept( IVisitor& printer ) const
	{
		printer.Visit( this );
	}

	const int value;
};

// Метка для переходов
class CName : public IExp {
public:
	CName( const Temp::CLabel* _label ) :
		label( _label )
	{}

	virtual void Accept( IVisitor& printer ) const
	{
		printer.Visit( this );
	}

	const Temp::CLabel* label;
};

// Временная переменная
class CTemp : public IExp {
public:
	CTemp( const Temp::CTemp& _temp ) :
		temp( _temp )
	{}

	virtual void Accept( IVisitor& printer ) const
	{
		printer.Visit( this );
	}

	const Temp::CTemp temp;
};

// Бинарный оператор
class CBinop : public IExp {
public:
	CBinop( TBinop _binop, const IExp* const _left, const IExp* const _right ) :
		binop( _binop ),
		left( _left ),
		right( _right )
	{}

	virtual void Accept( IVisitor& printer ) const
	{
		printer.Visit( this );
	}
	
	const TBinop binop;
	std::shared_ptr<const IExp> left; 
	std::shared_ptr<const IExp> right;
};

// Читаем значение из памяти, лежащее по адресу, который возвращает exp
class CMem : public IExp {
public:
	CMem( const IExp* const _exp ) :
		exp( _exp )
	{}

	virtual void Accept( IVisitor& printer ) const override
	{
		// АЗАТ че за дела? Чего ты метод не дописал?
		printer.Visit( this );
	}

	std::shared_ptr<const IExp> exp;
};

// Вызов функции по адресу func с аргументами args
class CCall : public IExp {
public:
	CCall( const IExp* const _func, const CExpList& _args ) :
		func( _func ),
		args( _args )
	{}

	virtual void Accept( IVisitor& printer ) const
	{
		printer.Visit( this );
	}

	std::shared_ptr<const IExp> func;
	const CExpList args;
};

// Выполняет stm, затем вычисляет и возвращает exp
class CEseq : public IExp {
public:
	CEseq( const IStm* const _stm, const IExp* const _exp ) :
		stm( _stm ),
		exp( _exp )
	{}

	virtual void Accept( IVisitor& printer ) const
	{
		printer.Visit( this );
	}

	std::shared_ptr<const IStm> stm;
	std::shared_ptr<const IExp> exp;
};


} // namespace IRTree
