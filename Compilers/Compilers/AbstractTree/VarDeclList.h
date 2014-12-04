// Описание: Класс, описывающий вершину AST, отвечающую набору объявлений переменных.

#pragma once

#include <memory>
#include <list>
#include <Grammar.h>
#include <Visitor.h>

class CVarDeclList : public IVarDeclList, public CLocationStorage {
public:
	CVarDeclList( CVarDeclList* pVarDeclList, IVarDecl* _pVarDecl, const CLocation& location ) : CLocationStorage( location )
	{
		if( pVarDeclList != 0 ) {
			varDeclList = pVarDeclList->varDeclList;
		}
		varDeclList.emplace_back( std::shared_ptr<IVarDecl>( _pVarDecl ) );
	}

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::list< std::shared_ptr<IVarDecl> >& VarDeclList() const { return varDeclList; }

private:
	std::list< std::shared_ptr<IVarDecl> > varDeclList;
};