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
	std::vector< std::shared_ptr<const IStm> > GetReordered();

	
private:
	
	// Указатель на тот фрейм с которым сейчас работаем
	const Frame::CFrame* frame;	
	std::vector< std::shared_ptr<const IStm> > linearized;
	std::list< std::vector< std::shared_ptr<const IStm> > > independentBlocks;

	void CLinearizer::linearize( std::shared_ptr<const IStm> root );
	void splitByLabelAndJump();
	// Перегруппирует IndependentBlocks таким образом чтобы после каждого CJump шла его false метка
	void reorder();
	
};

} // namespace IRTree