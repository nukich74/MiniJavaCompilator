#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>

class CVarDecl : public IVarDecl {
public:
	CVarDecl( IType* _pType, const std::string& _id ) :
		id( _id ),
		pType( _pType )
	{}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IType> pType;
	std::string id;
};