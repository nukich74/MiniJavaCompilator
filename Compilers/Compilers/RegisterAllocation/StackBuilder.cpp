#include "StackBuilder.h"
#include <string>

namespace RegisterAllocation {
	
	void CStackBuilder::buildStack() 
	{
			//построение стэка для вершин
			do {
				bool isSimplified = simplify();
				while (isSimplified) isSimplified = simplify();
				bool isCoaliced = coalice();
				if (isCoaliced) continue;
				bool isFrosen = freeze();
				if (isFrosen) continue;
				bool isSpilled = spill();
				if (!isSpilled) break;
			} while ( true );
			//раскраска
			vector<Temp::CTemp> vertices;
			sourceGraph.GetVertices( vertices );
			int currColor = 1;
			for ( auto vert : vertices ) {
				if ( vert.Name()[0] == 'E' ) {
					colors[vert] = currColor;
					++currColor;
				}
			}
			while ( !vertexStack.empty() ) {
				Temp::CTemp currVertex = vertexStack.top();
				vertexStack.pop();
				size_t isUnion = currVertex.Name().find("&");
				vector<Temp::CTemp> vertices;
				sourceGraph.GetVertices( vertices );
				std::unordered_set<int> neighborColors;
				if (isUnion == std::string::npos) {
					for (auto vert : vertices) {
						if ( sourceGraph.GetEdge( currVertex, vert ) == RegisterAllocation::CVarInterferenceGraphBuilder::ET_Interfere ) {
							neighborColors.insert( colors[vert] );
						}
					}
					int assignColor = 0;
					for (int i = 1; i <= k; ++i) {
						if ( neighborColors.find(i) == neighborColors.end() ) {
							assignColor = i;
							break;
						}
					}
					if ( assignColor != 0 ) {
						colors[currVertex] = assignColor;
					} else {
						spilledVars.insert( currVertex );
					}
				} else {
					Temp::CTemp  firstVar = Temp::CTemp( currVertex.Name().substr( 0, isUnion ) );
					Temp::CTemp  secondVar = Temp::CTemp( currVertex.Name().substr( isUnion + 1, currVertex.Name().size() - isUnion - 1  ) );
					for (auto vert : vertices) {
						if ( sourceGraph.GetEdge( firstVar, vert ) == RegisterAllocation::CVarInterferenceGraphBuilder::ET_Interfere ||
							sourceGraph.GetEdge( secondVar, vert ) == RegisterAllocation::CVarInterferenceGraphBuilder::ET_Interfere) {
							neighborColors.insert( colors[vert] );
						}
					}
					int assignColor = 0;
					for (int i = 1; i <= k; ++i) {
						if ( neighborColors.find(i) == neighborColors.end() ) {
							assignColor = i;
							break;
						}
					}
					if ( assignColor != 0 ) {
						colors[firstVar] = assignColor;
						colors[secondVar] = assignColor;
					}
				}
			}
			//соответствие цветов и регистров
			std::unordered_map<int, Temp::CTemp> colors2Registers;
			for ( auto iter = colors.begin(); iter != colors.end(); ++iter ) {
				if ( iter->first.Name()[0] == 'E' ) {
					colors2Registers[iter->second] = iter->first;
				}
			}
			for ( auto iter = colors.begin(); iter != colors.end(); ++iter ) {
				registers[iter->first] = colors2Registers[iter->second];
			}
		}

	bool CStackBuilder::simplify()
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices( vertices );
		for ( auto from : vertices ) {
			if ( from.Name()[0] == 'E' ) continue;
			if ( varGraph.GetDegree(from) <= k ) {
				bool moveMarked = false;
				for (auto to : vertices) {
					if ( varGraph.GetEdge( from, to ) == CVarInterferenceGraphBuilder::ET_Move ) {
						moveMarked = true;
						break;
					}
				}
				if ( !moveMarked ) {
					vertexStack.push(from);
					varGraph.DeleteVertex(from);
					return true;
				}
			}
		}
		return false;
	}

	bool CStackBuilder::freeze()
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices( vertices );
		for (auto from : vertices) {
			bool moveVertex = false;
			int degree = varGraph.GetDegree( from ); 
			for (auto to : vertices) {
				if ( varGraph.GetEdge( from, to ) == CVarInterferenceGraphBuilder::ET_Move ) {
					moveVertex = true;
					break;
				}
			}
			if ( moveVertex && degree < k ) {
				varGraph.FreezeVertex(from);
				return true;
			}
		}
		return false;
	}

	bool CStackBuilder::coalice()
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices( vertices );
		for ( auto firstVar : vertices )  {
			for ( auto secondVar : vertices ) {
				if ( varGraph.GetEdge( firstVar, secondVar ) == CVarInterferenceGraphBuilder::ET_Move 
						&& varGraph.CanCoalice( firstVar, secondVar, k ) ) {
					varGraph.MergeVertices( firstVar, secondVar );
					return true;
				}
			}
		}
		return false;
	}

	bool CStackBuilder::spill() 
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices(vertices);
		for ( auto vert : vertices ) {
			if ( vert.Name()[0] != 'E' ) {
				varGraph.DeleteVertex( vert );
				vertexStack.push( vert );
				return true;
			}
		}
		return false;
	}

}