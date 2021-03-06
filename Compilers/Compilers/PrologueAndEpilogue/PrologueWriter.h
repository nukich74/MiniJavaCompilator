﻿// Автор: Николай Фролов.

// Описание: добавляет код пролога к функции.

#pragma once

#include <Frame.h>
#include <Instruction.h>

class CPrologueWriter {
public:
	static std::vector< std::unique_ptr<CodeGeneration::IInstruction> > AddPrologue( const Frame::CFrame* frame, int numberOfTemps );
private:
	static void emit( CodeGeneration::IInstruction*, std::vector< std::unique_ptr<CodeGeneration::IInstruction> >& instList );
	static void saveRegisters( const Frame::CFrame* frame, std::vector< std::unique_ptr<CodeGeneration::IInstruction> >& instList );
};