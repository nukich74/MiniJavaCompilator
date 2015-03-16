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
		CSeq* seq1 = new CSeq(rightEseq->stm.get(), moveRight);//тут
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp(*leftTemp);
		CMove* moveLeft = new CMove(leftTempIRTree, leftEseq->exp.get());//тут
		CSeq* seq2 = new CSeq(moveLeft, seq1);
		CSeq* seq3 = new CSeq(leftEseq->stm.get(), seq2);//тут
		CTemp* rightTempGet = new CTemp(*rightTemp);
		CTemp* leftTempGet = new CTemp(*leftTemp);
		CCjump* newJump = new CCjump(node->relop, leftTempGet, rightTempGet, node->iftrue, node->iffalse);
		CSeq* newNode = new CSeq(seq3, newJump);
		lastBuildStm = newNode;
	} else if (leftEseq != 0 && rightEseq == 0) {
		CCjump* newJump = new CCjump(node->relop, leftEseq->exp.get(), newRight, node->iftrue, node->iffalse);
		CSeq* newNode = new CSeq(leftEseq->stm.get(), newJump);
		lastBuildStm = newNode;
	} else if (leftEseq == 0 && rightEseq != 0) {
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempGet = new CTemp(*leftTemp);
		CMove* leftMove = new CMove(leftTempGet, newLeft);//тут
		CSeq* seq1 = new CSeq(leftMove, rightEseq->stm.get());//тут
		CCjump* newJump = new CCjump(node->relop, leftTempGet, rightEseq->exp.get(), node->iftrue, node->iffalse);
		CSeq* seq2 = new CSeq(seq1, newJump);
		lastBuildStm = seq2;
	} else {

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
		CSeq* seq1 = new CSeq(rightEseq->stm.get(), moveRight);//тут
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp(*leftTemp);
		CMove* moveLeft = new CMove(leftTempIRTree, leftEseq->exp.get());//тут
		CSeq* seq2 = new CSeq(moveLeft, seq1);
		CSeq* seq3 = new CSeq(leftEseq->stm.get(), seq2);//тут
		CTemp* rightTempGet = new CTemp(*rightTemp);
		CTemp* leftTempGet = new CTemp(*leftTemp);
		CBinop* newBinop = new CBinop(node->binop, leftTempGet, rightTempGet);
		CEseq* newNode = new CEseq(seq3, newBinop);
		lastBuildExp = newNode;
	} else if (leftEseq != 0 && rightEseq == 0) {
		CBinop* newBinop = new CBinop(node->binop, leftEseq->exp.get(), newRight);//тут
		CEseq* newNode = new CEseq(leftEseq->stm.get(), newBinop);//тут
		lastBuildExp = newNode;
	} else if (leftEseq == 0 && rightEseq != 0) {
		Temp::CTemp* leftTemp = new Temp::CTemp;
		CTemp* leftTempIRTree = new CTemp(*leftTemp);
		CMove* leftMove = new CMove(leftTempIRTree, newLeft);//тут
		CSeq* seq1 = new CSeq(leftMove, rightEseq->stm.get());
		CTemp* leftTempGet = new CTemp(*leftTemp);
		CBinop* newBinop = new CBinop(node->binop, leftTempGet, rightEseq->exp.get());
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
		CEseq* newNode = new CEseq(eseqCheck->stm.get(), newMem);//тут
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
		CEseq* newNode = new CEseq(leftSeq, eseqCheck->exp.get()); //тут
		lastBuildExp = newNode;
	} else {
		CEseq* newNode = new CEseq(newStm, newExp);
		lastBuildExp = newNode;
	}
}

void IRTreeEseqLifter::Visit(const CExpList* node) 
{
	//TODO
}

void IRTreeEseqLifter::Visit(const CLabel* node) 
{
	CLabel* newNode = new CLabel(*node);
	lastBuildStm = newNode;
}