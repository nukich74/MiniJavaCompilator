// Автор: Николай Фролов.

#include <IRTreeCallLifter.h>

using namespace IRTree;

void CIRTreeCallLifter::Visit( const CMove* node )
{
	node->dst->Accept( *this );
	node->src->Accept( *this );
}

void CIRTreeCallLifter::Visit( const CExp* node )
{
	node->exp->Accept( *this );
}

void CIRTreeCallLifter::Visit( const CJump* node )
{
}

void CIRTreeCallLifter::Visit( const CCjump* node )
{
	node->left->Accept( *this );
	node->right->Accept( *this );
}

void CIRTreeCallLifter::Visit( const CSeq* node )
{
	node->left->Accept( *this );
	node->right->Accept( *this );
}

void CIRTreeCallLifter::Visit( const CConst* node )
{
}

void CIRTreeCallLifter::Visit( const CName* node )
{
}

void CIRTreeCallLifter::Visit( const CTemp* node )
{
}

void CIRTreeCallLifter::Visit( const CBinop* node )
{
	node->left->Accept( *this );
	node->right->Accept( *this );
}

void CIRTreeCallLifter::Visit( const CMem* node )
{
	node->exp->Accept( *this );
}

void CIRTreeCallLifter::Visit( const CCall* node )
{
	// Тут супервершинка.
}

void CIRTreeCallLifter::Visit( const CEseq* node )
{
	node->exp->Accept( *this );
	node->stm->Accept( *this );
}

void CIRTreeCallLifter::Visit( const CExpList* node )
{
	node->head->Accept( *this );
	node->tail->Accept( *this );
}

void CIRTreeCallLifter::Visit( const CLabel* node )
{
}