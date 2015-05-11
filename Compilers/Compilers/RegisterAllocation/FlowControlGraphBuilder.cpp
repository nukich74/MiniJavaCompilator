// Автор: Азат Давлетшин
// Описание: Реализация алгоритма построения графа потока управления

#include <RegisterAllocation\FlowControlGraphBuilder.h>
#include <algorithm>

namespace RegisterAllocation {

void CFlowControlGraphBuilder::BuildFlowControlGraph( const vector<unique_ptr<IInstruction> >& instructionsList )
{
	// Создаем вершины графа
	addInstructionsToGraph( instructionsList );

	// Упорядочиваем вершины в порядке DFS для оптимизации
	vector<CFlowControlVertex*> orderedVertices;
	flowControlGraph.SortVertices( orderedVertices, VO_DFS );

	bool hasAnyChanges = false;

	do {
		hasAnyChanges = false;

		for( auto& vertex : orderedVertices ) {
			bool hasChangesInVertex = updateLiveSetsInVertex( vertex );

			if( hasChangesInVertex ) {
				hasAnyChanges = true;
			}
		}
	} while( hasAnyChanges );
}

void CFlowControlGraphBuilder::addInstructionsToGraph( const vector<unique_ptr<IInstruction> >& instructionsList )
{
	for( const auto& instrutcion : instructionsList ) {
		flowControlGraph.AttachVertex( new CFlowControlVertex( instrutcion.get() ) );
	}
}

bool CFlowControlGraphBuilder::updateLiveSetsInVertex( CFlowControlVertex* vertex )
{
	bool hasChangesInVertex = false;
	
	// in[n] <- use[n] U ( out[n] - def[n] )
	CFlowControlVertex::SetOfVars liveIn;
	liveIn.insert( vertex->Uses.begin(), vertex->Uses.end() );
	
	for( const auto& var : vertex->LiveOut ) {
		// Проверям, что переменная отсутствует в Defs
		if( vertex->Defs.find( var ) == vertex->Defs.end() ) {
			liveIn.insert( var );
		}
	}

	// out[n] <- U_{s in succ[n]} in[s]
	CFlowControlVertex::SetOfVars liveOut;
	auto successors = flowControlGraph.GetEdgesFromVertex( vertex );
	for( const auto& successor : successors ) {
		liveOut.insert( successor->LiveIn.begin(), successor->LiveIn.end() );
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

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CFlowControlVertex::CFlowControlVertex( const CodeGeneration::IInstruction* instruction ) :
	Instruction( instruction )
{
	for( const auto& var : instruction->DefinedVars() ) {
		Defs.insert( &var );
	}

	for( const auto& var : instruction->UsedVars() ) {
		Uses.insert( &var );
	}

	IsMoveInstruction = dynamic_cast<const CodeGeneration::CMove*>( instruction ) != 0;
}

bool CFlowControlVertex::operator == ( const CFlowControlVertex& other ) const
{
	return Instruction == other.Instruction;
}

} // namespace RegisterAllocation