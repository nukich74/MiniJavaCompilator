#include <Temp.h>

using namespace std;

int Temp::CLabel::nextUniqueId = 0;
int Temp::CTemp::nextUniqueId = 0;

namespace Temp
{
CLabel::CLabel()
{
	name = "tempLabel" + std::to_string( nextUniqueId );
	nextUniqueId++;
}

CLabel::CLabel( const string& _name ) :
	name( _name ) {}

CTemp::CTemp()
{
	name = "tempVar" + std::to_string( nextUniqueId );
	nextUniqueId++;
}

CTemp::CTemp( const string& _name ) :
	name( _name )
{
	// Nothing
}
}