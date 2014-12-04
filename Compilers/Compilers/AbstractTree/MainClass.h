// Описание: Класс, описывающий вершину AST, отвечающую классу содержащему entry point.

#pragma once

#include <memory>
#include <Grammar.h>
#include <Visitor.h>

class CMainClass : public IMainClass, public CLocationStorage {
public:
	CMainClass( const std::string& _mainClassName, const std::string& _stringName, IStatementList* _pStatementList, const CLocation& location ) 
		: CLocationStorage( location )
		, mainClassName( _mainClassName )
		, stringName( _stringName )
		, pStatementList( _pStatementList )
	{ }

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const IStatementList* StatementList() const { return pStatementList.get(); }

	const std::string& MainClassName() const { return mainClassName; }

	const std::string& StringName() const { return stringName; }

private:
	std::string mainClassName;
	std::string stringName;
	std::shared_ptr<IStatementList> pStatementList;
};