#pragma once

#include <string>

namespace Temp
{
// ����� - ����� �������� � ����
class CLabel {
public:
	// ������� ����� � ���������� ������
	CLabel();
	// ������� ����� � �������� ������
	explicit CLabel( const std::string& name );

	const std::string& Name() const { return name; }

private:
	// ������� ��� �������� ���������� ���������������
	static int nextUniqueId;
	std::string name;
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ��������� ����������
class CTemp {
public:
	// ����� ���������� � ���������� ������
	CTemp();
	// ����� ���������� � �������� ������
	explicit CTemp( const std::string& name );

	const std::string& Name() const { return name; }

private:
	// ������� ��� �������� ���������� ���
	static int nextUniqueId;
	std::string name;
};
}