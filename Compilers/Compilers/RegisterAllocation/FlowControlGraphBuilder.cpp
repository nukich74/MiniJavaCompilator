// Автор: Азат Давлетшин
// Описание: Реализация алгоритма построения графа потока управления

#include <RegisterAllocation\FlowControlGraphBuilder.h>
#include <unordered_map>
#include <string>
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
	std::unordered_map<Temp::CLabel, CFlowControlVertex*> labels;
	vector<CFlowControlVertex*> notLabels;

	CFlowControlVertex* prevVertex = 0;
	for( const auto& instruction : instructionsList ) {
		auto vertex = new CFlowControlVertex( instruction.get() );
		flowControlGraph.AttachVertex( vertex );

		if( prevVertex != 0 ) {
			flowControlGraph.AddEdge( prevVertex, vertex );
		}
		prevVertex = vertex;

		const CodeGeneration::CLabel* instrAsLabel = dynamic_cast<const CodeGeneration::CLabel*>( vertex->Instruction );
		if( instrAsLabel != 0 ) {
			assert( instrAsLabel->JumpTargets().size( ) == 1 );
			labels.insert( std::make_pair( *instrAsLabel->JumpTargets().begin(), vertex ) );
		} else {
			notLabels.push_back( vertex );
		}
	}

	for( auto& vertex : notLabels ) {
		for( const Temp::CLabel& label : vertex->Instruction->JumpTargets() ) {
			auto it = labels.find( label );
			if( it != labels.end() ) {
				if( !flowControlGraph.HasEdge( vertex, it->second ) ) {
					flowControlGraph.AddEdge( vertex, it->second );
				}
			}
		}
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
	Defs.insert( instruction->DefinedVars().begin(), instruction->DefinedVars().end() );
	Uses.insert( instruction->UsedVars().begin(), instruction->UsedVars().end() );

	IsMoveInstruction = dynamic_cast<const CodeGeneration::CMove*>( instruction ) != 0;
}

bool CFlowControlVertex::operator == ( const CFlowControlVertex& other ) const
{
	return Instruction == other.Instruction;
}

} // namespace RegisterAllocation