// Автор: Николай Фролов.

#include "EpilogueWriter.h"

using namespace std;

vector< unique_ptr<CodeGeneration::IInstruction> > CEpilogueWriter::AddEpilogue( Frame::CFrame* frame )
{
	return vector< unique_ptr<CodeGeneration::IInstruction> >();
}

void CEpilogueWriter::emit( CodeGeneration::IInstruction*, vector< unique_ptr<CodeGeneration::IInstruction> >& instList )
{
}