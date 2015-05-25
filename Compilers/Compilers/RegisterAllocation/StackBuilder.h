#include "FlowControlGraphBuilder.h"
#include "VarInterferenceGraphBuilder.h"
#include "DirectedGraph.hpp"
#include <stack>

namespace RegisterAllocation {

	class CStackBuilder {
	public:
		CStackBuilder(CVarInterferenceGraphBuilder::CGraph inputGraph) : sourceGraph(inputGraph), varGraph(inputGraph), k(6) {}
		void buildStack();
		std::unordered_map<Temp::CTemp, Temp::CTemp> getRegisterMap() { return registers; }
	private:
		int k;
		std::stack<Temp::CTemp> vertexStack;
		//вспомогательная копия исходного графа, с которой идет работа
		RegisterAllocation::CVarInterferenceGraphBuilder::CGraph varGraph;
		//исходный граф
		RegisterAllocation::CVarInterferenceGraphBuilder::CGraph sourceGraph;
		std::unordered_set<Temp::CTemp> spilledVars;
		std::unordered_map<Temp::CTemp, int> colors;
		std::unordered_map<Temp::CTemp, Temp::CTemp> registers;
		bool simplify();
		bool coalice();
		bool spill();
		bool select();
		bool freeze();
	};

}