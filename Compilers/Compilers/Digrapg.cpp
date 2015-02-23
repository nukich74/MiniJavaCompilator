#include "Digrapg.h"

#include <ostream>
#include <fstream>

CDigraph::CDigraph( std::string _fileName )
	: fileName( _fileName ), data( "digraph {\n" )
{

}

CDigraph::~CDigraph()
{
	data += "\n}";
	flush();
}

void CDigraph::AddEdge( std::string from, std::string to )
{
	data += from + " -> " + to + " \n";
}

void CDigraph::flush()
{
	std::ofstream out( "fileName" );
	out << data;
	out.close();
}


