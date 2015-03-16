/*
	јвтор: ћысин ёрий
*/

#include <IRTreeEseqLifter.h>
using namespace IRTree;

void IRTreeEseqLifter::Visit(const CMove* node)
{
	node->dst->Visit(*this);
	IExp* newDst = lastBuildExp;
	node->src->Visit(*this);
	IExp* newSrc = lastBuildExp;
	CMove* newNode = new CMove(newDst, newSrc);
	lastBuildStm = dynamic_cast<IStm*>(newNode);
}

void IRTreeEseqLifter::Visit(const CExp* node) 
{
	node->exp->Visit(*this);
	IExp* newExp = lastBuildExp;
	CExp* newNode = new CExp(newExp);
	lastBuildStm = dynamic_cast<IStm*>(newNode);
}
//в книге не так
void IRTreeEseqLifter::Visit(const CJump* node)
{
	CJump* newNode = new CJump(node->label);
	lastBuildStm = newNode;
}

void IRTreeEseqLifter::Visit(const CCjump* node) 
{
	node->left->Visit(*this);
	IExp* newLeft = lastBuildExp;
	node->right->Visit(*this);
	IExp* newRight = lastBuildExp;
	CEseq* leftEseq = dynamic_cast<CEseq*>(newLeft);
	CEseq* rightEseq = dynamic_cast<CEseq*>(newRight);
	if (leftEseq != 0 && rightEseq != 0) {
		Temp::CTemp* rightTemp = new Temp::CTemp;
		CTemp* rightTempIRTree = new CTemp(*rightTemp);
		CMove* moveRight = new CMove(rightTempIRTree, rightEseq->exp.get());//тут
		moveRight->src = rightEseq->exp;
		CSeq* seq1 = new CSeq(rightEseq->stm.get(), moveRight);//тут
		seq1->left = rightEseq->stm;
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp(*leftTemp);
		CMove* moveLeft = new CMove(leftTempIRTree, leftEseq->exp.get());//тут
		moveLeft->src = leftEseq->exp;
		CSeq* seq2 = new CSeq(moveLeft, seq1);
		CSeq* seq3 = new CSeq(leftEseq->stm.get(), seq2);//тут
		seq3->left = leftEseq->stm;
		CTemp* rightTempGet = new CTemp(*rightTemp);
		CTemp* leftTempGet = new CTemp(*leftTemp);
		CCjump* newJump = new CCjump(node->relop, leftTempGet, rightTempGet, node->iftrue, node->iffalse);
		CSeq* newNode = new CSeq(seq3, newJump);
		lastBuildStm = newNode;
	} else if (leftEseq != 0 && rightEseq == 0) {
		CCjump* newJump = new CCjump(node->relop, leftEseq->exp.get(), newRight, node->iftrue, node->iffalse);//тут
		newJump->left = leftEseq->exp;
		CSeq* newNode = new CSeq(leftEseq->stm.get(), newJump);//тут
		newNode->left = leftEseq->stm;
		lastBuildStm = newNode;
	} else if (leftEseq == 0 && rightEseq != 0) {
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempSet = new CTemp(*leftTemp);
		CMove* leftMove = new CMove(leftTempSet, newLeft);
		CSeq* seq1 = new CSeq(leftMove, rightEseq->stm.get());//тут
		seq1->right = rightEseq->stm;
		CTemp* leftTempGet = new CTemp(*leftTemp);
		CCjump* newJump = new CCjump(node->relop, leftTempGet, rightEseq->exp.get(), node->iftrue, node->iffalse);//тут
		newJump->right = rightEseq->exp;
		CSeq* seq2 = new CSeq(seq1, newJump);
		lastBuildStm = seq2;
	} else {
		CCjump* newNode = new CCjump(node->relop, newLeft, newRight, node->iftrue, node->iffalse);
		lastBuildStm = newNode;
	}
}

void IRTreeEseqLifter::Visit(const CSeq* node)
{
	node->left->Visit(*this);
	IStm* newLeft = lastBuildStm;
	node->right->Visit(*this);
	IStm* newRight = lastBuildStm;
	CSeq* newNode = new CSeq(newLeft, newRight);
	lastBuildStm = newNode;
}

void IRTreeEseqLifter::Visit(const CConst* node) 
{
	CConst* newNode = new CConst(node->value);
	lastBuildExp = newNode;
}

void IRTreeEseqLifter::Visit(const CName* node) 
{
	CName* newNode = new CName(node->label);
	lastBuildExp = newNode;
}

void IRTreeEseqLifter::Visit(const CTemp* node)
{
	CTemp* newNode = new CTemp(node->temp);
	lastBuildExp = newNode;
}

void IRTreeEseqLifter::Visit(const CBinop* node) 
{
	node->left->Visit(*this);
	IExp* newLeft = lastBuildExp;
	node->right->Visit(*this);
	IExp* newRight = lastBuildExp;
	const CEseq* leftEseq = dynamic_cast<const CEseq*>(newLeft);
	const CEseq* rightEseq = dynamic_cast<const CEseq*>(newRight);
	//далее код не работает без глубокого копировани€
	if (leftEseq != 0 && rightEseq != 0) {
		//если оба потомка Eseq, то сохран€ем результаты вычислений, и только потом вычисл€ем Binop
		Temp::CTemp* rightTemp = new Temp::CTemp;
		CTemp* rightTempIRTree = new CTemp(*rightTemp);
		CMove* moveRight = new CMove(rightTempIRTree, rightEseq->exp.get());//тут
		moveRight->src = rightEseq->exp;
		CSeq* seq1 = new CSeq(rightEseq->stm.get(), moveRight);//тут
		seq1->left = rightEseq->stm;
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp(*leftTemp);
		CMove* moveLeft = new CMove(leftTempIRTree, leftEseq->exp.get());//тут
		moveLeft->src = leftEseq->exp;
		CSeq* seq2 = new CSeq(moveLeft, seq1);
		CSeq* seq3 = new CSeq(leftEseq->stm.get(), seq2);//тут
		seq3->left = leftEseq->stm;
		CTemp* rightTempGet = new CTemp(*rightTemp);
		CTemp* leftTempGet = new CTemp(*leftTemp);
		CBinop* newBinop = new CBinop(node->binop, leftTempGet, rightTempGet);
		CEseq* newNode = new CEseq(seq3, newBinop);
		lastBuildExp = newNode;
	} else if (leftEseq != 0 && rightEseq == 0) {
		CBinop* newBinop = new CBinop(node->binop, leftEseq->exp.get(), newRight);//тут
		newBinop->left = leftEseq->exp;
		CEseq* newNode = new CEseq(leftEseq->stm.get(), newBinop);//тут
		newNode->stm = leftEseq->stm;
		lastBuildExp = newNode;
	} else if (leftEseq == 0 && rightEseq != 0) {
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp(*leftTemp);
		CMove* leftMove = new CMove(leftTempIRTree, newLeft);
		CSeq* seq1 = new CSeq(leftMove, rightEseq->stm.get());
		seq1->right = rightEseq->stm;
		CTemp* leftTempGet = new CTemp(*leftTemp);
		CBinop* newBinop = new CBinop(node->binop, leftTempGet, rightEseq->exp.get());
		newBinop->right = rightEseq->exp;
		CEseq* newNode = new CEseq(seq1, newBinop);
		lastBuildExp = newNode;
	} else {
		CBinop* newBinop = new CBinop(node->binop, newLeft, newRight);
		lastBuildExp = newBinop;
	}
}

void IRTreeEseqLifter::Visit(const CMem* node) 
{
	node->exp->Visit(*this);
	IExp* newExp = lastBuildExp;
	CEseq* eseqCheck = dynamic_cast<CEseq*>(newExp);
	if (eseqCheck != 0) {
		CMem* newMem = new CMem(eseqCheck->exp.get());//тут
		newMem->exp = eseqCheck->exp;
		CEseq* newNode = new CEseq(eseqCheck->stm.get(), newMem);//тут
		newNode->stm = eseqCheck->stm;
		lastBuildExp = newNode;
	} else {
		CMem* newNode = new CMem(newExp);
		lastBuildExp = newNode;
	}
}

void IRTreeEseqLifter::Visit(const CCall* node)
{
	//TODO
}

void IRTreeEseqLifter::Visit(const CEseq* node) 
{
	node->stm->Visit(*this);
	IStm* newStm = lastBuildStm;
	node->exp->Visit(*this);
	IExp* newExp = lastBuildExp;
	CEseq* eseqCheck = dynamic_cast<CEseq*>(newExp);
	if (eseqCheck != 0) {
		CSeq* leftSeq = new CSeq(newStm, eseqCheck->stm.get()); //тут
		leftSeq->right = eseqCheck->stm;
		CEseq* newNode = new CEseq(leftSeq, eseqCheck->exp.get()); //тут
		newNode->exp = eseqCheck->exp;
		lastBuildExp = newNode;
	} else {
		CEseq* newNode = new CEseq(newStm, newExp);
		lastBuildExp = newNode;
	}
}

void IRTreeEseqLifter::Visit(const CExpList* node) 
{
	//TODO
	vector<const IExp*> args;
	vector<const IExp*> newArgs;
	const IExp* current = node->head.get();
	while (current != 0) {
		args.push_back(current);
		if (node->tail.get()) {
			current = node->tail.get()->head.get();
		} else {
			break;
		}
	}
	IStm* resultStm = dynamic_cast<IStm*>(new CConst(0));
	for (vector<const IExp*>::const_iterator iter = args.begin(); iter != args.end(); ++iter) {
		Temp::CTemp* newTemp = new Temp::CTemp;
		CTemp* newTempSet = new CTemp(*newTemp);
		CTemp* newTempGet = new CTemp(*newTemp);
		const CEseq* eseqCheck = dynamic_cast<const CEseq*>(*iter);
		if (eseqCheck) {
			CMove* setTemp = new CMove(newTempSet, eseqCheck->exp.get());//тут
			setTemp->src = eseqCheck->exp;
			CSeq* eseqReplacer = new CSeq(eseqCheck->stm.get(), setTemp);
			eseqReplacer->left = eseqCheck->stm;
			CSeq* newResultStm = new CSeq(resultStm, eseqReplacer);
			resultStm = newResultStm;
			newArgs.push_back(newTempGet);
		} else {
			CMove* setTemp = new CMove(newTempSet, *iter);
			CSeq* expReplacer = new CSeq(resultStm, setTemp);
		}
		newArgs.push_back(newTempGet);
	}
	CExpList* resultExpList = 0;
	for (vector<const IExp*>::const_reverse_iterator iter = newArgs.rbegin(); iter != newArgs.rend(); ++iter) {
		CExpList* newHeadExpList = new CExpList(*iter, resultExpList);
		resultExpList = newHeadExpList;
	}
	lastBuildPair = make_pair(resultStm, resultExpList);
}

void IRTreeEseqLifter::Visit(const CLabel* node) 
{
	CLabel* newNode = new CLabel(*node);
	lastBuildStm = newNode;
}
