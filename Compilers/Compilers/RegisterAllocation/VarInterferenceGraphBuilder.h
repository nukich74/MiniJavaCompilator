// Автор: Азат Давлетшин
// Описание: Построение графа взаимодействия переменных на основе ГПУ

#pragma once

#include <RegisterAllocation\FlowControlGraphBuilder.h>
#include <Temp.h>

namespace RegisterAllocation {

// Класс-механизм для построения графа взаимодействия переменных (ГВП). ГВП - граф, вершины которого - 
// указатели на переменные, а ребро означает наличие взаимодействия
class CVarInterferenceGraphBuilder {
public:
	// Собственно построить граф взаимодействия переменных по графу потока управления
	void BuildVarInterferenceGraph( const vector<CFlowControlVertex*>& flowControlVertices );
	// Получить ГВП (результат работы алгоритма)
	const CDirectedGraph<Temp::CTemp>& GetVarInterferenceGraph()
		{ return varInterferenceGraph; }

private:
	CDirectedGraph<Temp::CTemp> varInterferenceGraph;
};

} // namespace RegisterAllocation
