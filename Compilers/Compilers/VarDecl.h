#pragma once

#include <memory>
#include "Grammar.h"
#include "Exp.h"
#include "Visitor.h"

class CVarDecl : public IVarDecl {
public:
	CVarDecl( std::shared_ptr<IType> _pType, std::shared_ptr<CId> _pId ) :
		pId( _pId ),
		pType( _pType )
	{}

	std::shared_ptr<IType> GetType() { return pType; }
	std::shared_ptr<CId> GetId() { return pId; }

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

private:
	std::shared_ptr<IType> pType;
	std::shared_ptr<CId> pId;
};