// �����: ������ �������.

// ��������: ����� ��������������� ������ ��� ���������� ������� ��������.

#pragma once

#include <vector>

namespace SymbolsTable {
	// ��������� ���� �� � ������� ���������, ��������� �������� ������ ���.
	template <class T>
	bool HasSuchNameInScope( std::vector<T> descriptors, std::string name )
	{
		for( int i = 0; i < descriptors.size(); ++i ) {
			if( descriptors[i].name == name ) {
				return true;
			}
		}
		return false;
	}
}