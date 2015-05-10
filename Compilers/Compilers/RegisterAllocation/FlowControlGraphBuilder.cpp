// Автор: Азат Давлетшин
// Описание: Реализация алгоритма построения графа потока управления

#include <RegisterAllocation\FlowControlGraphBuilder.h>
#include <algorithm>

namespace RegisterAllocation {

void CFlowControlGraphBuilder::BuildFlowControlGraph( const vector<unique_ptr<IInstruction> >& instructionsList )
{
	// Создаем вершины графа
	addInstructionsToGraph( instructionsList );

	bool hasAnyChanges = false;

	do {
		hasAnyChanges = false;
		auto vertices = flowControlGraph.GetVertices();

		for( int i = 0; i < vertices.size(); i++ ) {
			bool hasChangesInVertex = updateLiveSetsInVertex( vertices[i].get() );

			if( hasChangesInVertex ) {
				hasAnyChanges = true;
			}
		}
	} while( hasAnyChanges );
}

void CFlowControlGraphBuilder::addInstructionsToGraph( const vector<unique_ptr<IInstruction> >& instructionsList )
{
	for( int i = 0; i < instructionsList.size(); i++ ) {
		CFlowControlVertex::SetOfVars defs, uses;
		for( auto it = instructionsList[i]->DefinedVars().begin(); it != instructionsList[i]->DefinedVars().end(); it++ ) {
			defs.insert( &*it );
		}

		for( auto it = instructionsList[i]->UsedVars( ).begin( ); it != instructionsList[i]->UsedVars( ).end( ); it++ ) {
			uses.insert( &*it );
		}

		flowControlGraph.AddVertex( new CFlowControlVertex( std::move( defs ), std::move( uses ) ) );
	}
}

bool CFlowControlGraphBuilder::updateLiveSetsInVertex( CFlowControlVertex* vertex )
{
	bool hasChangesInVertex = false;
	
	// in[n] <- use[n] U ( out[n] - def[n] )
	CFlowControlVertex::SetOfVars liveIn;
	liveIn.insert( vertex->Uses.begin(), vertex->Uses.end() );
	
	for( auto it = vertex->LiveOut.begin(); it != vertex->LiveOut.end(); it++ ) {
		// Проверям, что переменная отсутствует в Defs
		if( vertex->Defs.find( *it ) == vertex->Defs.end() ) {
			liveIn.insert( *it );
		}
	}

	// out[n] <- U_{s in succ[n]} in[s]
	CFlowControlVertex::SetOfVars liveOut;
	auto successors = flowControlGraph.GetEdgesFromVertex( vertex );
	for( auto it = successors.begin(); it != successors.end(); it++ ) {
		liveOut.insert( (*it)->LiveIn.begin(), (*it)->LiveIn.end() );
	}

	// Проверяем изменения
	if( liveIn != vertex->LiveIn ) {
		vertex->LiveIn.swap( liveIn );
		hasChangesInVertex = true;
	}

	if( liveOut != vertex->LiveOut ) {
		vertex->LiveOut.swap( liveOut );
		hasChangesInVertex = true;
	}

	return hasChangesInVertex;
}

} // namespace RegisterAllocation