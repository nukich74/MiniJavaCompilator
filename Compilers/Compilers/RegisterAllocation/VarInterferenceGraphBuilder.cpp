// Автор: Азат Давлетшин
// Описание: Реализация построения графа взаимодействия переменных на основе ГПУ

#include <RegisterAllocation\VarInterferenceGraphBuilder.h>

namespace RegisterAllocation {

void CVarInterferenceGraphBuilder::BuildVarInterferenceGraph( const vector<CFlowControlVertex*>& flowControlVertices )
{
	for( const auto& vertex : flowControlVertices ) {
		if( vertex->IsMoveInstruction ) {
			// Для MOVE инструкции a <- c для всех b1, ..., bn из live-out, не равных c, добавляем пары (a, b1), ..., (a, bn)
			assert( vertex->Defs.size() == 1 );
			assert( vertex->Uses.size() == 1 );
			const Temp::CTemp& dst = *vertex->Defs.begin();
			const Temp::CTemp& src = *vertex->Uses.begin();
			for( const Temp::CTemp& var : vertex->LiveOut ) {
				if( var != src ) {
					varInterferenceGraph.AddBothEdges( dst, var );
				}
			}
		} else {
			// В любой не-MOVE инструкции, которая определяет некоторую переменную a, для всех переменных b1, ..., bn
			// из live-out добавляем пары взаимодействия (a, b1), ..., (a, bn)
			if( vertex->Defs.size() > 0 ) {
				assert( vertex->Defs.size() == 1 );
				const Temp::CTemp& def = *vertex->Defs.begin();
				for( const Temp::CTemp& var : vertex->LiveOut ) {
					assert( !varInterferenceGraph.HasEdge( def, var ) );
					varInterferenceGraph.AddBothEdges( def, var );
				}
			}
		}
	}
}

} // namespace RegisterAllocation