#include "FlowControlGraphBuilder.h"
#include "VarInterferenceGraphBuilder.h"
#include "DirectedGraph.hpp"
#include <stack>

namespace RegisterAllocation {

	class CStackBuilder {
	public:
		CStackBuilder(CVarInterferenceGraphBuilder::CGraph inputGraph) : sourceGraph(inputGraph), varGraph(inputGraph), k(8) {}
		void buildStack();
		std::unordered_map<Temp::CTemp, int> getColorMap() { return colors; }
	private:
		int k;
		std::stack<Temp::CTemp> vertexStack;
		//��������������� ����� ��������� �����, � ������� ���� ������
		RegisterAllocation::CVarInterferenceGraphBuilder::CGraph varGraph;
		//�������� ����
		RegisterAllocation::CVarInterferenceGraphBuilder::CGraph sourceGraph;
		std::unordered_set<Temp::CTemp> spilledVars;
		std::unordered_map<Temp::CTemp, int> colors;
		bool simplify();
		bool coalice();
		bool spill();
		bool select();
		bool freeze();
	};

}