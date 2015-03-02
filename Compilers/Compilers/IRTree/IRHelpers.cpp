#include "IRHelpers.h"

std::string IRTree::ToString( const TBinop binOp )
{
	switch( binOp ) {
	case B_Plus:
		return std::string( "+" );
	case B_Minus:
		return std::string( "-" );
	case B_Mul:
		return std::string( "*" );
	case B_Division:
		return std::string( "/" );
	case B_Xor:
		return std::string( "^" );
	case B_Less:
		return std::string( "<" );
	case B_Greater:
		return std::string( ">" );
	case B_And:
		return std::string( "&" );
	default:
		assert( false );
		return std::string( "" );
	}
}
