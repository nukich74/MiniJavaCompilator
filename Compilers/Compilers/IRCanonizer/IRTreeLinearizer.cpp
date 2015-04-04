// Автор: Владислав Воротилов
// Описание: Класс реализующий обход дерева, с преобразованием его в линейную структуру

#include "IRTreeLinearizer.h"
#include <assert.h>
#include <IRExp.h>

using namespace std;

namespace IRTree {

void CLinearizer::Linearize( std::shared_ptr<const IStm> root )
{
	const CSeq* seq = dynamic_cast< const CSeq* >( root.get() );
	if( seq != nullptr ) {
		Linearize( seq->left );
		Linearize( seq->right );
		return;
	}
	const CEseq* eseq = dynamic_cast< const CEseq* >( root.get() );
	if( eseq != nullptr ) {
		linearized.emplace_back( shared_ptr<IStm>( new CExp( eseq->exp.get() ) ) );
		Linearize( eseq->stm );
		return;
	}
	linearized.push_back( root );
}

} // namespace IRTree