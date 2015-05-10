// Автор: Азат Давлетшин
// Описание: Опредление класса направленного графа. Применяется для Анализа потока управления и Графа взаимодействия

#pragma once

#include <vector>
#include <map>
#include <assert.h>
#include <algorithm>
#include <memory>

using std::vector;
using std::map;
using std::find;
using std::shared_ptr;

namespace RegisterAllocation {

// Тип упорядочивания вершин графа
enum TVerticesOrder {
	VO_DFS
};

// Ориетированный граф. Так как графы в наших задачах разреженные, то целесообразно представить граф в виде списков
// смежности. Владеет памятью через unique_ptr
template <typename T>
class CDirectedGraph {
public:
	// Добавляет вершину для объекта. Если такое же значение уже есть в графе, то сработет assert
	void AddVertex( const T& value );
	// Добавляем ориентированное ребро. Если какой-нибудь вершины нет, то сработает assert
	void AddEdge( T* fromVertex, T* toVertex );
	// Добавляет ребра в обе стороны
	void AddBothEdges( T* firstVertex, T* secondVertex );

	// Методы удаления нереализованы
	void DeleteVertex( const T& value );
	void DeleteEdge( T* fromVertex, T* toVertex );

	// Есть ли такое ребро?
	bool HasEdge( T* fromVertex, T* toVertex ) const;
	// Поиск вершины по значению, если не найдено, то возвращает 0
	T* FindVertex( const T& value ) const;

	// Доступ к ребрам, выходящих из fromVertex. Если такой вершины нет, то сработает assert
	const vector<T*>& GetEdgesFromVertex( T* fromVertex ) const;
	// Доступ к ребрам, входящих в toVertex. Если такой вершины нет, то сработает assert
	const vector<T*>& GetEdgesToVertex( T* toVertex ) const;
	// Доступ к вершинам
	const vector<shared_ptr<T> >& GetVertices( ) const
		{ return vertices; }

	// Упорядочить вершины в порядке обхода в глубины (пригодится для оптимизаций)
	void SortVertices( vector<T*>& orderedVertices, TVerticesOrder type ) const;


private:
	// adjacencyListOut[i] - список вершин, в которые входят ребра, исходящие из i-ой вершины
	map<T*, vector<T*> > adjacencyListsOut;
	// adjacencyListsIn[i] - список вершин, из которых исходят ребра, входящие в i-ю вершину
	map<T*, vector<T*> > adjacencyListsIn;
	// Массив всех вершин
	vector<shared_ptr<T> > vertices;

	// Обход в глубину
	void walkDFS( T* vertex, vector<T*>& orderedVertices ) const;

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Реализация методов шаблонного класса CDirectedGraph

template <typename T>
void CDirectedGraph<T>::AddVertex( const T& value )
{
	assert( FindVertex( value ) == 0 );
	// Добавляем пустые списки
	vertices.emplace_back( new T( value ) );
	T* objectPtr = vertices.back().get();
	adjacencyListsOut[objectPtr];
	adjacencyListsIn[objectPtr];
}

template <typename T>
void CDirectedGraph<T>::AddEdge( T* fromVertex, T* toVertex )
{
	// Обе вершины должны существовать
	assert( adjacencyListsOut.find( fromVertex ) != adjacencyListsOut.end( ) );
	assert( adjacencyListsOut.find( toVertex ) != adjacencyListsOut.end( ) );

	assert( adjacencyListsIn.find( fromVertex ) != adjacencyListsIn.end( ) );
	assert( adjacencyListsIn.find( toVertex ) != adjacencyListsIn.end( ) );

	adjacencyListsOut[fromVertex].push_back( toVertex );
	adjacencyListsIn[toVertex].push_back( fromVertex );
}

template <typename T>
void CDirectedGraph<T>::AddBothEdges( T* firstVertex, T* secondVertex )
{
	AddEdge( fromVertex, toVertex );
	AddEdge( toVertex, fromVertex );
}

template <typename T>
void CDirectedGraph<T>::DeleteVertex( const T& value )
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
	return adjacencyListsOut.find( fromVertex )->second;
}

template <typename T>
const vector<T*>& CDirectedGraph<T>::GetEdgesToVertex( T* toVertex ) const
{
	assert( adjacencyListsIn.find( toVertex ) != adjacencyListsIn.end( ) );
	return adjacencyListsIn.find( toVertex )->second;
}

template <typename T>
T* CDirectedGraph<T>::FindVertex( const T& value ) const
{
	for( int i = 0; i < vertices.size(); i++ ) {
		if( *vertices[i] == value ) {
			return vertices[i].get();
		}
	}

	return 0;
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

template <typename T>
void CDirectedGraph<T>::SortVertices( vector<T*>& orderedVertices, TVerticesOrder type ) const
{
	assert( type == VO_DFS );

	orderedVertices.clear();

	for( int i = 0; i < vertices.size(); i++ ) {
		walkDFS( vertices[i].get(), orderedVertices );
	}

	assert( orderedVertices.size() == vertices.size() );
}

template <typename T>
void CDirectedGraph<T>::walkDFS( T* vertex, vector<T*>& orderedVertices ) const
{
	if( find( orderedVertices.begin(), orderedVertices.end(), vertex ) != orderedVertices.end() ) {
		return;
	}

	orderedVertices.push_back( vertex );
	const vector<T*>& edgesFromVertex = GetEdgesFromVertex( vertex );
	for( int i = 0; i < edgesFromVertex.size(); i++ ) {
		walkDFS( edgesFromVertex[i], orderedVertices );
	}
}

} // RegisterAllocation
