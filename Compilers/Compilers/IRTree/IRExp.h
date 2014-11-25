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

	const int value;
};

// Метка для переходов
class CIRName : public IIRExp {
public:
	CIRName( const Temp::CLabel& _label ) :
		label( _label )
	{}

	const Temp::CLabel label;
};

// Временная переменная
class CIRTemp : public IIRExp {
public:
	CIRTemp( const Temp::CTemp& _temp ) :
		temp( _temp )
	{}

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
	
	const TBinop binop;
	const std::shared_ptr<const IIRExp> left; 
	const std::shared_ptr<const IIRExp> right;
};


}
