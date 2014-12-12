﻿// Автор: Азат Давлетшин
// Описание: Реализации интерфейса IIRStm
#pragma once

#include <IRTree.h>
#include <IRHelpers.h>
#include <Temp.h>
#include <IRPrint.h>
#include <memory>
#include <assert.h>

namespace IRTree {
// Копируем результат вычисления выражения src в dst (dst - либо временная переменная CIRTemp, либо адрес CIRMem)
class CMove : public IStm {
public:
	CMove( const IExp* const _dst, const IExp* const _src ) :
		dst( _dst ),
		src( _src )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	std::shared_ptr<const IExp> dst;
	std::shared_ptr<const IExp> src;
};

// Вычисляем exp и забываем про результат
class CExp : public IStm {
public:
	CExp( const IExp* const _exp ) :
		exp( _exp )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	std::shared_ptr<const IExp> exp;
};

// Переходим в узел CIRLabel, которому соответствует метка
class CJump : public IStm {
public:
	CJump( const Temp::CLabel* const _label ) :
		label( _label )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	const Temp::CLabel* const label;
};

// Условный переход по меткам
class CIRCjump : public IStm {
public:
	CIRCjump( TCJump _relop, const IExp* const _left, const IExp* const _right, const Temp::CLabel* const _iftrue,
		const Temp::CLabel* const _iffalse ) :
		relop( _relop ),
		left( _left ),
		right( _right ),
		iftrue( _iftrue ),
		iffalse( _iffalse )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	const TCJump relop;
	std::shared_ptr<const IExp> left;
	std::shared_ptr<const IExp> right;
	const Temp::CLabel* const iftrue;
	const Temp::CLabel* const iffalse;
};

// Последовательно исполняет left, right
class CSeq : public IStm {
public:
	CSeq( const IStm* const _left, const IStm* const _right ) : left( _left ), right( _right ) {}

	CSeq(const IStm* const arg1, const IStm* const arg2, const IStm* const arg3 ) : left( arg1 ), right( new CSeq( arg2, arg3 ) ) {}

	CSeq(const IStm* const arg1, const IStm* const arg2, const IStm* const arg3, const IStm* const arg4 ) : 
		left( arg1 ), right( new CSeq( arg2, arg3, arg4 ) ) {}

	CSeq(const IStm* const arg1, const IStm* const arg2, const IStm* const arg3, const IStm* const arg4, const IStm* const arg5 ) : 
		left( arg1 ), right( new CSeq( arg2, arg3, arg4, arg5 ) ) {}

	CSeq(const IStm* const arg1, const IStm* const arg2, const IStm* const arg3, const IStm* const arg4, 
			const IStm* const arg5, const IStm* const arg6) : 
		left(arg1), right( new CSeq( arg2, arg3, arg4, arg5, arg6 ) ) {}

	virtual void Print( CPrinter& printer ) const
	{
		printer.Print( this );
	}

	std::shared_ptr<const IStm> left;
	std::shared_ptr<const IStm> right;
};

// В этот узел будет осуществляться переход по метке label
class CLabel : public IStm {
public:
	CLabel( const Temp::CLabel* const _label ) :
		label( _label )
	{}

	virtual void Print( CPrinter& printer ) const
	{
		assert( false );
	}

	const Temp::CLabel* const label;
};

}