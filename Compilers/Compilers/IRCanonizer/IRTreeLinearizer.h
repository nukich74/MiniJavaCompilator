// Автор: Владислав Воротилов
// Описание: Класс реализующий обход дерева, с преобразованием его в линейную структуру

#pragma once

#include <IRTreeVisitor.h>
#include <vector>
#include <list>
#include <IRStm.h>
#include "Frame.h"

namespace IRTree {

class CLinearizer {
public:
	CLinearizer( const Frame::CFrame* _frame ) : frame( _frame ) {}

	void Linearize();
	void SplitByLabelAndJump();
	// Перегруппирует IndependentBlocks таким образом чтобы после каждого CJump шла его false метка
	void Reorder();

	std::vector< std::shared_ptr<const IStm> > Linearized;
	std::list< std::vector< std::shared_ptr<const IStm> > > IndependentBlocks;
private:
	
	// Указатель на тот фрейм с которым сейчас работаем
	const Frame::CFrame* frame;
	void CLinearizer::linearize( std::shared_ptr<const IStm> root );
	
};

} // namespace IRTree