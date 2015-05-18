// Автор: Азат Давлетшин
// Описание: Реализация построения графа взаимодействия переменных на основе ГПУ

#include <RegisterAllocation\VarInterferenceGraphBuilder.h>
#include <unordered_set>

namespace RegisterAllocation {

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Реализация графа

void CVarInterferenceGraphBuilder::CGraph::AddVertices( const vector<Temp::CTemp>& vertices )
{
	for( const auto& firstVertex : vertices ) {
		for( const auto& secondVertex : vertices ) {
			edges[firstVertex][secondVertex] = ET_None;
		}
	}
}

CVarInterferenceGraphBuilder::TEdgeType CVarInterferenceGraphBuilder::CGraph::GetEdge( const Temp::CTemp& firstVar, const Temp::CTemp& secondVar ) const
{
	auto edgesFromFirstVarIt = edges.find( firstVar );
	assert( edgesFromFirstVarIt != edges.end() );

	auto edgeIt = edgesFromFirstVarIt->second.find( secondVar );
	assert( edgeIt != edgesFromFirstVarIt->second.end() );
	return edgeIt->second;
}

void CVarInterferenceGraphBuilder::CGraph::SetEdge( const Temp::CTemp& firstVar, const Temp::CTemp& secondVar, TEdgeType edgeType )
{
	auto edgesFromFirstVarIt = edges.find( firstVar );
	assert( edgesFromFirstVarIt != edges.end( ) );

	auto edgeIt = edgesFromFirstVarIt->second.find( secondVar );
	assert( edgeIt != edgesFromFirstVarIt->second.end( ) );
	edgeIt->second = edgeType;

	edgesFromFirstVarIt = edges.find( secondVar );
	assert( edgesFromFirstVarIt != edges.end( ) );

	edgeIt = edgesFromFirstVarIt->second.find( firstVar );
	assert( edgeIt != edgesFromFirstVarIt->second.end( ) );
	edgeIt->second = edgeType;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// CVarInterferenceGraphBuilder

void CVarInterferenceGraphBuilder::BuildVarInterferenceGraph( const vector<CFlowControlVertex*>& flowControlVertices )
{
	addVerticesToGraph( flowControlVertices );

	for( const auto& vertex : flowControlVertices ) {
		if( vertex->IsMoveInstruction ) {
			// Для MOVE инструкции a <- c для всех b1, ..., bn из live-out, не равных c, добавляем пары (a, b1), ..., (a, bn)
			assert( vertex->Defs.size() == 1 );
			assert( vertex->Uses.size() == 1 );

			const Temp::CTemp& def = *vertex->Defs.begin();
			for( const Temp::CTemp& var : vertex->LiveOut ) {
				if( var == def ) {
					// Нет смысла добавлять взаимодействие переменной с собой
					continue;
				}
				if( var != *vertex->Uses.begin() ) {
					if( varInterferenceGraph.GetEdge( def, var ) != ET_None ) {
						// Ребро уже есть
						continue;
					}
					varInterferenceGraph.SetEdge( def, var, ET_Move );
				}
			}
		} else {
			// В любой не-MOVE инструкции, которая определяет некоторую переменную a, для всех переменных b1, ..., bn
			// из live-out добавляем пары взаимодействия (a, b1), ..., (a, bn)
			if( vertex->Defs.size() > 0 ) {
				assert( vertex->Defs.size() == 1 );
				const Temp::CTemp& def = *vertex->Defs.begin();
				for( const Temp::CTemp& var : vertex->LiveOut ) {
					if( var == def ) {
						// Нет смысла добавлять взаимодействие переменной с собой
						continue;
					}
					if( varInterferenceGraph.GetEdge( def, var ) != ET_Interfere ) {
						// Ребро уже есть
						continue;
					}
					varInterferenceGraph.SetEdge( def, var, ET_Interfere );
				}
			}
		}
	}
}

void CVarInterferenceGraphBuilder::addVerticesToGraph( const vector<CFlowControlVertex*>& flowControlVertices )
{
	std::unordered_set<Temp::CTemp> varsSet;
	for( const auto& flowControlVertex : flowControlVertices ) {
		varsSet.insert( flowControlVertex->Defs.begin(), flowControlVertex->Defs.end() );
		varsSet.insert( flowControlVertex->Uses.begin(), flowControlVertex->Uses.end() );
	}

	vector<Temp::CTemp> vars;
	for( const auto& var : varsSet ) {
		vars.push_back( var );
	}

	varInterferenceGraph.AddVertices( vars );
}

} // namespace RegisterAllocation