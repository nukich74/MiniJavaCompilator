#include "FlowControlGraphBuilder.h"
#include "VarInterferenceGraphBuilder.h"
#include "DirectedGraph.hpp"
#include <stack>

namespace RegisterAllocation {

	class CStackBuilder {
	public:
		CStackBuilder(CVarInterferenceGraphBuilder::CGraph inputGraph) : colored(false), sourceGraph(inputGraph), varGraph(inputGraph), k(6) {}
		void buildStack();
		std::unordered_map<Temp::CTemp, std::string> getRegisterMap() { assert(colored); return registers; }
	private:
		int k;
		std::stack<Temp::CTemp> vertexStack;
		//��������������� ����� ��������� �����, � ������� ���� ������
		RegisterAllocation::CVarInterferenceGraphBuilder::CGraph varGraph;
		//�������� ����
		RegisterAllocation::CVarInterferenceGraphBuilder::CGraph sourceGraph;
		std::unordered_set<Temp::CTemp> spilledVars;
		std::unordered_map<Temp::CTemp, int> colors;
		std::unordered_map<Temp::CTemp, std::string> registers;
		bool colored;
		bool simplify();
		bool coalice();
		bool spill();
		bool select();
		bool freeze();
	};

}