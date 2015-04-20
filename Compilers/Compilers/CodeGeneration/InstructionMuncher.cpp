// Автор: Николай Фролов.

#include "InstructionsMuncher.h"
#include <IRTree\IRStm.h>
#include <IRTree\IRExp.h>

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

	// Перебор других случаев (TODO Влад)
}

void CInstructionsMuncher::munchMove( const IRTree::CMem* dst, const IRTree::IExp* src )
{

}