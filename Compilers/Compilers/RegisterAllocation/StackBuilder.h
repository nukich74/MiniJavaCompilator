#include "FlowControlGraphBuilder.h"
#include "VarInterferenceGraphBuilder.h"
#include "DirectedGraph.hpp"
#include <stack>
#include "CodeGeneration\InstructionsMuncher.h"

namespace RegisterAllocation {

	class CStackBuilder {
	public:
		CStackBuilder() : colored(false), k(6) {}
		void BuildStack( CodeGeneration::CInstructionsMuncher& instructionMuncher );
		std::unordered_map<Temp::CTemp, std::string> GetRegisterMap() { return registers; }
	private:
		int k;
		std::stack<Temp::CTemp> vertexStack;
		//вспомогательная копия исходного графа, с которой идет работа
		RegisterAllocation::CVarInterferenceGraphBuilder::CGraph varGraph;
		//исходный граф
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
		void preparation();
	};

}