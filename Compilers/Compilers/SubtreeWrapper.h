// Автор: Воротилов Владислав

#pragma once
#include "IRTree.h"
#include "Temp.h"

namespace Translate {
	class ISubtreeWrapper {
	public:
		virtual const IRTree::IIRExp* ToExp( ) const = 0;
		virtual const IRTree::IIRStm* ToStm( ) const = 0;
		virtual const IRTree::IIRStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const = 0;

	};


}; //namespace Translate