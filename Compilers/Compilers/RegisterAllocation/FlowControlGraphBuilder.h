// Автор: Азат Давлетшин
// Описание: Построение графа потока управления

#pragma once

#include <vector>
#include <unordered_set>
#include <RegisterAllocation\DirectedGraph.hpp>
#include <Temp.h>
#include <CodeGeneration\Instruction.h>
#include <memory>

namespace RegisterAllocation {

using std::vector;
using std::unordered_set;
using std::unique_ptr;
using CodeGeneration::IInstruction;

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Вспомогательные классы

// Вершина графа потока управления. Не владеет памятью
struct CFlowControlVertex {
	typedef unordered_set<const Temp::CTemp*> SetOfVars;
	// Множество переменных, определяемых в данной вершине
	SetOfVars Defs;
	// Множество используемых в данной вершине переменных
	SetOfVars Uses;

	// Переменная называется «живой» в данном ребре, если существует прямой путь из него в вершину, в которой она
	// используется, который не проходит ни через одну вершину, в которой эта переменная определяется.

	// Множество переменных, которые живы на каком-либо из входящих ребер узла
	SetOfVars LiveIn;
	// Множество переменных, которые живы на каком-лиюо выходящем ребре
	SetOfVars LiveOut;
	
	// Является ли инструкция, соответствующая данной вершине, инструкцией Move
	bool IsMoveInstruction;

	// Инструкция, которой соответствует вершина
	const CodeGeneration::IInstruction* const Instruction;

	explicit CFlowControlVertex( const CodeGeneration::IInstruction* instruction );

	// Вершины равны, если указатели на соответствующие инструкции равны
	bool operator == ( const CFlowControlVertex& other ) const;
};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Класс-механизм, строящий граф потока управления по списку ассемблерных инструкций

class CFlowControlGraphBuilder {
public:

	// Собственно построить граф потока управления
	void BuildFlowControlGraph( const vector<unique_ptr<IInstruction> >& instructionsList );

	// Получить результат работы алгоритма (построенный граф)
	const CDirectedGraph<CFlowControlVertex>& GetFlowControlGraph() const
		{ return flowControlGraph; }
private:
	// Граф потока управления (результат работы алгоритма)
	CDirectedGraph<CFlowControlVertex> flowControlGraph;

	// Добавляет все вершины из списка инструкций в граф. Создает Defs и Uses для каждой вершины
	void addInstructionsToGraph( const vector<unique_ptr<IInstruction> >& instructionsList );
	// Обновляет множества LiveIn и LiveOut вершины. Если есть изменения, возвращает true
	bool updateLiveSetsInVertex( CFlowControlVertex* vertex );
};

} // namespace RegisterAllocation