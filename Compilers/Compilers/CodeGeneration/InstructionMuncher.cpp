// Автор: Николай Фролов.

#include "InstructionsMuncher.h"
#include <IRTree\IRStm.h>
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
	const IRTree::CSeq* asSeq = dynamic_cast< const IRTree::CSeq* >( stm );
	if( asSeq != nullptr ) {
		munchStm( asSeq->left.get() );
		munchStm( asSeq->right.get() );
	}

	// Label
	const IRTree::CLabel* asLabel = dynamic_cast< const IRTree::CLabel* >( stm );
	if( asLabel != nullptr ) {
		emit( new CodeGeneration::CLabel( *asLabel->label ) );
	}

	// Jump
	const IRTree::CJump* asJump = dynamic_cast< const IRTree::CJump* >( stm );
	if( asJump != nullptr ) {
		emit( new CodeGeneration::COper( std::string( "jmp l0" ), std::list<Temp::CTemp>(), std::list<Temp::CTemp>(), std::list<Temp::CLabel>( 1, *asJump->label ) ) );
	}

}

void CInstructionsMuncher::emit( IInstruction* instruction )
{
	assert( false );
}