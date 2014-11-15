#pragma once

#include <memory>
#include "Grammar.h"
#include "Exp.h"
#include "Visitor.h"

class CVarDecl : public IVarDecl {
public:
	CVarDecl( IType* _pType, CId* _pId ) :
		pId( _pId ),
		pType( _pType )
	{}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IType> pType;
	std::shared_ptr<CId> pId;
};