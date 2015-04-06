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

namespace CodeGeneration {

class CInstructionsMuncher {
public:
	// Передаем упорядоченный список IStm-ов как аргумент механизма
	CInstructionsMuncher( const std::vector< std::shared_ptr<const IRTree::IStm> >& _reorderedStmList ) :
		reorderedStmList( _reorderedStmList ) {}

	// Построить спискок ассемблерных инструкций
	void Process();

	// Результат работы механизма
	const std::vector<IInstruction>& GetInstructionsList() const
		{ return instructionsList; }

private:
	const std::vector< std::shared_ptr<const IRTree::IStm> >& reorderedStmList;
	std::vector<IInstruction> instructionsList;

	// методы, обрабатывающие различные случаи
	void munchMove( const IRTree::CMem* dst, const IRTree::IExp* src );
	// ....
};

}