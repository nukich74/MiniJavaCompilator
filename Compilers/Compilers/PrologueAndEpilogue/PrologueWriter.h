// Автор: Николай Фролов.

// Описание: добавляет код пролога к функции.

#pragma once

#include <Frame.h>
#include <Instruction.h>

class CPrologueWriter {
public:
	static std::vector< std::unique_ptr<CodeGeneration::IInstruction> > AddPrologue( Frame::CFrame* frame, int numberOfTemps );
private:

};