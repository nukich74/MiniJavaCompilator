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
	CAndWrapper( const IRTree::IExp* _left, const IRTree::IExp* _right ) : left( _left ), right( _right ) {}

	const virtual IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const override;

private:
	const IRTree::IExp* left;
	const IRTree::IExp* right;
};

}