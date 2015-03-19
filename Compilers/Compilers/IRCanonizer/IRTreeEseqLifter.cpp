/*
	Автор: Мысин Юрий
*/

#include <IRTreeEseqLifter.h>
using namespace IRTree;
using namespace std;

void CIRTreeEseqLifter::Visit( const CMove* node )
{
	node->dst->Accept( *this );
	IExp* newDst = lastBuildExp;
	node->src->Accept( *this );
	IExp* newSrc = lastBuildExp;
	CCall* callCheck = dynamic_cast<CCall*>( newSrc );
	if (!callCheck) {
		CMove* newNode = new CMove( newDst, newSrc );
		lastBuildStm = newNode;
	} else {
		CCall* newCall = new CCall( callCheck->func, *lastBuildPair.second );
		CMove* newMove = new CMove( newDst, newCall );
		CSeq* newNode = new CSeq( lastBuildPair.first, newMove );
		lastBuildStm = newNode;
	}
}

void CIRTreeEseqLifter::Visit( const CExp* node ) 
{
	node->exp->Accept( *this );
	IExp* newExp = lastBuildExp;
	CExp* newNode = new CExp( newExp );
	lastBuildStm = newNode;
}

void CIRTreeEseqLifter::Visit( const CJump* node )
{
	CJump* newNode = new CJump( node->label );
	lastBuildStm = newNode;
}

void CIRTreeEseqLifter::Visit( const CCjump* node ) 
{
	node->left->Accept( *this );
	IExp* newLeft = lastBuildExp;
	node->right->Accept( *this );
	IExp* newRight = lastBuildExp;
	CEseq* leftEseq = dynamic_cast<CEseq*>( newLeft );
	CEseq* rightEseq = dynamic_cast<CEseq*>( newRight );
	if ( leftEseq != 0 && rightEseq != 0 ) {
		Temp::CTemp* rightTemp = new Temp::CTemp;
		CTemp* rightTempIRTree = new CTemp( *rightTemp );
		CMove* moveRight = new CMove( rightTempIRTree, rightEseq->exp.get() );//���
		moveRight->src = rightEseq->exp;
		CSeq* seq1 = new CSeq( rightEseq->stm.get(), moveRight );//���
		seq1->left = rightEseq->stm;
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp( *leftTemp );
		CMove* moveLeft = new CMove( leftTempIRTree, leftEseq->exp.get() );//���
		moveLeft->src = leftEseq->exp;
		CSeq* seq2 = new CSeq( moveLeft, seq1 );
		CSeq* seq3 = new CSeq( leftEseq->stm.get(), seq2 );//���
		seq3->left = leftEseq->stm;
		CTemp* rightTempGet = new CTemp( *rightTemp );
		CTemp* leftTempGet = new CTemp( *leftTemp );
		CCjump* newJump = new CCjump( node->relop, leftTempGet, rightTempGet, node->iftrue, node->iffalse );
		CSeq* newNode = new CSeq( seq3, newJump );
		lastBuildStm = newNode;
	} else if ( leftEseq != 0 && rightEseq == 0 ) {
		CCjump* newJump = new CCjump( node->relop, leftEseq->exp.get(), newRight, node->iftrue, node->iffalse );//���
		newJump->left = leftEseq->exp;
		CSeq* newNode = new CSeq( leftEseq->stm.get(), newJump );//���
		newNode->left = leftEseq->stm;
		lastBuildStm = newNode;
	} else if ( leftEseq == 0 && rightEseq != 0 ) {
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempSet = new CTemp( *leftTemp );
		CMove* leftMove = new CMove( leftTempSet, newLeft );
		CSeq* seq1 = new CSeq( leftMove, rightEseq->stm.get() );//���
		seq1->right = rightEseq->stm;
		CTemp* leftTempGet = new CTemp( *leftTemp );
		CCjump* newJump = new CCjump( node->relop, leftTempGet, rightEseq->exp.get(), node->iftrue, node->iffalse );//���
		newJump->right = rightEseq->exp;
		CSeq* seq2 = new CSeq( seq1, newJump );
		lastBuildStm = seq2;
	} else {
		CCjump* newNode = new CCjump( node->relop, newLeft, newRight, node->iftrue, node->iffalse );
		lastBuildStm = newNode;
	}
}

void CIRTreeEseqLifter::Visit( const CSeq* node )
{
	node->left->Accept( *this );
	IStm* newLeft = lastBuildStm;
	node->right->Accept( *this );
	IStm* newRight = lastBuildStm;
	CSeq* newNode = new CSeq( newLeft, newRight );
	lastBuildStm = newNode;
}

void CIRTreeEseqLifter::Visit( const CConst* node ) 
{
	CConst* newNode = new CConst( node->value );
	lastBuildExp = newNode;
}

void CIRTreeEseqLifter::Visit( const CName* node ) 
{
	CName* newNode = new CName( node->label );
	lastBuildExp = newNode;
}

void CIRTreeEseqLifter::Visit( const CTemp* node )
{
	CTemp* newNode = new CTemp( node->temp );
	lastBuildExp = newNode;
}

void CIRTreeEseqLifter::Visit( const CBinop* node ) 
{
	node->left->Accept( *this );
	IExp* newLeft = lastBuildExp;
	node->right->Accept( *this );
	IExp* newRight = lastBuildExp;
	const CEseq* leftEseq = dynamic_cast<const CEseq*>( newLeft );
	const CEseq* rightEseq = dynamic_cast<const CEseq*>( newRight );
	//далее код не работает без глубокого копирования
	if ( leftEseq != 0 && rightEseq != 0 ) {
		//если оба потомка Eseq, то сохраняем результаты вычислений, и только потом вычисляем Binop
		Temp::CTemp* rightTemp = new Temp::CTemp;
		CTemp* rightTempIRTree = new CTemp( *rightTemp );
		CMove* moveRight = new CMove( rightTempIRTree, rightEseq->exp.get() );//���
		moveRight->src = rightEseq->exp;
		CSeq* seq1 = new CSeq( rightEseq->stm.get(), moveRight );//���
		seq1->left = rightEseq->stm;
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp( *leftTemp );
		CMove* moveLeft = new CMove( leftTempIRTree, leftEseq->exp.get() );//���
		moveLeft->src = leftEseq->exp;
		CSeq* seq2 = new CSeq( moveLeft, seq1 );
		CSeq* seq3 = new CSeq( leftEseq->stm.get(), seq2 );//���
		seq3->left = leftEseq->stm;
		CTemp* rightTempGet = new CTemp( *rightTemp );
		CTemp* leftTempGet = new CTemp( *leftTemp );
		CBinop* newBinop = new CBinop( node->binop, leftTempGet, rightTempGet );
		CEseq* newNode = new CEseq( seq3, newBinop );
		lastBuildExp = newNode;
	} else if ( leftEseq != 0 && rightEseq == 0 ) {
		CBinop* newBinop = new CBinop( node->binop, leftEseq->exp.get(), newRight );//���
		newBinop->left = leftEseq->exp;
		CEseq* newNode = new CEseq( leftEseq->stm.get(), newBinop );//���
		newNode->stm = leftEseq->stm;
		lastBuildExp = newNode;
	} else if ( leftEseq == 0 && rightEseq != 0 ) {
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp( *leftTemp );
		CMove* leftMove = new CMove( leftTempIRTree, newLeft );
		CSeq* seq1 = new CSeq( leftMove, rightEseq->stm.get() );
		seq1->right = rightEseq->stm;
		CTemp* leftTempGet = new CTemp( *leftTemp );
		CBinop* newBinop = new CBinop( node->binop, leftTempGet, rightEseq->exp.get() );
		newBinop->right = rightEseq->exp;
		CEseq* newNode = new CEseq( seq1, newBinop );
		lastBuildExp = newNode;
	} else {
		CBinop* newBinop = new CBinop( node->binop, newLeft, newRight );
		lastBuildExp = newBinop;
	}
}

void CIRTreeEseqLifter::Visit( const CMem* node ) 
{
	node->exp->Accept( *this );
	IExp* newExp = lastBuildExp;
	CEseq* eseqCheck = dynamic_cast<CEseq*>( newExp );
	if ( eseqCheck != 0 ) {
		CMem* newMem = new CMem( eseqCheck->exp.get() );//���
		newMem->exp = eseqCheck->exp;
		CEseq* newNode = new CEseq( eseqCheck->stm.get(), newMem );//���
		newNode->stm = eseqCheck->stm;
		lastBuildExp = newNode;
	} else {
		CMem* newNode = new CMem( newExp );
		lastBuildExp = newNode;
	}
}

void CIRTreeEseqLifter::Visit( const CCall* node )
{
	Visit( &( node->args ) );
}

void CIRTreeEseqLifter::Visit( const CEseq* node )
{
	node->stm->Accept( *this );
	IStm* newStm = lastBuildStm;
	node->exp->Accept( *this );
	IExp* newExp = lastBuildExp;
	CEseq* eseqCheck = dynamic_cast<CEseq*>( newExp );
	if ( eseqCheck != 0 ) {
		CSeq* leftSeq = new CSeq( newStm, eseqCheck->stm.get() ); //���
		leftSeq->right = eseqCheck->stm;
		CEseq* newNode = new CEseq( leftSeq, eseqCheck->exp.get() ); //���
		newNode->exp = eseqCheck->exp;
		lastBuildExp = newNode;
	} else {
		CEseq* newNode = new CEseq( newStm, newExp );
		lastBuildExp = newNode;
	}
}

void CIRTreeEseqLifter::Visit( const CExpList* node )
{
	//TODO
	vector<const IExp*> args;
	vector<const IExp*> newArgs;
	const IExp* current = node->head.get();
	const CExpList* currList = node;
	while ( current != 0 ) 
	{
		args.push_back( current );
		if ( currList->tail.get() ) {
			current = currList->tail.get()->head.get();
			currList = currList->tail.get();
		} else {
			break;
		}
	}
	IStm* resultStm = dynamic_cast<IStm*>(new CConst(0));
	for ( vector<const IExp*>::const_iterator iter = args.begin(); iter != args.end(); ++iter ) 
	{
		Temp::CTemp* newTemp = new Temp::CTemp;
		CTemp* newTempSet = new CTemp( *newTemp );
		CTemp* newTempGet = new CTemp( *newTemp );
		const CEseq* eseqCheck = dynamic_cast<const CEseq*>( *iter );
		if (eseqCheck) {
			CMove* setTemp = new CMove( newTempSet, eseqCheck->exp.get() );//���
			setTemp->src = eseqCheck->exp;
			CSeq* eseqReplacer = new CSeq( eseqCheck->stm.get(), setTemp );
			eseqReplacer->left = eseqCheck->stm;
			CSeq* newResultStm = new CSeq( resultStm, eseqReplacer );
			resultStm = newResultStm;
			newArgs.push_back( newTempGet );
		} else {
			CMove* setTemp = new CMove( newTempSet, *iter );
			CSeq* expReplacer = new CSeq( resultStm, setTemp );
		}
		newArgs.push_back( newTempGet );
	}
	CExpList* resultExpList = 0;
	for ( vector<const IExp*>::const_reverse_iterator iter = newArgs.rbegin(); iter != newArgs.rend(); ++iter )
	{
		CExpList* newHeadExpList = new CExpList( *iter, resultExpList );
		resultExpList = newHeadExpList;
	}
	lastBuildPair = make_pair( resultStm, resultExpList );
}

void CIRTreeEseqLifter::Visit( const CLabel* node ) 
{
	CLabel* newNode = new CLabel( *node );
	lastBuildStm = newNode;
}
