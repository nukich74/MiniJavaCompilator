#include "IRStm.h"
#include "IRHelpers.h"
#include "SubtreeWrapper.h"
#include "IRExp.h"

namespace Translate {
	
	class CConditionalWrapper : public ISubtreeWrapper {
		const IRTree::IExp* ToExp() const;
		const IRTree::IStm* ToStm() const;
	};

	class CAndWrapper : public CConditionalWrapper {
	public:
		const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f);
	private:
		const IRTree::IExp* left;
		const IRTree::IExp* right;
	};

	class CLessWrapper : public CConditionalWrapper {
	public:
		const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f );
	private:
		const IRTree::IExp* left;
		const IRTree::IExp* right;
	};
}