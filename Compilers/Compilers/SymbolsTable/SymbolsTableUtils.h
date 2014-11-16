// �����: ������ �������.

// ��������: ����� ��������������� ������ ��� ���������� ������� ��������.

#pragma once

#include <vector>

namespace SymbolsTable {
	// ��������� ���� �� � ������� ���������, ��������� �������� ������ ���.
	template <class T>
	bool HasSuchNameInScope( std::vector<T> descriptors, std::string name )
	{
		for( int i = 0; i < static_cast<int>( descriptors.size() ); ++i ) {
			if( descriptors[i].Name == name ) {
				return true;
			}
		}
		return false;
	}
}