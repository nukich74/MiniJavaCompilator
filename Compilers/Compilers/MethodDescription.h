// �����: ������� ������

// ��������: �����, ������������� ���������� � ������� ������ - ��� �����,
// ������������ ��������, ����� ����������, ��������� ����������.

#pragma once

#include "FieldDescription.h"
#include <string>
#include <vector>

class CMethodDescription {
public:
	// ��� ������.
	std::string Name;
	// ������������ ��������.
	CTypeIdentifier ReturnType;
	// ������� ��������� ������.
	std::vector<CFieldDescription> Params;
	// ��������� ���������� ������.
	std::vector<CFieldDescription> Locals;

	CMethodDescription( const std::string& _Name, const CTypeIdentifier& _ReturnType )
		: Name( _Name )
		, ReturnType( _ReturnType )
	{ }
};