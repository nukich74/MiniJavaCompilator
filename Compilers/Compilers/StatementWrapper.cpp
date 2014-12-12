#include "StatementWrapper.h"

namespace Translate {
	const IRTree::IIRStm* CConditionalWrapper::ToStm() const {
		Temp::CLabel* tempLabel = new Temp::CLabel();
		IRTree::CIRLabel* irLabel = new IRTree::CIRLabel( tempLabel );
		const IRTree::IIRStm* cond = ToConditional( tempLabel, tempLabel );
		IRTree::CIRSeq* seq = new IRTree::CIRSeq( cond, irLabel );
		return seq;
	}

	const IRTree::IIRExp* CConditionalWrapper::ToExp() const {
		Temp::CTemp* temp = new Temp::CTemp();
		IRTree::CIRTemp* irTemp = new IRTree::CIRTemp( *temp );
		IRTree::CIRMove* moveTrue = new IRTree::CIRMove( irTemp, new IRTree::CIRConst( 1 ) );
		IRTree::CIRMove* moveFalse = new IRTree::CIRMove( irTemp, new IRTree::CIRConst( 0 ) );
		Temp::CLabel* trueLabel = new Temp::CLabel();
		Temp::CLabel* falseLabel = new Temp::CLabel();
		IRTree::CIRLabel* trueIRLabel = new IRTree::CIRLabel( trueLabel );
		IRTree::CIRLabel* falseIRLabel = new IRTree::CIRLabel( falseLabel );
		IRTree::CIRSeq* seqTrue = new IRTree::CIRSeq( trueIRLabel, moveTrue );
		IRTree::CIRSeq* seqFalse = new IRTree::CIRSeq( falseIRLabel, moveFalse );
		const IRTree::IIRStm* cond = ToConditional( trueLabel, falseLabel );
		IRTree::CIREseq* eseq = new IRTree::CIREseq( cond, irTemp );
		return eseq;
	}
	
	const IRTree::IIRStm* CAndWrapper::ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) {
		Temp::CLabel* firstTrueLabel = new Temp::CLabel();
		IRTree::CIRConst* falseConst = new IRTree::CIRConst(0);
		IRTree::CIRCjump* firstTrueJump = new IRTree::CIRCjump( IRTree::CJ_NotEqual, left, falseConst, firstTrueLabel, f );
		IRTree::CIRLabel* firstTrueIRLabel = new IRTree::CIRLabel( firstTrueLabel );
		IRTree::CIRCjump* secondTrueJump = new IRTree::CIRCjump( IRTree::CJ_NotEqual, right, falseConst, t, f );
		IRTree::CIRSeq* firstFalseSeq = new IRTree::CIRSeq( firstTrueIRLabel, secondTrueJump );
		IRTree::CIRSeq* finalSeq = new IRTree::CIRSeq( firstTrueJump, firstFalseSeq );
		return finalSeq;
	}

	const IRTree::IIRStm* CLessWrapper::ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) {
		IRTree::CIRCjump* returnValue = new IRTree::CIRCjump( IRTree::CJ_Less, left, right, t, f );
		return returnValue;
	}
}