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
		emit( new CodeGeneration::COper( std::string( "jmp l0" ), nullptr, nullptr, std::list<Temp::CLabel>( 1, *asJump->label ) ) );
	}
}

void CInstructionsMuncher::munchMove( const IRTree::CMem* dst, const IRTree::IExp* src )
{

}

const Temp::CTemp* CInstructionsMuncher::munchExp( const IRTree::IExp* exp )
{
	if( dynamic_cast<const IRTree::CMem*>( exp ) != 0 ) {

	} else if( dynamic_cast<const IRTree::CBinop*>( exp ) != 0 ) {

	} else if( dynamic_cast<const IRTree::CConst*>( exp ) != 0 )  {
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( "MOVE d0 <- i\n", 0, new std::list<Temp::CTemp*>( 1, tmp ) ) );
		return tmp;
	} else if( dynamic_cast<const IRTree::CTemp*>( exp ) != 0 ) {
		return &dynamic_cast<const IRTree::CTemp*>( exp )->temp;
	} else {
		assert( false );
	}
}

void CInstructionsMuncher::emit( IInstruction* instruction )
{
	assert( false );
}