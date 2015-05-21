#include "StackBuilder.h"

namespace RegisterAllocation {

	void CStackBuilder::simplify()
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices(vertices);
		for (auto vertex : vertices)
		{
			if ( varGraph.GetDegree(vertex) <= k ) {
				vertexStack.push(vertex);
				varGraph.DeleteVertex(vertex);
				break;
			}
		}
	}

	void CStackBuilder::spill() 
	{
	}

}