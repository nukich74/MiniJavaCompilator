#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>
#include "TypeIdentifier.h"

class CType : public IType {
public:

	CType( const std::string& _id ) :
		id( _id )
	{ }

	void accept( IVisitor& visitor )
	{
		visitor.visit( *this );
	}

	std::string id;
};