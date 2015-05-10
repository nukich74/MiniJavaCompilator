// Автор: Азат Давлетшин
// Описание: Реализация построения графа взаимодействия переменных на основе ГПУ

#include <RegisterAllocation\VarInterferenceGraphBuilder.h>

namespace RegisterAllocation {

void CVarInterferenceGraphBuilder::BuildVarInterferenceGraph( const CDirectedGraph<CFlowControlVertex>& flowControlGraph )
{
	addVerticesToGraph( flowControlGraph );
}

void CVarInterferenceGraphBuilder::addVerticesToGraph( const CDirectedGraph<CFlowControlVertex>& flowControlGraph )
{
	for( int i = 0; i < flowControlGraph.GetVertices().size(); i++ ) {
		if( varInterferenceGraph.FindVertex(  )
	}
}

} // namespace RegisterAllocation