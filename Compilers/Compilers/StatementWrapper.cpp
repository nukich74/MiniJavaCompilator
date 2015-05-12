#include "StatementWrapper.h"

namespace Translate {

const IRTree::IStm* CConditionalWrapper::ToStm() const {
	Temp::CLabel* tempLabel = new Temp::CLabel();
	IRTree::CLabel* irLabel = new IRTree::CLabel( tempLabel );
	const IRTree::IStm* cond = ToConditional( tempLabel, tempLabel );
	IRTree::CSeq* seq = new IRTree::CSeq( cond, irLabel );
	return seq;
}

const IRTree::IExp* CConditionalWrapper::ToExp() const {
	Temp::CTemp* temp = new Temp::CTemp();
	IRTree::CTemp* irTemp = new IRTree::CTemp( *temp );
	IRTree::CMove* moveTrue = new IRTree::CMove( irTemp, new IRTree::CConst( 1 ) );
	IRTree::CMove* moveFalse = new IRTree::CMove( irTemp, new IRTree::CConst( 0 ) );
	Temp::CLabel* trueLabel = new Temp::CLabel();
	Temp::CLabel* falseLabel = new Temp::CLabel();
	IRTree::CLabel* trueIRLabel = new IRTree::CLabel( trueLabel );
	IRTree::CLabel* falseIRLabel = new IRTree::CLabel( falseLabel );
	IRTree::CSeq* seqTrue = new IRTree::CSeq( trueIRLabel, moveTrue );
	IRTree::CSeq* seqFalse = new IRTree::CSeq( falseIRLabel, moveFalse );
	const IRTree::IStm* cond = ToConditional( trueLabel, falseLabel );
	IRTree::CEseq* eseq = new IRTree::CEseq( cond, irTemp );
	return eseq;
}
	
const IRTree::IStm* CAndWrapper::ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const {
	Temp::CLabel* firstTrueLabel = new Temp::CLabel();
	IRTree::CLabel* firstTrueIRLabel = new IRTree::CLabel( firstTrueLabel );

	IRTree::CConst* falseConst = new IRTree::CConst(0);

	// первый аргумент
	const IRTree::IStm* firstTrueJump = nullptr;
	auto asBinop = dynamic_cast< const IRTree::CBinop* >( left );
	if( asBinop != nullptr ) {
		switch( asBinop->binop ) {
			case IRTree::B_And:
			{
				CAndWrapper andWrapper( asBinop->left.get(), asBinop->right.get() );
				firstTrueJump = andWrapper.ToConditional( firstTrueLabel, f );
				break;
			}
			default:
				assert( false );
				break;
		}
	} else {
		firstTrueJump = new IRTree::CCjump( IRTree::CJ_NotEqual, left, falseConst, firstTrueLabel, f );
	}

	IRTree::CCjump* secondTrueJump = new IRTree::CCjump( IRTree::CJ_NotEqual, right, falseConst, t, f );

	return new IRTree::CSeq( firstTrueJump, firstTrueIRLabel, secondTrueJump );
}

}