// Автор: Воротилов Владислав

#pragma once
#include "IRTree.h"
#include "IRStm.h"
#include "Temp.h"
#include "SubtreeWrapper.h"
#include <assert.h>

namespace Translate {

class CExpConverter;

class CStmConverter : public ISubtreeWrapper {
public:
	CStmConverter(const IRTree::IIRStm* e) : expr( e ) {}
	const IRTree::IIRExp* ToExp() const { assert( false ); }
	const IRTree::IIRStm* ToStm() const { return expr; }
	const IRTree::IIRStm* ToConditional(const IRTree::CIRLabel* t, const IRTree::CIRLabel* f) const { 
		assert( false );
	}
private:
	const IRTree::IIRStm* expr;
};

}; //namespace Translate