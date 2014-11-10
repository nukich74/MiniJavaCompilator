#pragma once

#include <memory>
#include "Grammar.h"
#include "Visitor.h"

class CProgram : public IProgram {
public:
	CProgram( std::shared_ptr<IMainClass> _pMainClass, std::shared_ptr<IClassDeclList> _pClassDeclList ) :
		pMainClass( _pMainClass ), pClassDeclList( _pClassDeclList ) {}

	std::shared_ptr<IMainClass> GetMainClass() { return pMainClass; }
	std::shared_ptr<IClassDeclList> GetClassDeclList() { return pClassDeclList; }

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

private:
	std::shared_ptr<IMainClass> pMainClass;
	std::shared_ptr<IClassDeclList> pClassDeclList;
};