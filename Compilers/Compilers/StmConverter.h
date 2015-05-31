// Автор: Воротилов Владислав

#pragma once
#include "IRTree.h"
#include "IRStm.h"
#include "Temp.h"
#include "SubtreeWrapper.h"
#include "FineAssert.h"

namespace Translate {

class CStmConverter : public ISubtreeWrapper {
public:
	CStmConverter( IRTree::IStm* e) : expr( e ) {}
	IRTree::IExp* ToExp() const { assert( false ); }
	IRTree::IStm* ToStm() const { return expr; }
	IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const { 
		assert( false );
	}
private:
	IRTree::IStm* expr;
};

}; //namespace Translate