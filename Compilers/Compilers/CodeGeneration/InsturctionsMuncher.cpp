// Автор: Николай Фролов.

#include "InstructionsMuncher.h"
#include <IRTree\IRStm.h>
#include <IRTree\IRExp.h>
#include <list>

using namespace CodeGeneration;

void CInstructionsMuncher::CodeGen()
{
	for( auto& stm : reorderedStmList ) {
		munchStm( stm.get() );
	}
}

void CInstructionsMuncher::munchStm( const IRTree::IStm* stm )
{
	// MOVE(...)
	const IRTree::CMove* asMove = dynamic_cast<const IRTree::CMove*>(stm);
	if( asMove != 0 ) {
		const IRTree::CMem* dstAsMem = dynamic_cast<const IRTree::CMem*>(asMove->dst.get());
		assert( dstAsMem != 0 );
		return munchMove( dstAsMem, asMove->src.get() );
	}

	// Seq
	const IRTree::CSeq* asSeq = dynamic_cast< const IRTree::CSeq* >(stm);
	if( asSeq != nullptr ) {
		munchStm( asSeq->left.get( ) );
		munchStm( asSeq->right.get( ) );
	}

	// Label
	const IRTree::CLabel* asLabel = dynamic_cast< const IRTree::CLabel* >(stm);
	if( asLabel != nullptr ) {
		emit( new CodeGeneration::CLabel( *asLabel->label ) );
	}

	// Jump
	const IRTree::CJump* asJump = dynamic_cast< const IRTree::CJump* >(stm);
	if( asJump != nullptr ) {
		emit( new CodeGeneration::COper( std::string( "jmp l0" ), nullptr, nullptr, new std::list<Temp::CLabel>( 1, *asJump->label ) ) );
	}

	// Exp (тот который забывает про результат)
	const IRTree::CExp* asExp = dynamic_cast<const IRTree::CExp*>( stm );
	if( asExp != nullptr ) {
		munchExp( asExp->exp.get() );
	}

	// CJump
	const IRTree::CCjump* asCjump = dynamic_cast<const IRTree::CCjump*>(stm);
	if( asCjump != nullptr ) {
		auto left = munchExp( asCjump->left.get() );
		auto right = munchExp( asCjump->right.get() );
		auto cmp = new std::list<Temp::CTemp*>( );
		auto labelList = new std::list<Temp::CLabel>();
		labelList->push_back( *(asCjump->iftrue) );
		cmp->push_back( left );
		cmp->push_back( right );
		emit( new CodeGeneration::COper( std::string( "cmp s0 s1" ), nullptr, cmp, nullptr ) );
		switch( asCjump->relop ) {
		case IRTree::CJ_Less:
			emit( new CodeGeneration::COper( std::string( "jl l0" ), nullptr, nullptr, labelList ) );
			break;
		case IRTree::CJ_Greater:
			emit( new CodeGeneration::COper( std::string( "jg l0" ), nullptr, nullptr, labelList ) );
			break;
		case IRTree::CJ_EqLess:
			emit( new CodeGeneration::COper( std::string( "jle l0" ), nullptr, nullptr, labelList ) );
			break;
		case IRTree::CJ_EqGreater:
			emit( new CodeGeneration::COper( std::string( "jge l0" ), nullptr, nullptr, labelList ) );
			break;
		case IRTree::CJ_Equal:
			emit( new CodeGeneration::COper( std::string( "je l0" ), nullptr, nullptr, labelList ) );
			break;
		case IRTree::CJ_NotEqual:
			emit( new CodeGeneration::COper( std::string( "jne l0" ), nullptr, nullptr, labelList ) );
			break;
		default:
			assert( false );
			break;
		}
	}

}

void CInstructionsMuncher::munchMove( const IRTree::CMem* dst, const IRTree::IExp* src )
{

}

void CInstructionsMuncher::emit( IInstruction* instruction )
{
	instructionsList.emplace_back( std::unique_ptr<IInstruction>( instruction ) );
}