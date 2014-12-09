// Автор: Азат Давлетшин
// Описание: Вспомогательные классы и константы
#pragma once

#include <IRExp.h>
#include <memory>

namespace IRTree {

class CIRExpList {
public:
	CIRExpList( const IIRExp* const _head, const CIRExpList* const _tail ) :
		head( _head ), tail( _tail )
	{}

	std::shared_ptr<const IIRExp> head;
	std::shared_ptr<const CIRExpList> tail;
};

class CIRStmList {
	CIRStmList( const IIRStm* const _head, const CIRStmList* const _tail ) :
		head( _head ), tail( _tail )
	{}

	std::shared_ptr<const IIRStm> head;
	std::shared_ptr<const CIRStmList> tail;
};

// Арифметика
enum TBinop {
	B_Plus,
	B_Minus,
	B_Mul
};

// Логическое
enum TCJump {
	CJ_Less
};

} // namespace IRTree 