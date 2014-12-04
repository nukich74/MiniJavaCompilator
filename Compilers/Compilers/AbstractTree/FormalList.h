// Описание: Класс, описывающий вершину AST, отвечающую списку определений переменных.

#pragma once

#include <memory>
#include <list>
#include <Grammar.h>
#include <Visitor.h>

class CFormalList : public IFormalList, public CLocationStorage {
public:
	CFormalList( CFormalList* pFormalList, IType* _pType, const std::string& id, const CLocation& location ) : CLocationStorage( location )
	{
		if( pFormalList != 0 ) {
			formalList = pFormalList->formalList;
		}
		formalList.emplace_back( std::make_pair( std::shared_ptr<IType>( _pType ), id ) );
	}

	void Accept( IVisitor& visitor ) const { visitor.Visit( *this ); }

	const std::list< std::pair< std::shared_ptr<IType>, std::string > >& FormalList() const { return formalList; }

private:
	std::list< std::pair< std::shared_ptr<IType>, std::string > > formalList;
};