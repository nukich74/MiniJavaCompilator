#include "InstructionsMuncher.h"
#include <IRTree\IRStm.h>
#include <IRTree\IRExp.h>
#include <list>

using namespace CodeGeneration;

const Temp::CTemp* CInstructionsMuncher::munchExp( const IRTree::IExp* exp )
{
	if( dynamic_cast< const IRTree::CMem* >( exp ) != 0 ) {

	} else if( dynamic_cast< const IRTree::CBinop* >( exp ) != 0 ) {

	} else if( dynamic_cast< const IRTree::CConst* >( exp ) != 0 ) {
		Temp::CTemp* tmp = new Temp::CTemp();
		emit( new COper( "MOVE d0 <- i\n", 0, new std::list<Temp::CTemp*>( 1, tmp ) ) );
		return tmp;
	} else if( dynamic_cast< const IRTree::CTemp* >( exp ) != 0 ) {
		return &dynamic_cast< const IRTree::CTemp* >( exp )->temp;
	} else {
		assert( false );
	}
}
