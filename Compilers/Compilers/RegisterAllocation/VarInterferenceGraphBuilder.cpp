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
		degree[firstVertex] = 0;
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

void CVarInterferenceGraphBuilder::CGraph::DeleteVertex( const Temp::CTemp& vertex )
{
	assert( edges.find(vertex) != edges.end() );
	edges.erase( vertex );
	degree.erase( vertex );
	for ( auto from = edges.begin(); from != edges.end(); ++from )  {
		if ( from->second[vertex] == ET_Interfere ) --degree[from->first];
		from->second.erase( vertex );
	}
}

void CVarInterferenceGraphBuilder::CGraph::MergeVertices( const Temp::CTemp& firstVar, const Temp::CTemp& secondVar )
{
	assert( firstVar.Name() != secondVar.Name() );
	assert( edges.find( firstVar ) != edges.end() );
	assert( edges.find( secondVar ) != edges.end() );
	std::unordered_map<Temp::CTemp, TEdgeType> newVertexRow;
	//Переменная, представляющая объединение 2-х
	Temp::CTemp mergedTemp( firstVar.Name() + std::string("&") + secondVar.Name() );
	for ( auto iter = edges.begin(); iter != edges.end(); ++iter ) {
		newVertexRow[iter->first] = ET_None;
	}
	//Получаем информацию с какими вершинами соединены 2 входные
	for ( auto iter = edges.find( firstVar )->second.begin(); iter != edges.find( firstVar )->second.end(); ++iter ) {
		if (iter->first.Name() != secondVar.Name() ) newVertexRow[iter->first] = std::min( newVertexRow[iter->first], iter->second );
	}
	for ( auto iter = edges.find( secondVar )->second.begin(); iter != edges.find( secondVar )->second.end(); ++iter ) {
		if (iter->first.Name() != firstVar.Name() ) newVertexRow[iter->first] = std::min( newVertexRow[iter->first], iter->second );
	}
	//Обновляем значения в графе для старых вершин
	newVertexRow[mergedTemp] = ET_None;
	degree[mergedTemp] = 0;
	for (auto iter = edges.begin(); iter != edges.end(); ++iter) {
		iter->second[mergedTemp] = newVertexRow[iter->first];
		if (newVertexRow[iter->first] == ET_Interfere) {
			++degree[mergedTemp];
			++degree[iter->first];
		}
	}
	edges[mergedTemp] = newVertexRow;
	DeleteVertex(firstVar);
	DeleteVertex(secondVar);
}

void CVarInterferenceGraphBuilder::CGraph::GetVertices( vector<Temp::CTemp>& vertices)
{
	vertices.clear();
	for (auto iter = edges.begin(); iter != edges.end(); ++iter)  {
		vertices.push_back(iter->first);
	}
}

int CVarInterferenceGraphBuilder::CGraph::GetDegree( const Temp::CTemp& vertex )
{
	assert( edges.find(vertex) != edges.end() );
	return degree[vertex];
}

void CVarInterferenceGraphBuilder::CGraph::FreezeVertex( const Temp::CTemp& vertex )
{
	assert( edges.find(vertex) != edges.end() );
	for ( auto iter = edges.find(vertex)->second.begin(); iter != edges.find(vertex)->second.end(); ++iter ) {
		if ( iter->second == ET_Move ) {
			iter->second = ET_None;
		}
	}
}

bool CVarInterferenceGraphBuilder::CGraph::CanCoalice( const Temp::CTemp& firstVar, const Temp::CTemp& secondVar, int k )
{
	//Briggs coalice
	std::unordered_map<Temp::CTemp, TEdgeType> newVertexRow;
	for ( auto iter = edges.begin(); iter != edges.end(); ++iter ) {
		newVertexRow[iter->first] = ET_None;
	}
	//Получаем информацию с какими вершинами соединены 2 входные
	for ( auto iter = edges.find( firstVar )->second.begin(); iter != edges.find( firstVar )->second.end(); ++iter ) {
		newVertexRow[iter->first] = std::min( newVertexRow[iter->first], iter->second );
	}
	for ( auto iter = edges.find( secondVar )->second.begin(); iter != edges.find( secondVar )->second.end(); ++iter ) {
		newVertexRow[iter->first] = std::min( newVertexRow[iter->first], iter->second );
	}
	int	neighborsCount = 0;
	bool moveRelated = false;
	for ( auto iter = newVertexRow.begin(); iter != newVertexRow.end(); ++iter ) {
		if ( iter->second == ET_Interfere ) ++neighborsCount;
		if ( iter->second == ET_Move && iter->first.Name() != firstVar.Name() && 
				secondVar.Name() != iter->first.Name() ) {
			moveRelated = true;
			break;
		}
	}
	if ( neighborsCount <= k && !moveRelated ) {
		return true;
	}

	//George coalice
	bool georgeWorks = true;
	for ( auto iter = edges.find( firstVar )->second.begin(); iter != edges.find( firstVar )->second.end(); ++iter ) {
		if ( edges[iter->first][secondVar] != ET_Interfere || degree[iter->first] >= k ) {
			georgeWorks = false;
			break;
		}
	}
	if ( georgeWorks && !moveRelated ) {
		return true;
	}

	return false;
}

void CVarInterferenceGraphBuilder::CGraph::UpdateDegree()
{
	for ( auto from = edges.begin(); from != edges.end(); ++from )
	{
		degree[from->first] = 0;
		for ( auto to = from->second.begin(); to != from->second.end(); ++to )
		{
			if (to->second == ET_Interfere) ++degree[from->first];
		}
	}
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
			for( const auto& varFromDefs : vertex->Defs ) {
				for( const Temp::CTemp& var : vertex->LiveOut ) {
					if( var == varFromDefs ) {
						// Нет смысла добавлять взаимодействие переменной с собой
						continue;
					}
					if( varInterferenceGraph.GetEdge( varFromDefs, var ) == ET_Interfere ) {
						// Ребро уже есть
						continue;
					}
					varInterferenceGraph.SetEdge( varFromDefs, var, ET_Interfere );
				}
			}
		}
	}
	varInterferenceGraph.UpdateDegree();
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