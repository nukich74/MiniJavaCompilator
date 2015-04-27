#include "InstructionsMuncher.h"
#include <IRTree\IRStm.h>
#include <IRTree\IRExp.h>
#include <list>

using namespace CodeGeneration;

void CInstructionsMuncher::munchMove( const IRTree::IExp* dst, const IRTree::IExp* src )
{
	const IRTree::CMem* dstAsMem = dynamic_cast<const IRTree::CMem*>(dst);
	if( dstAsMem != 0 ) {
		// MOVE(MEM(e1), e2)
		return munchMove( dstAsMem, src );
	}

	// MOVE(TEMP(i), e2)
	const IRTree::CTemp* dstAsTemp = dynamic_cast<const IRTree::CTemp*>(dst);
	assert( dstAsTemp != 0 );

	const IRTree::CMem* srcAsMem = dynamic_cast<const IRTree::CMem*>(src);

	if( srcAsMem != 0 ) {
		// MOVE(TEMP(i), MEM(e2))
		return munchMove( dstAsTemp, srcAsMem );
	}

	// MOVE(TEMP(i), e2)
	emit( new CMove( "mov 'd0, 's0", std::list<Temp::CTemp>( 1, dstAsTemp->temp ), std::list<Temp::CTemp>( 1, munchExp( src ) ) ) );

}

void CInstructionsMuncher::munchMove( const IRTree::CMem* dst, const IRTree::IExp* src )
{
	emit( new CMove( "mov ['d0], 's0", std::list<Temp::CTemp>( 1, munchExp( dst->exp.get() ) ), std::list<Temp::CTemp>( 1, munchExp( src ) ) ) );
}

void CInstructionsMuncher::munchMove( const IRTree::CTemp* dst, const IRTree::CMem* src )
{
	emit( new CMove( "mov 'd0, ['s0]", std::list<Temp::CTemp>( 1, dst->temp ), std::list<Temp::CTemp>( 1, munchExp( src->exp.get( ) ) ) ) );
	// TODO оптимизация: другие шаблоны
}