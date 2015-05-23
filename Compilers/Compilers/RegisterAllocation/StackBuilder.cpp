#include "StackBuilder.h"
#include <string>

namespace RegisterAllocation {
	
	void CStackBuilder::buildStack() 
	{
			//���������� ����� ��� ������
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
			//���������
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
		}

	bool CStackBuilder::simplify()
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices( vertices );
		for ( auto from : vertices ) {
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
		if (!vertices.empty()) {
			varGraph.DeleteVertex(vertices[0]);
			return true;
			vertexStack.push(vertices[0]);
		}
		return false;
	}

}