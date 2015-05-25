// Автор: Николай Фролов.

// Описание: добавляет код эпилога к функции.

#pragma once

#include <Instruction.h>
#include <Frame.h>

class CEpilogueWriter {
public:
	static std::vector< std::unique_ptr<CodeGeneration::IInstruction> > AddEpilogue( const Frame::CFrame* frame );
private:
	static void emit( CodeGeneration::IInstruction*, std::vector< std::unique_ptr<CodeGeneration::IInstruction> >& instList );
	static void restoreRegisters( const Frame::CFrame* frame, std::vector< std::unique_ptr<CodeGeneration::IInstruction> >& instList );
};