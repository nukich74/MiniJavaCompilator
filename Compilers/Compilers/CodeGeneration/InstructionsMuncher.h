// �����: ���� ���������
// ��������: �����-��������, ������� �� �������������� ������ Stm-�� �������� ������ ������� ��������� � ����
// ������ IInstruction

#pragma once

#include <CodeGeneration\Instruction.h>
#include <vector>
#include <memory>
#include <IRTree.h>
#include <IRExp.h>
#include <IRStm.h>

namespace CodeGeneration {

class CInstructionsMuncher {
public:
	// �������� ������������� ������ IStm-�� ��� �������� ���������
	CInstructionsMuncher( const std::vector< std::shared_ptr<const IRTree::IStm> >& _reorderedStmList ) :
		reorderedStmList( _reorderedStmList ) {}

	// ��������� ������� ������������ ����������
	void Process();

	// ��������� ������ ���������
	const std::vector<IInstruction>& GetInstructionsList() const
		{ return instructionsList; }

private:
	const std::vector< std::shared_ptr<const IRTree::IStm> >& reorderedStmList;
	std::vector<IInstruction> instructionsList;

	// ������, �������������� ��������� ������
	void munchMove( const IRTree::CMem* dst, const IRTree::IExp* src );
	// ....
};

}