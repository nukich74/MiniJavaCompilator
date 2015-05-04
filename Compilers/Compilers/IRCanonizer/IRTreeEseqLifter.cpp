/*
	Автор: Мысин Юрий
*/

#include <IRTreeEseqLifter.h>
#include <iostream>
using namespace IRTree;
using namespace std;

void CIRTreeEseqLifter::Visit( const CMove* node )
{
	const CMem* memCheck = dynamic_cast<const CMem*>( node->dst.get() );
	//node->dst->Accept( *this );
	//IExp* newDst = lastBuildExp;
	//node->src->Accept( *this );
	//IExp* newSrc = lastBuildExp;
	const CCall* callCheck = dynamic_cast<const CCall*>( node->src.get() );
	if ( !callCheck ) {
		if ( memCheck ) {
			CExpList* innerList = new CExpList( 0, 0 );
			innerList->head = node->src;
			CExpList* outList = new CExpList( 0, innerList );
			outList->head = node->src;
			Visit( outList );
			CMove* newMove = new CMove( 0, 0 );
			newMove->dst = lastBuildPair.second->head;
			newMove->src = lastBuildPair.second->tail->head;
			CSeq* newNode = new CSeq( lastBuildPair.first, newMove );
			lastBuildStm = newNode;
		} else {
			CExpList* expressions = new CExpList( 0, 0 );
			expressions->head = node->src;
			Visit( expressions );
			CMove* newMove = new CMove( 0, 0 );
			newMove->dst = node->dst;
			newMove->src = lastBuildPair.second->head;
			CSeq* newNode = new CSeq( lastBuildPair.first, newMove );
			lastBuildStm = newNode;
		}
	} else {
		//все вызовы call находятся только внутри move, где dst - это CTemp
		//проверка на mem не нужна
		Visit( callCheck );
		CEseq* buildEseq = dynamic_cast<CEseq*>(lastBuildExp);
		node->dst->Accept( *this );
		IExp* newTemp = lastBuildExp;
		CMove* newMove = new CMove( newTemp, 0 );
		newMove->src = buildEseq->exp;
		CSeq* newNode = new CSeq( 0, newMove );
		newNode->left = buildEseq->stm;
		lastBuildStm = newNode;
	}
}

void CIRTreeEseqLifter::Visit( const CExp* node ) 
{
	node->exp->Accept( *this );
	IExp* newExp = lastBuildExp;
	CEseq* eseqCheck = dynamic_cast<CEseq*>( newExp );
	if ( !eseqCheck ) {
		CExp* newNode = new CExp( newExp );
		lastBuildStm = newNode;
	} else {
		CExp* newExp = new CExp( 0 );
		newExp->exp = eseqCheck->exp;
		CSeq* newSeq = new CSeq( 0, newExp );
		newSeq->left = eseqCheck->stm;
		lastBuildStm = newSeq;
	}
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
		CMove* moveRight = new CMove( rightTempIRTree, 0 );
		moveRight->src = rightEseq->exp;
		CSeq* seq1 = new CSeq( 0, moveRight );
		seq1->left = rightEseq->stm;
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp( *leftTemp );
		CMove* moveLeft = new CMove( leftTempIRTree, 0 );
		moveLeft->src = leftEseq->exp;
		CSeq* seq2 = new CSeq( moveLeft, seq1 );
		CSeq* seq3 = new CSeq( 0, seq2 );
		seq3->left = leftEseq->stm;
		CTemp* rightTempGet = new CTemp( *rightTemp );
		CTemp* leftTempGet = new CTemp( *leftTemp );
		CCjump* newJump = new CCjump( node->relop, leftTempGet, rightTempGet, node->iftrue, node->iffalse );
		CSeq* newNode = new CSeq( seq3, newJump );
		lastBuildStm = newNode;
	} else if ( leftEseq != 0 && rightEseq == 0 ) {
		CCjump* newJump = new CCjump( node->relop, 0, newRight, node->iftrue, node->iffalse );//���
		newJump->left = leftEseq->exp;
		CSeq* newNode = new CSeq( 0, newJump );
		newNode->left = leftEseq->stm;
		lastBuildStm = newNode;
	} else if ( leftEseq == 0 && rightEseq != 0 ) {
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempSet = new CTemp( *leftTemp );
		CMove* leftMove = new CMove( leftTempSet, newLeft );
		CSeq* seq1 = new CSeq( leftMove, 0 );
		seq1->right = rightEseq->stm;
		CTemp* leftTempGet = new CTemp( *leftTemp );
		CCjump* newJump = new CCjump( node->relop, leftTempGet, 0, node->iftrue, node->iffalse );
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
	if ( leftEseq != 0 && rightEseq != 0 ) {
		//если оба потомка Eseq, то сохраняем результаты вычислений, и только потом вычисляем Binop
		Temp::CTemp* rightTemp = new Temp::CTemp;
		CTemp* rightTempIRTree = new CTemp( *rightTemp );
		CMove* moveRight = new CMove( rightTempIRTree, 0 );
		moveRight->src = rightEseq->exp;
		CSeq* seq1 = new CSeq( 0, moveRight );
		seq1->left = rightEseq->stm;
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp( *leftTemp );
		CMove* moveLeft = new CMove( leftTempIRTree, 0 );
		moveLeft->src = leftEseq->exp;
		CSeq* seq2 = new CSeq( moveLeft, seq1 );
		CSeq* seq3 = new CSeq( 0, seq2 );
		seq3->left = leftEseq->stm;
		CTemp* rightTempGet = new CTemp( *rightTemp );
		CTemp* leftTempGet = new CTemp( *leftTemp );
		CBinop* newBinop = new CBinop( node->binop, leftTempGet, rightTempGet );
		CEseq* newNode = new CEseq( seq3, newBinop );
		lastBuildExp = newNode;
	} else if ( leftEseq != 0 && rightEseq == 0 ) {
		CBinop* newBinop = new CBinop( node->binop, 0, newRight );
		newBinop->left = leftEseq->exp;
		CEseq* newNode = new CEseq( 0, newBinop );
		newNode->stm = leftEseq->stm;
		lastBuildExp = newNode;
	} else if ( leftEseq == 0 && rightEseq != 0 ) {
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp( *leftTemp );
		CMove* leftMove = new CMove( leftTempIRTree, newLeft );
		CSeq* seq1 = new CSeq( leftMove, 0 );
		seq1->right = rightEseq->stm;
		CTemp* leftTempGet = new CTemp( *leftTemp );
		CBinop* newBinop = new CBinop( node->binop, leftTempGet, 0 );
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
		CMem* newMem = new CMem( 0 );
		newMem->exp = eseqCheck->exp;
		CEseq* newNode = new CEseq( 0, newMem );
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
	CCall* newCall = new CCall( 0, *lastBuildPair.second );
	newCall->func = node->func;
	CEseq* resultEseq = new CEseq(lastBuildPair.first, newCall);
	lastBuildExp = resultEseq;
}

void CIRTreeEseqLifter::Visit( const CEseq* node )
{
	node->stm->Accept( *this );
	IStm* newStm = lastBuildStm;
	node->exp->Accept( *this );
	IExp* newExp = lastBuildExp;
 	CEseq* eseqCheck = dynamic_cast<CEseq*>( newExp );
	if ( eseqCheck != 0 ) {
		CSeq* leftSeq = new CSeq( newStm, 0 );
		leftSeq->right = eseqCheck->stm;
		CEseq* newNode = new CEseq( leftSeq, 0 );
		newNode->exp = eseqCheck->exp;
		lastBuildExp = newNode;
	} else {
		CEseq* newNode = new CEseq( newStm, newExp );
		lastBuildExp = newNode;
	}
}

void CIRTreeEseqLifter::Visit( const CExpList* node )
{
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
	const IStm* resultStm = 0;
	for ( vector<const IExp*>::const_iterator iter = args.begin(); iter != args.end(); ++iter ) 
	{
		Temp::CTemp* newTemp = new Temp::CTemp;
		CTemp* newTempSet = new CTemp( *newTemp );
		CTemp* newTempGet = new CTemp( *newTemp );
		( *iter )->Accept( *this );
		IExp* modifiedExp = lastBuildExp;
		const CEseq* eseqCheck = dynamic_cast<const CEseq*>( modifiedExp );
		if ( eseqCheck ) {
			CMove* setTemp = new CMove( newTempSet, 0 );
			setTemp->src = eseqCheck->exp;
			CSeq* eseqStmReplacer = new CSeq( 0, setTemp );
			eseqStmReplacer->left = eseqCheck->stm;
			const IStm* newResultStm = 0;
			if (resultStm == 0) {
				newResultStm = eseqStmReplacer;
			} else {
				newResultStm = new CSeq( resultStm, eseqStmReplacer );
			}
			resultStm = newResultStm;
		} else {
			CMove* setTemp = new CMove( newTempSet, modifiedExp );
			const IStm* newResultStm = 0;
			if (resultStm == 0) {
				newResultStm = setTemp;
			} else {
				newResultStm = new CSeq( resultStm, setTemp );
			}
			resultStm = newResultStm;
		}
		newArgs.push_back( newTempGet );
	}
	if (resultStm == 0) {
		resultStm = new CExp( new CConst(0) );
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
	CLabel* newNode = new CLabel( node->label );
	lastBuildStm = newNode;
}
