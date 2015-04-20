// Автор: Николай Фролов.

#include "InstructionsMuncher.h"

using namespace CodeGeneration;

void CInstructionsMuncher::CodeGen()
{
	for( auto& stm : reorderedStmList ) {
		munchStm( stm.get() );
	}
}