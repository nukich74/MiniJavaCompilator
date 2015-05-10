﻿// Автор: Азат Давлетшин
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

	CFlowControlVertex( SetOfVars&& defs, SetOfVars&& uses, SetOfVars&& liveIn, SetOfVars&& liveOut ) :
		Defs( defs ), Uses( uses ), LiveIn( liveIn ), LiveOut( liveOut )
	{}

	CFlowControlVertex( SetOfVars&& defs, SetOfVars&& uses ) :
		Defs( defs ), Uses( uses )
	{}
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