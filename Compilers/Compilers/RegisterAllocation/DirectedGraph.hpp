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
	T* AddVertex( const T& value );
	// Добавляет созданный ранее с помощью оператора new объект, который переходит во владение этого класса.
	void AttachVertex( T* objectPtr );
	// Добавляем ориентированное ребро. Если какой-нибудь вершины нет, то сработает assert
	void AddEdge( T* fromVertex, T* toVertex );
	void AddEdge( const T& fromVertexByValue, const T& toVertexByValue );
	// Добавляет ребра в обе стороны
	void AddBothEdges( T* firstVertex, T* secondVertex );
	void AddBothEdges( const T& firstVertexByValue, const T& secondVertexByValue );

	// Методы удаления нереализованы
	void DeleteVertex( const T& value );
	void DeleteEdge( T* fromVertex, T* toVertex );

	// Есть ли такое ребро?
	bool HasEdge( T* fromVertex, T* toVertex ) const;
	bool HasEdge( const T& fromVertexByValue, const T& toVertexByValue ) const;
	// Поиск вершины по значению, если не найдено, то возвращает 0
	T* FindVertex( const T& value );

	// Доступ к ребрам, выходящих из fromVertex. Если такой вершины нет, то сработает assert
	const vector<T*>& GetEdgesFromVertex( T* fromVertex );
	// Доступ к ребрам, входящих в toVertex. Если такой вершины нет, то сработает assert
	const vector<T*>& GetEdgesToVertex( T* toVertex );
	// Доступ к вершинам
	const vector<shared_ptr<T> >& GetVertices()
		{ return vertices; }

	// Скопировать указатели на вершины
	void CopyVerticesTo( vector<T*>& dst );

	// Упорядочить вершины в порядке обхода в глубины (пригодится для оптимизаций)
	void SortVertices( vector<T*>& orderedVertices, TVerticesOrder type );


private:
	// adjacencyListOut[i] - список вершин, в которые входят ребра, исходящие из i-ой вершины
	map<T*, vector<T*> > adjacencyListsOut;
	// adjacencyListsIn[i] - список вершин, из которых исходят ребра, входящие в i-ю вершину
	map<T*, vector<T*> > adjacencyListsIn;
	// Массив всех вершин
	vector<shared_ptr<T> > vertices;

	// Обход в глубину
	void walkDFS( T* vertex, vector<T*>& orderedVertices );

};

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Реализация методов шаблонного класса CDirectedGraph

template <typename T>
T* CDirectedGraph<T>::AddVertex( const T& value )
{
	assert( FindVertex( value ) == 0 );
	// Добавляем пустые списки
	vertices.push_back( shared_ptr<T>( new T( value ) ) );
	T* objectPtr = vertices.back().get();
	adjacencyListsOut[objectPtr];
	adjacencyListsIn[objectPtr];

	return objectPtr;
}

template <typename T>
void CDirectedGraph<T>::AttachVertex( T* objectPtr )
{
	assert( FindVertex( *objectPtr ) == 0 );
	// Добавляем пустые списки
	vertices.push_back( shared_ptr<T>( objectPtr ) );
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

	// Нельзя добавить дублирующее ребро
	assert( find( adjacencyListsOut[fromVertex].begin(), adjacencyListsOut[fromVertex].end(), toVertex ) ==
		adjacencyListsOut[fromVertex].end() );
	assert( find( adjacencyListsIn[toVertex].begin( ), adjacencyListsIn[toVertex].end( ), fromVertex ) ==
		adjacencyListsIn[toVertex].end() );

	adjacencyListsOut[fromVertex].push_back( toVertex );
	adjacencyListsIn[toVertex].push_back( fromVertex );
}

template <typename T>
void CDirectedGraph<T>::AddEdge( const T& fromVertexByValye, const T& toVertexByValye )
{
	T* fromVertex = FindVertex( fromVertexByValue );
	if( fromVertex == 0 ) {
		fromVertex = AddVertex( fromVertexByValye );
	}
	T* toVertex = FindVertex( toVertexByValue );
	if( toVertex == 0 ) {
		toVertex = AddVertex( toVertexByValue );
	}
	AddEdge( fromVertex, toVertex );
}

template <typename T>
void CDirectedGraph<T>::AddBothEdges( T* firstVertex, T* secondVertex )
{
	AddEdge( firstVertex, secondVertex );
	AddEdge( secondVertex, firstVertex );
}

template <typename T>
void CDirectedGraph<T>::AddBothEdges( const T& firstVertexByValue, const T& secondVertexByValue )
{
	T* firstVertex = FindVertex( firstVertexByValue );
	if( firstVertex == 0 ) {
		firstVertex = AddVertex( firstVertexByValue );
	}
	T* secondVertex = FindVertex( secondVertexByValue );
	if( secondVertex == 0 ) {
		secondVertex = AddVertex( secondVertexByValue );
	}
	AddBothEdges( firstVertex, secondVertex );
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
const vector<T*>& CDirectedGraph<T>::GetEdgesFromVertex( T* fromVertex )
{
	assert( adjacencyListsOut.find( fromVertex ) != adjacencyListsOut.end( ) );
	return adjacencyListsOut.find( fromVertex )->second;
}

template <typename T>
const vector<T*>& CDirectedGraph<T>::GetEdgesToVertex( T* toVertex )
{
	assert( adjacencyListsIn.find( toVertex ) != adjacencyListsIn.end( ) );
	return adjacencyListsIn.find( toVertex )->second;
}

template <typename T>
T* CDirectedGraph<T>::FindVertex( const T& value )
{
	for( const auto& vertex : vertices ) {
		if( *vertex == value ) {
			return vertex.get();
		}
	}

	return 0;
}

template <typename T>
bool CDirectedGraph<T>::HasEdge( T* fromVertex, T* toVertex ) const
{
	auto it = adjacencyListsOut.find( fromVertex );
	if( it == adjacencyListsOut.end( ) ) {
		return false;
	}

	const vector<T*>& outList = it->second;
	return find( outList.begin( ), outList.end( ), toVertex ) != outList.end();
}

template <typename T>
bool CDirectedGraph<T>::HasEdge( const T& fromVertexByValue, const T& toVertexByValue ) const
{
	T* fromVertex = const_cast<CDirectedGraph<T>*>(this)->FindVertex( fromVertexByValue );
	if( fromVertex == 0 ) {
		return false;
	}
	T* toVertex = const_cast<CDirectedGraph<T>*>(this)->FindVertex( toVertexByValue );
	if( toVertex == 0 ) {
		return false;
	}

	return HasEdge( fromVertex, toVertex );
}

template <typename T>
void CDirectedGraph<T>::SortVertices( vector<T*>& orderedVertices, TVerticesOrder type )
{
	assert( type == VO_DFS );

	orderedVertices.clear();

	for( const auto& vertex : vertices ) {
		walkDFS( vertex.get(), orderedVertices );
	}

	assert( orderedVertices.size() == vertices.size() );
}

template <typename T>
void CDirectedGraph<T>::walkDFS( T* vertex, vector<T*>& orderedVertices )
{
	if( find( orderedVertices.begin(), orderedVertices.end(), vertex ) != orderedVertices.end() ) {
		return;
	}

	orderedVertices.push_back( vertex );
	for( const auto& vertexPtr : GetEdgesFromVertex( vertex ) ) {
		walkDFS( vertexPtr, orderedVertices );
	}
}

template <typename T>
void CDirectedGraph<T>::CopyVerticesTo( vector<T*>& dst )
{
	dst.clear();

	for( auto& vertex : vertices ) {
		dst.push_back( &*vertex );
	}
}

} // RegisterAllocation
