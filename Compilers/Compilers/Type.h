#pragma once

#include <memory>
#include "Grammar.h"
#include "Exp.h"
#include "Visitor.h"

class CType : public IType {
public:
	enum Type {
		T_INT,
		T_INTARR,
		T_BOOL,
		T_ID
	};

	CType( CType::Type _type, CId* _pId ) :
		type( _type ),
		pId( _pId ) {}

	void accept( IVisitor& visitor )
	{
		visitor.visit( *this );
	}

	Type type;
	std::shared_ptr<CId> pId;
};