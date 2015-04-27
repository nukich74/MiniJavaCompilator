﻿// Автор: Азат Давлетшин
// Описание: класс-механизм, который из упорядоченного списка Stm-ов получает список листинг программы в виде
// списка IInstruction

#pragma once

#include <CodeGeneration\Instruction.h>
#include <vector>
#include <memory>
#include <IRTree.h>
#include <IRExp.h>
#include <IRStm.h>

namespace CodeGeneration {

class CInstructionsMuncher {
public:
	// Передаем упорядоченный список IStm-ов как аргумент механизма
	CInstructionsMuncher( const std::vector< std::shared_ptr<const IRTree::IStm> >& _reorderedStmList, const Frame::CFrame* _frame ) :
		reorderedStmList( _reorderedStmList ), frame( _frame ) {}

	// Построить спискок ассемблерных инструкций
	void CodeGen();

	// Результат работы механизма
	const std::vector< std::unique_ptr<IInstruction> >& GetInstructionsList() const
		{ return instructionsList; }

private:
	const std::vector< std::shared_ptr<const IRTree::IStm> >& reorderedStmList;
	std::vector< std::unique_ptr<IInstruction> > instructionsList;
	const Frame::CFrame* frame;

	void emit( IInstruction* instruction );

	// Обработка statement.
	void munchStm( const IRTree::IStm* stm );
	// Обработка statement MOVE
	void munchMove( const IRTree::IExp* dst, const IRTree::IExp* src );
	// MOVE из регистра в память
	void munchMove( const IRTree::CMem* dst, const IRTree::IExp* src );
	// MOVE из памяти в регистр
	void munchMove( const IRTree::CTemp* dst, const IRTree::CMem* src );

	// Обработка expression.
	Temp::CTemp munchExp( const IRTree::IExp* exp );
	Temp::CTemp munchExpMem( const IRTree::CMem* exp );
	Temp::CTemp munchExpBinopInMem( const IRTree::CBinop* exp );
	Temp::CTemp munchExpBinop( const IRTree::CBinop* exp );
};

} // namespace CodeGeneration