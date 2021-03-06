﻿// Автор: Азат Давлетшин
// Описание: Построение графа взаимодействия переменных на основе ГПУ

#pragma once

#include <RegisterAllocation\FlowControlGraphBuilder.h>
#include <Temp.h>
#include <unordered_map>

namespace RegisterAllocation {

// Класс-механизм для построения графа взаимодействия переменных (ГВП). ГВП - граф, вершины которого - 
// указатели на переменные, а ребро означает наличие взаимодействия
class CVarInterferenceGraphBuilder {
public:
	// Тип ребра ГВП
	enum TEdgeType {
		// Есть взаимодействие (не MOVE)
		ET_Interfere,
		// Взаимодействие через инструкцию MOVE
		ET_Move,
		// Нет взаимодействия
		ET_None,
		ET_EnumSize
	};

	// Определяем свой граф для этого класса, так как CDirectedGraph плохо подходит к этой задаче
	class CGraph {
	public:
		void AddVertices( const vector<Temp::CTemp>& vars );
		// Получить ребро
		TEdgeType GetEdge( const Temp::CTemp& firstVar, const Temp::CTemp& secondVar ) const;
		// Установить ребро
		void SetEdge( const Temp::CTemp& firstVar, const Temp::CTemp& secondVar, TEdgeType edgeType );
		//Получить список вершин
		void GetVertices( vector<Temp::CTemp>& vertices );
		//Объединить 2 вершины
		void MergeVertices( const Temp::CTemp& firstVar, const Temp::CTemp& secondVar );
		//Удалить вершину
		void DeleteVertex( const Temp::CTemp& vertex );
		//Заморозка вершины
		void FreezeVertex( const Temp::CTemp& vertex );
		//Проверяет, можно ли объединить 2 вершины
		bool CanCoalice( const Temp::CTemp& firstVar, const Temp::CTemp& secondVar, int k );
		//Обновляет значения степеней вершин
		void UpdateDegree();
		void ConnectRegisters();
		int GetDegree( const Temp::CTemp& vertex );

	private:
		std::unordered_map<Temp::CTemp, std::unordered_map<Temp::CTemp, TEdgeType> > edges;
		std::unordered_map<Temp::CTemp, int> degree;
	};

	// Собственно построить граф взаимодействия переменных по графу потока управления
	void BuildVarInterferenceGraph( const vector<CFlowControlVertex*>& flowControlVertices );
	// Получить ГВП (результат работы алгоритма)
	const CGraph& GetVarInterferenceGraph()
		{ return varInterferenceGraph; }

private:
	CGraph varInterferenceGraph;

	void addVerticesToGraph( const vector<CFlowControlVertex*>& flowControlVertices );
};

} // namespace RegisterAllocation
