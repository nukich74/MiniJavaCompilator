#pragma once

#include <memory>
#include <list>
#include "Grammar.h"
#include "Exp.h"
#include "Visitor.h"

class CFormalList : public IFormalList {
public:
	CFormalList( CFormalList* pFormalList, IType* _pType, CId* _pId )
	{
		if( pFormalList != 0 )
		{
			formalList = pFormalList->formalList;
		}
		formalList.push_back( std::make_pair( std::shared_ptr<IType>( _pType ), std::shared_ptr<CId>( _pId ) ) );
	}

	void accept( IVisitor& visitor ) { visitor.visit( *this ); }

	std::list< std::pair< std::shared_ptr<IType>, std::shared_ptr<CId> > > formalList;
};