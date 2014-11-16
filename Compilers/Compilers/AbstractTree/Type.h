#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>
#include "TypeIdentifier.h"

class CType : public IType {
public:

	CType( SymbolsTable::CTypeIdentifier _type, std::string& _id ) :
		type( _type ),
		id( _id ) {}

	void accept( IVisitor& visitor )
	{
		visitor.visit( *this );
	}

	SymbolsTable::CTypeIdentifier type;
	std::string id;
};