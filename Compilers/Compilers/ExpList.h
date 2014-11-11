#pragma once

#include "Visitor.h"
#include "Grammar.h"
#include <memory>
#include <list>

class CExpList : public IExpList {
public:
	CExpList(CExpList* _restOfList, IExp* _exp) {
		if (_restOfList != 0) {
			expList = _restOfList->expList;
		}
		expList.push_back( std::shared_ptr<IExp>(_exp) );
	}

	std::list<std::shared_ptr<IExp>> expList;
};