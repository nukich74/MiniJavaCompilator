#include "FlowControlGraphBuilder.h"
#include "VarInterferenceGraphBuilder.h"
#include "DirectedGraph.hpp"
#include <stack>

namespace RegisterAllocation {

	class CStackBuilder {
	public:
		CStackBuilder(CVarInterferenceGraphBuilder::CGraph inputGraph) : varGraph(inputGraph), k(8) {}
		void buildStack();

	private:
		int k;
		std::stack<Temp::CTemp> vertexStack;
		RegisterAllocation::CVarInterferenceGraphBuilder::CGraph varGraph;
		bool simplify();
		bool coalice();
		bool spill();
		bool select();
		bool freeze();
	};

}