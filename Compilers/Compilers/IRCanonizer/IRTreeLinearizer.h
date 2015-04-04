// �����: ��������� ���������
// ��������: ����� ����������� ����� ������, � ��������������� ��� � �������� ���������

#pragma once

#include <IRTreeVisitor.h>
#include <vector>
#include <IRStm.h>

namespace IRTree {

class CLinearizer {
public:
	void Linearize( std::shared_ptr<const IStm> root );

private:

	std::vector< std::shared_ptr<const IStm> > linearized;

};

} // namespace IRTree