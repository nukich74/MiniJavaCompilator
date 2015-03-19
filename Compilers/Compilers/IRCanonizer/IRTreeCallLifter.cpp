// Автор: Николай Фролов.

#include <IRTreeCallLifter.h>

using namespace IRTree;

void CIRTreeCallLifter::Visit( const CMove* node )
{
	node->dst->Accept( *this );
	IExp* tmpDst = lastExp;
	node->src->Accept( *this );
	IExp* tmpSrc = lastExp;
	lastStm = new CMove( tmpDst, tmpSrc );
}

void CIRTreeCallLifter::Visit( const CExp* node )
{
	node->exp->Accept( *this );
	IExp* tmpExp = lastExp;
	lastStm = new CExp( tmpExp );
}

void CIRTreeCallLifter::Visit( const CJump* node )
{
	Temp::CLabel* tmpLabel = new Temp::CLabel( node->label->Name() );
	lastStm = new CJump( tmpLabel );
}

void CIRTreeCallLifter::Visit( const CCjump* node )
{
	node->left->Accept( *this );
	IExp* tmpLeft = lastExp;
	node->right->Accept( *this );
	IExp* tmpRight = lastExp;
	Temp::CLabel* iffalse = new Temp::CLabel( node->iffalse->Name() );
	Temp::CLabel* iftrue = new Temp::CLabel( node->iftrue->Name() );
	lastStm = new CCjump( node->relop, tmpLeft, tmpRight, iftrue, iffalse );
}

void CIRTreeCallLifter::Visit( const CSeq* node )
{
	node->left->Accept( *this );
	IStm* tmpLeft = lastStm;
	node->right->Accept( *this );
	IStm* tmpRight = lastStm;
	lastStm = new CSeq( tmpLeft, tmpRight );
}

void CIRTreeCallLifter::Visit( const CConst* node )
{
	lastExp = new CConst( node->value );
}

void CIRTreeCallLifter::Visit( const CName* node )
{
	Temp::CLabel* tmpLabel = new Temp::CLabel( node->label->Name() );
	lastExp = new CName( tmpLabel );
}

void CIRTreeCallLifter::Visit( const CTemp* node )
{
	lastExp = new CTemp( node->temp );	
}

void CIRTreeCallLifter::Visit( const CBinop* node )
{
	node->left->Accept( *this );
	IExp* tmpLeft = lastExp;
	node->right->Accept( *this );
	IExp* tmpRight = lastExp;
	lastExp = new CBinop( node->binop, tmpLeft, tmpRight );
}

void CIRTreeCallLifter::Visit( const CMem* node )
{
	node->exp->Accept( *this );
	IExp* tmpExp = lastExp;
	lastExp = new CMem( tmpExp );
}

void CIRTreeCallLifter::Visit( const CCall* node )
{
	node->func->Accept( *this );
	IExp* tmpFunc = lastExp;
	node->args.Accept( *this );
	CExpList* tmpExpList = lastExpList;
	CTemp* newTmp = new CTemp( Temp::CTemp() );
	lastExp = new CEseq( new CMove( newTmp, new CCall( tmpFunc, *tmpExpList ) ), newTmp );
}

void CIRTreeCallLifter::Visit( const CEseq* node )
{
	node->exp->Accept( *this );
	IExp* tmpExp = lastExp;
	node->stm->Accept( *this );
	IStm* tmpStm = lastStm;
	lastExp = new CEseq( tmpStm, tmpExp );
}

void CIRTreeCallLifter::Visit( const CExpList* node )
{
	node->head->Accept( *this );
	IExp* tmpHead = lastExp;
	if( node->tail != nullptr ) {
		node->tail->Accept( *this );
		lastExpList = new CExpList( tmpHead, lastExpList );
	} else {
		lastExpList = new CExpList( tmpHead, nullptr );
	}
}

void CIRTreeCallLifter::Visit( const CLabel* node )
{
	lastStm = new CLabel( node->label );
}