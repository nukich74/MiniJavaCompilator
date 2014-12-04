// Описание: Класс, описывающий вершину AST, отвечающую типу.

#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>
#include "TypeIdentifier.h"

class CType : public IType, public CLocationStorage {
public:

	CType( const std::string& _typeName, const CLocation& location ) 
		: CLocationStorage( location )
		, typeName( _typeName )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::string& TypeName() const { return typeName; }

private:
	std::string typeName;
};