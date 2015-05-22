// Автор: Николай Фролов.

#include "PrologueWriter.h"

using namespace std;
using namespace CodeGeneration;

vector< unique_ptr<CodeGeneration::IInstruction> > CPrologueWriter::AddPrologue( Frame::CFrame* frame, int numberOfTemps )
{
	vector< unique_ptr<CodeGeneration::IInstruction> > prologue;
	emit( new CLabel( Temp::CLabel( frame->Name ) ), prologue );
	emit( new COper( "push 's0", std::list<Temp::CTemp>(), std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EBP ) ) ),
		  prologue );
	emit( new COper( "mov 'd0 's0", std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EBP ) ),
		std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_ESP ) ) ), prologue );
	emit( new COper( "add 'd0 8", std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EBP ) ),
		std::list<Temp::CTemp>() ), prologue );
	saveRegisters( frame, prologue );
	int espAddition = frame->WordSize() * ( frame->LocalCounter + numberOfTemps );
	emit( new COper( "add 'd0 " + std::to_string( espAddition ), std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_ESP ) ),
		std::list<Temp::CTemp>() ), prologue );
	return prologue;
}

void CPrologueWriter::emit( CodeGeneration::IInstruction* inst, vector< unique_ptr<CodeGeneration::IInstruction> >& instList )
{
	instList.emplace_back( unique_ptr<CodeGeneration::IInstruction>( inst ) );
}

void CPrologueWriter::saveRegisters( Frame::CFrame* frame, vector< unique_ptr<CodeGeneration::IInstruction> >& instList )
{
	emit( new COper( "push 's0", std::list<Temp::CTemp>(), std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EBX ) ) ),
		  instList );
	emit( new COper( "push 's0", std::list<Temp::CTemp>(), std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_ECX ) ) ),
		  instList );
	emit( new COper( "push 's0", std::list<Temp::CTemp>(), std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EDX ) ) ),
		  instList );
	emit( new COper( "push 's0", std::list<Temp::CTemp>(), std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_EDI ) ) ),
		  instList );
	emit( new COper( "push 's0", std::list<Temp::CTemp>(), std::list<Temp::CTemp>( 1, *frame->GetRegister( Frame::R_ESI ) ) ),
		  instList );
}