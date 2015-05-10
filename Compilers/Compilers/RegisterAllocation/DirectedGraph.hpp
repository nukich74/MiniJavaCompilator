// �����: ���� ���������
// ��������: ���������� ������ ������������� �����. ����������� ��� ������� ������ ���������� � ����� ��������������

#pragma once

#include <vector>
#include <map>
#include <assert.h>
#include <algorithm>

using std::vector;
using std::map;
using std::find;

namespace RegisterAllocation {

// �������������� ����. ��� ��� ����� � ����� ������� �����������, �� ������������� ����������� ���� � ���� �������
// ���������. �� ������� �������. ��� ������� ������ ������ ���� ������, ���� �������� � ������.
template <typename T>
class CDirectedGraph {
public:
	// ��������� ������� ��� �������. ���� ������ ��� ���� � �����, �� �������� assert
	void AddVertex( T* objectPtr );
	// ��������� ��������������� �����. ���� �����-������ ������� ���, �� ��������� assert
	void AddEdge( T* fromVertex, T* toVertex );

	// ������ �������� �������������
	void DeleteVertex( T* objectPtr );
	void DeleteEdge( T* fromVertex, T* toVertex );

	// ���� �� ����� �����?
	bool HasEdge( T* fromVertex, T* toVertex ) const;
	// ���� �� ����� �������?
	bool HasVertex( T* objectPtr ) const;

	// ������ � ������, ��������� �� fromVertex. ���� ����� ������� ���, �� ��������� assert
	const vector<T*>& GetEdgesFromVertex( T* fromVertex ) const;
	// ������ � ������, �������� � toVertex. ���� ����� ������� ���, �� ��������� assert
	const vector<T*>& GetEdgesToVertex( T* toVertex ) const;
	// ������ � ��������
	const vector<T*>& GetVertices() const
		{ return vertices; }



private:
	// adjacencyListOut[i] - ������ ������, � ������� ������ �����, ��������� �� i-�� �������
	map<T*, vector<T*> > adjacencyListsOut;
	// adjacencyListsIn[i] - ������ ������, �� ������� ������� �����, �������� � i-� �������
	map<T*, vector<T*> > adjacencyListsIn;
	// ������ ���� ������
	vector<T*> vertices;

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// ���������� ������� ���������� ������ CDirectedGraph

template <typename T>
void CDirectedGraph<T>::AddVertex( T* objectPtr )
{
	assert( objectPtr != 0 );
	assert( adjacencyListsOut.find( objectPtr ) == adjacencyListsOut.end( ) );
	assert( adjacencyListsIn.find( objectPtr ) == adjacencyListsIn.end( ) );
	assert( find( vertices.begin( ), vertices.end( ), objectPtr ) == vertices.end( ) );
	// ��������� ������ ������
	adjacencyListsOut[objectPtr];
	adjacencyListsIn[objectPtr];
	vertices.push_back( objectPtr );
}

template <typename T>
void CDirectedGraph<T>::AddEdge( T* fromVertex, T* toVertex )
{
	// ��� ������� ������ ������������
	assert( adjacencyListsOut.find( fromVertex ) != adjacencyListsOut.end( ) );
	assert( adjacencyListsOut.find( toVertex ) != adjacencyListsOut.end( ) );

	assert( adjacencyListsIn.find( fromVertex ) != adjacencyListsIn.end( ) );
	assert( adjacencyListsIn.find( toVertex ) != adjacencyListsIn.end( ) );

	assert( find( vertices.begin( ), vertices.end( ), fromVertex ) != vertices.end( ) );
	assert( find( vertices.begin( ), vertices.end( ), toVertex ) != vertices.end( ) );

	adjacencyListsOut[fromVertex].push_back( toVertex );
	adjacencyListsIn[toVertex].push_back( fromVertex );
}

template <typename T>
void CDirectedGraph<T>::DeleteVertex( T* objectPtr )
{
	// Not implemented
	assert( false );
}

template <typename T>
void CDirectedGraph<T>::DeleteEdge( T* fromVertex, T* toVertex )
{
	// Not implemented
	assert( false );
}

template <typename T>
const vector<T*>& CDirectedGraph<T>::GetEdgesFromVertex( T* fromVertex ) const
{
	assert( adjacencyListsOut.find( fromVertex ) != adjacencyListsOut.end( ) );
	return adjacencyListsOut[fromVertex];
}

template <typename T>
const vector<T*>& CDirectedGraph<T>::GetEdgesToVertex( T* toVertex ) const
{
	assert( adjacencyListsIn.find( toVertex ) != adjacencyListsIn.end( ) );
	return adjacencyListsIn[toVertex];
}

template <typename T>
bool CDirectedGraph<T>::HasVertex( T* objectPtr ) const
{
	return adjacencyListsIn.find( objectPtr ) != adjacencyListsIn.end( );
}

template <typename T>
bool CDirectedGraph<T>::HasEdge( T* fromVertex, T* toVertex ) const
{
	if( adjacencyListsOut.find( fromVertex ) == adjacencyListsOut.end( ) ) {
		return false;
	}

	vector<T*>& outList = adjacencyListsOut[fromVertex];
	return find( outList.begin( ), outList.end( ), toVertex ) != outList.end( );
}

} // RegisterAllocation