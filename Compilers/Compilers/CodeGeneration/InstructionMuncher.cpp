// Автор: Николай Фролов.

#include "InstructionsMuncher.h"

using namespace CodeGeneration;

void CInstructionsMuncher::CodeGen()
{
	for( auto& stm : reorderedStmList ) {
		munchStm( stm.get() );
	}
}

void CInstructionsMuncher::emit( IInstruction* instr )
{
	instructionsList.push_back( instr );
}

Temp::CTemp* CInstructionsMuncher::munchExp( const IRTree::IExp* exp )
{

}