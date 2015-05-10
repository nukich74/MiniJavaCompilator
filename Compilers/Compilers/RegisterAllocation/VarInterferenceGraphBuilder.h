// �����: ���� ���������
// ��������: ���������� ����� �������������� ���������� �� ������ ���

#pragma once

#include <RegisterAllocation\FlowControlGraphBuilder.h>
#include <Temp.h>

namespace RegisterAllocation {

// �����-�������� ��� ���������� ����� �������������� ���������� (���). ��� - ����, ������� �������� - 
// ����������, � ����� �������� ������� ��������������
class CVarInterferenceGraphBuilder {
public:
	// ���������� ��������� ���� �������������� ���������� �� ����� ������ ����������
	void BuildVarInterferenceGraph( const CDirectedGraph<CFlowControlVertex>& flowControlGraph );
	// �������� ��� (��������� ������ ���������)
	const CDirectedGraph<Temp::CTemp>& GetVarInterferenceGraph()
		{ return varInterferenceGraph; }

private:
	CDirectedGraph<Temp::CTemp> varInterferenceGraph;

	// ��������� ������� (����������) � ����
	void addVerticesToGraph( const CDirectedGraph<CFlowControlVertex>& flowControlGraph );
};

} // namespace RegisterAllocation
