#pragma once

#include <memory>
#include "Grammar.h"
#include "Visitor.h"

class CProgram : public IProgram {
public:
	CProgram( IMainClass* _pMainClass, IClassDeclList* _pClassDeclList ) :
		pMainClass( _pMainClass ), pClassDeclList( _pClassDeclList ) {}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::shared_ptr<IMainClass> pMainClass;
	std::shared_ptr<IClassDeclList> pClassDeclList;
};