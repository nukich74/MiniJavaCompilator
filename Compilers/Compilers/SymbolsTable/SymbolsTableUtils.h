// �����: ������ �������.

// ��������: ����� ��������������� ������ ��� ���������� ������� ��������.

#pragma once

#include <vector>

namespace SymbolsTable {
	// ��������� ���� �� � ������� ���������, ��������� �������� ������ ���.
	template <class T>
	bool HasSuchNameInScope( std::vector<T> descriptors, std::string name )
	{
		for( auto ptr = descriptors.begin() ; ptr != descriptors.end(); ++ptr ) {
			if( ptr->Name == name ) {
				return true;
			}
		}
		return false;
	}
}