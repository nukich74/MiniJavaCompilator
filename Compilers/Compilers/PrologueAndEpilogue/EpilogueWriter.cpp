// Автор: Николай Фролов.

#include "EpilogueWriter.h"

using namespace std;
using namespace CodeGeneration;

vector< unique_ptr<CodeGeneration::IInstruction> > CEpilogueWriter::AddEpilogue( Frame::CFrame* frame )
{
	vector< unique_ptr<CodeGeneration::IInstruction> > epilogue;
	return epilogue;
}

void CEpilogueWriter::emit( CodeGeneration::IInstruction* inst, vector< unique_ptr<CodeGeneration::IInstruction> >& instList )
{
	instList.emplace_back( unique_ptr<CodeGeneration::IInstruction>( inst ) );
}