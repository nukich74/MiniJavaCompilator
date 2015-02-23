// Автор: Воротилов Владислав
// Описание: Класс инкапсулирующий создание файла dot для graphviz

#pragma once

#include <string>

class CDigraph {
public:

	CDigraph( std::string _fileName );
	~CDigraph();

	void AddEdge( std::string from, std::string to );

private:

	void flush();
	
	std::string fileName;
	std::string data;

};