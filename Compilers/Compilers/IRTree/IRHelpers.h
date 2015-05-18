// Автор: Азат Давлетшин
// Описание: Вспомогательные классы и константы
#pragma once

#include <IRTree.h>
#include "IRTreeVisitor.h"
#include <memory>
#include <string>
#include "FineAssert.h"

namespace IRTree {

class CExpList {
public:
	CExpList( const IExp* const _head, const CExpList* const _tail ) :
		head( _head ), tail( _tail )
	{}

	void Accept( IVisitor& printer ) const
	{
		printer.Visit( this );
	}

	std::shared_ptr<const IExp> head;
	std::shared_ptr<const CExpList> tail;
};

class CStmList {
	CStmList( const IStm* const _head, const CStmList* const _tail ) :
		head( _head ), tail( _tail )
	{}

	std::shared_ptr<const IStm> head;
	std::shared_ptr<const CStmList> tail;
};

// Арифметика
enum TBinop {
	B_Plus,
	B_Minus,
	B_Mul,
	B_Division,
	B_Xor,
	B_Less,
	B_Greater,
	B_And,

	B_Count
};

std::string ToString( const TBinop binOp );

// Логическое
enum TCJump {
	CJ_Less,
	CJ_Greater,
	CJ_EqLess,
	CJ_EqGreater,
	CJ_Equal,
	CJ_NotEqual,

	CJ_Count
};

} // namespace IRTree 