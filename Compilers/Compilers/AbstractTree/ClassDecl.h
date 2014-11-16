#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>

class CClassDecl : public IClassDecl {
public:
	CClassDecl( std::string& _classId, IVarDeclList* _pVarDeclList, IMethodDeclList* _pMethodDeclList, std::string& _parrentId ) :
		classId( _classId ),
		pVarDeclList( _pVarDeclList ),
		pMethodDeclList( _pMethodDeclList ),
		parrentId( _parrentId )
	{}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::string classId;
	std::shared_ptr<IVarDeclList> pVarDeclList;
	std::shared_ptr<IMethodDeclList> pMethodDeclList;
	std::string parrentId;
};