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
	std::vector< std::shared_ptr<const IStm> > GetReordered();

	
private:
	
	// ��������� �� ��� ����� � ������� ������ ��������
	const Frame::CFrame* frame;	
	std::vector< std::shared_ptr<const IStm> > linearized;
	std::list< std::vector< std::shared_ptr<const IStm> > > independentBlocks;

	void CLinearizer::linearize( std::shared_ptr<const IStm> root );
	void splitByLabelAndJump();
	// �������������� IndependentBlocks ����� ������� ����� ����� ������� CJump ��� ��� false �����
	void reorder();
	
};

} // namespace IRTree