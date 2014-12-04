// Описание: Класс, описывающий вершину AST, отвечающую списку выражений.

#pragma once

#include "Grammar.h"
#include <memory>
#include <list>

class CExpList : public IExpList, public CLocationStorage {
public:
	CExpList( CExpList* _restOfList, IExp* _exp, const CLocation& location ) : CLocationStorage( location )
	{
		if( _restOfList != 0 ) {
			expList = _restOfList->expList;
		}
		expList.emplace_back( std::shared_ptr<IExp>( _exp ) );
	}

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::list< std::shared_ptr<IExp> >& ExpList() const { return expList; }

private:
	std::list< std::shared_ptr<IExp> > expList;
};