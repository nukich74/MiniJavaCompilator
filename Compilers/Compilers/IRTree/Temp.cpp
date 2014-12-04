#include <Temp.h>

using namespace std;

int Temp::CLabel::nextUniqueId = 0;
int Temp::CTemp::nextUniqueId = 0;

namespace Temp
{
CLabel::CLabel()
{
	name = "tempLabel" + nextUniqueId;
	nextUniqueId++;
}

CLabel::CLabel( const string& _name ) :
	name( _name )
{
	// Nothing
}

CTemp::CTemp()
{
	name = "tempVar" + nextUniqueId;
	nextUniqueId++;
}

CTemp::CTemp( const string& _name ) :
	name( _name )
{
	// Nothing
}
}