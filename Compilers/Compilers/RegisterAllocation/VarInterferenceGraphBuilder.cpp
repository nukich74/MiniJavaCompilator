// Автор: Азат Давлетшин
// Описание: Реализация построения графа взаимодействия переменных на основе ГПУ

#include <RegisterAllocation\VarInterferenceGraphBuilder.h>

namespace RegisterAllocation {

void CVarInterferenceGraphBuilder::BuildVarInterferenceGraph( const CDirectedGraph<CFlowControlVertex>& flowControlGraph )
{
	addVerticesFromFlowControlGraph( flowControlGraph );

	for( const auto& vertex : flowControlGraph.GetVertices() ) {
		if( vertex->IsMoveInstruction ) {
			// Для MOVE инструкции a <- c для всех b1, ..., bn из live-out, не равных c, добавляем пары (a, b1), ..., (a, bn)
			assert( vertex->Defs.size() == 1 );
			assert( vertex->Uses.size() == 1 );
			const Temp::CTemp* dstPtr = *vertex->Defs.begin();
			const Temp::CTemp* srcPtr = *vertex->Uses.begin();
			for( const Temp::CTemp* varPtr : vertex->LiveOut ) {
				if( varPtr != srcPtr ) {
					varInterferenceGraph.AddBothEdges( &dstPtr, &varPtr );
				}
			}
		} else {
			// В любой не-MOVE инструкции, которая определяет некоторую переменную a, для всех переменных b1, ..., bn
			// из live-out добавляем пары взаимодействия (a, b1), ..., (a, bn)
			if( vertex->Defs.size() > 0 ) {
				assert( vertex->Defs.size() == 1 );
				const Temp::CTemp* defPtr = *vertex->Defs.begin();
				for( const Temp::CTemp* varPtr : vertex->LiveOut ) {
					varInterferenceGraph.AddBothEdges( &defPtr, &varPtr );
				}
			}
		}
	}
}

void CVarInterferenceGraphBuilder::addVerticesFromFlowControlGraph( const CDirectedGraph<CFlowControlVertex>& flowControlGraph )
{
	// Каждая переменная должна быть где-то определена, поэтому добавляем Defs от каждой инструкции
	for( const auto& vertex : flowControlGraph.GetVertices() ) {
		for( const auto& varPtr : vertex->Defs ) {
			if( varInterferenceGraph.FindVertex( varPtr ) == 0 ) {
				varInterferenceGraph.AddVertex( varPtr );
			}
		}
	}
}

} // namespace RegisterAllocation