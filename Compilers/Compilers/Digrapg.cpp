#include "Digrapg.h"

#include <ostream>
#include <fstream>

CDigraph::CDigraph( std::string _fileName )
	: fileName( _fileName ), data( "digraph {\n" ), isFlushed( false )
{

}

CDigraph::~CDigraph()
{
	if( !isFlushed ) {
		Flush();
	}
}

void CDigraph::AddEdge( std::string from, std::string to )
{
	data += from + " -> " + to + " ; \n";
}

void CDigraph::AddEdge( std::string from, std::string to, std::string edgeName )
{
	data += from + " -> " + to + " [ label=\"" + edgeName + "\"] ; \n";
}

void CDigraph::Flush()
{
	data += "\n}";
	std::ofstream out( fileName );
	out << data;
	out.close();
	isFlushed = true;
}

void CDigraph::SetNodeLabel( std::string nodeName, std::string nodeLabel )
{
	data += nodeName + " [ label=\"" + nodeLabel + "\" ]; \n";
}


