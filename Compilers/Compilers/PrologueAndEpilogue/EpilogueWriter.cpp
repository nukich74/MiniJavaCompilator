// Автор: Николай Фролов.

#include "EpilogueWriter.h"

using namespace std;
using namespace CodeGeneration;

vector< unique_ptr<CodeGeneration::IInstruction> > CEpilogueWriter::AddEpilogue( Frame::CFrame* frame )
{
	vector< unique_ptr<CodeGeneration::IInstruction> > epilogue;
	emit( new COper( "mov 'd0 ['s0+6*4]", std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_ESP ) ), std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EBP ) ) ),
		  epilogue );
	restoreRegisters( frame, epilogue );
	emit( new COper( "pop 'd0", std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EBP ) ), std::list<Temp::CTemp>() ),
		  epilogue );
	emit( new COper( "ret", std::list<Temp::CTemp>(), std::list<Temp::CTemp>() ), epilogue );
	return epilogue;
}

void CEpilogueWriter::emit( CodeGeneration::IInstruction* inst, vector< unique_ptr<CodeGeneration::IInstruction> >& instList )
{
	instList.emplace_back( unique_ptr<CodeGeneration::IInstruction>( inst ) );
}

void CEpilogueWriter::restoreRegisters( Frame::CFrame* frame, vector< unique_ptr<CodeGeneration::IInstruction> >& instList )
{
	emit( new COper( "pop 'd0", std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_ESI ) ), std::list<Temp::CTemp>() ),
		  instList );
	emit( new COper( "pop 'd0", std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EDI ) ), std::list<Temp::CTemp>() ),
		  instList );
	emit( new COper( "pop 'd0", std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EDX ) ), std::list<Temp::CTemp>() ),
		  instList );
	emit( new COper( "pop 'd0", std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_ECX ) ), std::list<Temp::CTemp>() ),
		  instList );
	emit( new COper( "pop 'd0", std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EBX ) ), std::list<Temp::CTemp>() ),
		  instList );
}