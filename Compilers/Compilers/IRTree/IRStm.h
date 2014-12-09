// Автор: Азат Давлетшин
// Описание: Реализации интерфейса IIRStm
#pragma once

#include <IRTree.h>
#include <IRHelpers.h>
#include <Temp.h>
#include <memory>

namespace IRTree
{

// Копируем результат вычисления выражения src в dst (dst - либо временная переменная CIRTemp, либо адрес CIRMem)
class CIRMove : public IIRStm {
public:
	CIRMove( const IIRExp* const _dst, const IIRExp* const _src ) :
		dst( _dst ),
		src( _src )
	{}

	std::shared_ptr<const IIRExp> dst;
	std::shared_ptr<const IIRExp> src;
};

// Вычисляем exp и забываем про результат
class CIRExp : public IIRStm {
public:
	CIRExp( const IIRExp* const _exp ) :
		exp( _exp )
	{}

	std::shared_ptr<const IIRExp> exp;
};

// Переходим в узел CIRLabel, которому соответствует метка
class CIRJump : public IIRStm {
public:
	CIRJump( const Temp::CLabel* const _label ) :
		label( _label )
	{}

	const Temp::CLabel* const label;
};

// Условный переход по меткам
class CIRCjump : public IIRStm {
public:
	CIRCjump( TCJump _relop, const IIRExp* const _left, const IIRExp* const _right, const Temp::CLabel* const _iftrue,
		const Temp::CLabel* const _iffalse ) :
		relop( _relop ),
		left( _left ),
		right( _right ),
		iftrue( _iftrue ),
		iffalse( _iffalse )
	{}

	const TCJump relop;
	std::shared_ptr<const IIRExp> left;
	std::shared_ptr<const IIRExp> right;
	const Temp::CLabel* const iftrue;
	const Temp::CLabel* const iffalse;
};

// Последовательно исполняет left, right
class CIRSeq : public IIRStm {
public:
	CIRSeq( const IIRStm* const _left, const IIRStm* const _right ) : left( _left ), right( _right ) {}

	CIRSeq(const IIRStm* const arg1, const IIRStm* const arg2, const IIRStm* const arg3 ) : left( arg1 ), right( new CIRSeq( arg2, arg3 ) ) {}

	CIRSeq(const IIRStm* const arg1, const IIRStm* const arg2, const IIRStm* const arg3, const IIRStm* const arg4 ) : 
		left( arg1 ), right( new CIRSeq( arg2, arg3, arg4 ) ) {}

	CIRSeq(const IIRStm* const arg1, const IIRStm* const arg2, const IIRStm* const arg3, const IIRStm* const arg4, const IIRStm* const arg5 ) : 
		left( arg1 ), right( new CIRSeq( arg2, arg3, arg4, arg5 ) ) {}

	CIRSeq(const IIRStm* const arg1, const IIRStm* const arg2, const IIRStm* const arg3, const IIRStm* const arg4, 
			const IIRStm* const arg5, const IIRStm* const arg6) : 
		left(arg1), right( new CIRSeq( arg2, arg3, arg4, arg5, arg6 ) ) {}

	std::shared_ptr<const IIRStm> left;
	std::shared_ptr<const IIRStm> right;
};

// В этот узел будет осуществляться переход по метке label
class CIRLabel : public IIRStm {
public:
	CIRLabel( const Temp::CLabel* const _label ) :
		label( _label )
	{}

	const Temp::CLabel* const label;
};

}