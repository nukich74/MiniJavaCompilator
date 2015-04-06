// �����: ��������� ���������
// ��������: ����� ����������� ����� ������, � ��������������� ��� � �������� ���������

#pragma once

#include <IRTreeVisitor.h>
#include <vector>
#include <list>
#include <IRStm.h>
#include "Frame.h"

namespace IRTree {

class CLinearizer {
public:
	CLinearizer( const Frame::CFrame* _frame ) : frame( _frame ) {}

	void Linearize();
	void SplitByLabelAndJump();
	// �������������� IndependentBlocks ����� ������� ����� ����� ������� CJump ��� ��� false �����
	void Reorder();

	std::list< std::vector< std::shared_ptr<const IStm> > > IndependentBlocks;
private:
	
	// ��������� �� ��� ����� � ������� ������ ��������
	const Frame::CFrame* frame;	
	std::vector< std::shared_ptr<const IStm> > linearized;
	void CLinearizer::linearize( std::shared_ptr<const IStm> root );
	
};

} // namespace IRTree