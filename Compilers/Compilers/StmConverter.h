// Автор: Воротилов Владислав

#pragma once
#include "IRTree.h"
#include "IRStm.h"
#include "Temp.h"
#include "SubtreeWrapper.h"
#include <assert.h>

namespace Translate {

class CStmConverter : public ISubtreeWrapper {
public:
	CStmConverter( IRTree::IIRStm* e) : expr( e ) {}
	IRTree::IIRExp* ToExp() const { assert( false ); }
	IRTree::IIRStm* ToStm() const { return expr; }
	IRTree::IIRStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const { 
		assert( false );
	}
private:
	IRTree::IIRStm* expr;
};

}; //namespace Translate