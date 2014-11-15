#pragma once

#include <memory>
#include "Grammar.h"
#include "Exp.h"
#include "Visitor.h"
#include "TypeIdentifier.h"

class CType : public IType {
public:

	CType( SymbolsTable::CTypeIdentifier _type, CId* _pId ) :
		type( _type ),
		pId( _pId ) {}

	void accept( IVisitor& visitor )
	{
		visitor.visit( *this );
	}

	SymbolsTable::CTypeIdentifier type;
	std::shared_ptr<CId> pId;
};