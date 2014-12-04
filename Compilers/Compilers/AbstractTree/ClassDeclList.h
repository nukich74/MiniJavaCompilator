// Описание: Класс, описывающий вершину AST, отвечающую списку определений классов.

#pragma once

#include <memory>
#include <list>
#include <Grammar.h>
#include <Visitor.h>

class CClassDeclList : public IClassDeclList, public CLocationStorage {
public:
	CClassDeclList( CClassDeclList* pClassDeclList, IClassDecl* _pClassDecl, const CLocation& location ) : CLocationStorage( location ) 
	{
		if( pClassDeclList != 0 ) {
			classDeclList = pClassDeclList->classDeclList;
		}
		classDeclList.emplace_back( std::shared_ptr<IClassDecl>( _pClassDecl ) );
	}

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::list< std::shared_ptr<IClassDecl> >& ClassDeclList() const { return classDeclList; }

private:
	std::list< std::shared_ptr<IClassDecl> > classDeclList;
};