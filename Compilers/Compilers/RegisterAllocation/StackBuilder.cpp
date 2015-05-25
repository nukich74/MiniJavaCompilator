#include "StackBuilder.h"
#include <string>

namespace RegisterAllocation {
	
	void CStackBuilder::buildStack() 
	{
			//построение стэка для вершин
			do {
				bool isSimplified = simplify();
				while (isSimplified) isSimplified = simplify();
				bool isCoaliced = coalice();
				if (isCoaliced) continue;
				bool isFrosen = freeze();
				if (isFrosen) continue;
				bool isSpilled = spill();
				if (!isSpilled) break;
			} while ( true );
			//раскраска
			vector<Temp::CTemp> vertices;
			sourceGraph.GetVertices( vertices );
			int currColor = 1;
			std::unordered_set<int> availColors;
			for ( auto vert : vertices ) {
				if ( vert.Name()[0] == 'E' && vert.Name() != "ESP" && vert.Name() != "EBP" ) {
					colors[vert] = currColor;
					++currColor;
				}
			}
			while ( !vertexStack.empty() ) {
				Temp::CTemp currVertex = vertexStack.top();
				vertexStack.pop();
				vector<Temp::CTemp> vertices;
				sourceGraph.GetVertices( vertices );
				std::unordered_set<int> neighborColors;
				std::unordered_set<Temp::CTemp> coaliced;
				std::string vertName = currVertex.Name();
				int assignColor = 0;
				//вытаскиваем все переменные, свернутые в данную
				while ( vertName.find("&") != std::string::npos ) {
					int pos = vertName.find("&");
					std::string currTemp = vertName.substr( 0, pos );
					if ( currTemp[0] == 'E' ) assignColor = colors[ Temp::CTemp( currTemp ) ];
					coaliced.insert( Temp::CTemp( currTemp ) );
					vertName = vertName.substr( pos + 1 );
				}
				if ( assignColor == 0 ) {
					coaliced.insert( Temp::CTemp(vertName) );
					for ( auto vert : vertices ) {
						for ( auto firstVar : coaliced )
							if ( sourceGraph.GetEdge( firstVar, vert ) == RegisterAllocation::CVarInterferenceGraphBuilder::ET_Interfere ) {
								neighborColors.insert( colors[vert] );
							}
					}
					for (int i = 1; i <= k; ++i) {
						if ( neighborColors.find(i) == neighborColors.end() ) {
							assignColor = i;
							break;
						}
					}
				}
				for( auto coal : coaliced ) {
					colors[coal] = assignColor;
				}
				//так как исходная вершина с & раскрашена не будет, то делаем это отдельно
				colors[currVertex] = assignColor;
			}
			//удаляем вспомогательную информацию о свернутых переменных
			//инкремент упрятывается, чтобы не было инкремента невалидного итератора
			for ( auto iter = colors.begin(); iter != colors.end(); ) {
				if ( iter->first.Name().find("&") != std::string::npos ) {
					auto oldIter = iter;
					++iter; 
					colors.erase( oldIter );
				} else {
					++iter;
				}
			}
			//соответствие цветов и регистров
			std::unordered_map<int, Temp::CTemp> colors2Registers;
			for ( auto iter = colors.begin(); iter != colors.end(); ++iter ) {
				if ( iter->first.Name()[0] == 'E' ) {
					colors2Registers[iter->second] = iter->first;
				}
			}
			for ( auto iter = colors.begin(); iter != colors.end(); ++iter ) {
				registers[iter->first] = colors2Registers[iter->second].Name();
			}
			registers[Temp::CTemp("ESP")] = "ESP";
			registers[Temp::CTemp("EBP")] = "EBP";
		}

	bool CStackBuilder::simplify()
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices( vertices );
		for ( auto from : vertices ) {
			if ( from.Name()[0] == 'E' ) continue;
			if ( varGraph.GetDegree(from) <= k ) {
				bool moveMarked = false;
				for (auto to : vertices) {
					if ( varGraph.GetEdge( from, to ) == CVarInterferenceGraphBuilder::ET_Move ) {
						moveMarked = true;
						break;
					}
				}
				if ( !moveMarked ) {
					vertexStack.push(from);
					varGraph.DeleteVertex(from);
					return true;
				}
			}
		}
		return false;
	}

	bool CStackBuilder::freeze()
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices( vertices );
		for (auto from : vertices) {
			bool moveVertex = false;
			int degree = varGraph.GetDegree( from ); 
			for (auto to : vertices) {
				if ( varGraph.GetEdge( from, to ) == CVarInterferenceGraphBuilder::ET_Move ) {
					moveVertex = true;
					break;
				}
			}
			if ( moveVertex && degree < k ) {
				varGraph.FreezeVertex(from);
				return true;
			}
		}
		return false;
	}

	bool CStackBuilder::coalice()
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices( vertices );
		for ( auto firstVar : vertices )  {
			for ( auto secondVar : vertices ) {
				if ( varGraph.GetEdge( firstVar, secondVar ) == CVarInterferenceGraphBuilder::ET_Move 
						&& varGraph.CanCoalice( firstVar, secondVar, k ) ) {
					varGraph.MergeVertices( firstVar, secondVar );
					return true;
				}
			}
		}
		return false;
	}

	bool CStackBuilder::spill() 
	{
		vector<Temp::CTemp> vertices;
		varGraph.GetVertices(vertices);
		for ( auto vert : vertices ) {
			if ( vert.Name()[0] != 'E' ) {
				varGraph.DeleteVertex( vert );
				vertexStack.push( vert );
				return true;
			}
		}
		return false;
	}

}