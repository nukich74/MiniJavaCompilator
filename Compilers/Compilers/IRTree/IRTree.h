// �����: ���� ���������
// ��������: ��������� ��� ������ �������������� �������������
#pragma once

namespace IRTree
{

// ��������� ��� �����, ������������ ��������
class IIRExp {
public:
	virtual ~IIRExp() {}
};

// ��������� ��� ����������� �����������
class IIRStm {
public:
	virtual ~IIRStm() {}
};

}