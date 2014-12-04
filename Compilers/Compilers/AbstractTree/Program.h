// Описание: Класс, описывающий вершину AST, отвечающую самой программе(корень дерева).

#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>

class CProgram : public IProgram, public CLocationStorage {
public:
	CProgram( IMainClass* _pMainClass, IClassDeclList* _pClassDeclList, const CLocation& location ) 
		: CLocationStorage( location )
		, pMainClass( _pMainClass )
		, pClassDeclList( _pClassDeclList )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IMainClass* MainClass() const { return pMainClass.get(); }

	const IClassDeclList* ClassDeclList() const { return pClassDeclList.get(); }

private:
	std::shared_ptr<IMainClass> pMainClass;
	std::shared_ptr<IClassDeclList> pClassDeclList;
};