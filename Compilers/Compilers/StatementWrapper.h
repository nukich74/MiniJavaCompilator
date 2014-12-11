#include "IRStm.h"
#include "IRHelpers.h"
#include "SubtreeWrapper.h"

namespace Translate {
	
	class CConditionalWrapper : public ISubtreeWrapper {
		const IRTree::IIRExp* ToExp() const;
		const IRTree::IIRStm* ToStm() const;
	};

	class CAndWrapper : public CConditionalWrapper {
	public:
		const IRTree::IIRStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f);
	private:
		const IRTree::IIRExp* left;
		const IRTree::IIRExp* right;
	};

	class CLessWrapper : public CConditionalWrapper {
	public:
		const IRTree::IIRStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f );
	private:
		const IRTree::IIRExp* left;
		const IRTree::IIRExp* right;
	};
}