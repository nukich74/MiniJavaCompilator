#include "StackBuilder.h"

namespace RegisterAllocation {
	
	void CStackBuilder::buildStack() 
	{
		do {
			bool isSimplified = simplify();
			bool isCoaliced = coalice();
			if ( !isSimplified && !isCoaliced ) {
				bool isFrosen = freeze();
				if ( !isFrosen ) {
					bool isSpilled = spill();
				}
			}
			vector<Temp::CTemp> vect;
			varGraph.GetVertices( vect );
			if ( vect.empty() ) break;
		} while ( true );
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