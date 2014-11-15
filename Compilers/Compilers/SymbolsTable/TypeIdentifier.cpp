// Автор: Фролов Николай.

#include "TypeIdentifier.h"
#include <cassert>

namespace SymbolsTable {
	CTypeIdentifier::CTypeIdentifier( const std::string& typeName )
	{
		if( typeName == "int" ) {
			Base = BT_Int;
		} else if( typeName == "bool" ) {
			Base = BT_Bool;
		} else if( typeName == "int[]" ){
			Base = BT_IntArr;
		} else {
			Base = BT_UserDefined;
			UserDefinedName = typeName;
		}
	}

	bool CTypeIdentifier::operator == ( const CTypeIdentifier& rhs ) const
	{
		if( Base != BT_UserDefined ) {
			return Base == rhs.Base;
		} else {
			return UserDefinedName == rhs.UserDefinedName;
		}
	}

	bool CTypeIdentifier::operator != ( const CTypeIdentifier& rhs ) const
	{
		return !( *this == rhs );
	}

	bool CTypeIdentifier::operator == ( const BaseTypes& rhs ) const
	{
		if( rhs == BT_UserDefined ) {
			assert( false );
		} else {
			return Base == rhs;
		}
	}

	bool CTypeIdentifier::operator != ( const BaseTypes& rhs ) const
	{
		return !( *this == rhs );
	}
}
