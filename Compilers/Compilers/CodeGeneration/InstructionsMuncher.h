// Автор: Азат Давлетшин
// Описание: класс-механизм, который из упорядоченного списка Stm-ов получает список листинг программы в виде
// списка IInstruction

#pragma once

#include <CodeGeneration\Instruction.h>
#include <vector>
#include <memory>
#include <IRTree.h>
#include <IRExp.h>
#include <IRStm.h>
#include <Frame.h>
#include <unordered_set>

namespace CodeGeneration {

class CInstructionsMuncher {
public:
	// Передаем упорядоченный список IStm-ов как аргумент механизма
	CInstructionsMuncher( const std::vector< std::shared_ptr<const IRTree::IStm> >& _reorderedStmList, const Frame::CFrame* _frame ) :
		reorderedStmList( _reorderedStmList ), frame( _frame ) {}

	// Построить спискок ассемблерных инструкций
	void CodeGen();

	// Результат работы механизма
	const std::vector< std::unique_ptr<IInstruction> >& GetInstructionsList() const { return instructionsList; }

	const std::vector<std::string>& GetDebugInfo() const { return debugInfo; }
	// Оборачивает переменные перед использованием mov'ами
	void FetchStoreSpilledVars( const std::unordered_set<Temp::CTemp>& spilledVars );

private:
	const std::vector< std::shared_ptr<const IRTree::IStm> >& reorderedStmList;
	std::vector< std::unique_ptr<IInstruction> > instructionsList;
	std::vector<std::string> debugInfo;
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
	Temp::CTemp munchExpCall( const IRTree::CCall* exp );
	Temp::CTemp CInstructionsMuncher::munchExpBinopMul( const IRTree::CBinop* exp );
	Temp::CTemp CInstructionsMuncher::munchExpBinopLess( const IRTree::CBinop* exp );
	int munchArgs( const IRTree::CExpList exp );
};

} // namespace CodeGeneration