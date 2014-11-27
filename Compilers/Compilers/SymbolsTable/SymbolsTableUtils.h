// �����: ������ �������.

// ��������: ����� ��������������� ������ ��� ���������� ������� ��������.

#pragma once

#include <vector>

namespace SymbolsTable {
	// ��������� ���� �� � ������� ���������, ��������� �������� ������ ���.
	template <class T>
	bool HasSuchNameInScope( std::vector<T> descriptors, std::string name )
	{
		for( auto& descriptor : descriptors ) {
			if( descriptor.Name == name ) {
				return true;
			}
		}
		return false;
	}
}