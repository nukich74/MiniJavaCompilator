// Автор: Воротилов Владислав

#pragma once
#include "IRTree.h"
#include "Temp.h"

namespace Translate {
	class ISubtreeWrapper {
	public:
		virtual IRTree::IIRExp* ToExp( ) const = 0;
		virtual IRTree::IIRStm* ToStm( ) const = 0;
		virtual IRTree::IIRStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const = 0;

	};


}; //namespace Translate