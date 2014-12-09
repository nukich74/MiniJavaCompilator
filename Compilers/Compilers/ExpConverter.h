#include "IRExp.h"
#include "IRStm.h"
#include "SubtreeWrapper.h"

namespace Translate {
	
	class CExpConverter : public ISubtreeWrapper {
	public:
		CExpConverter( const IRTree::IIRExp* _exp ) : exp( _exp ) {}
		const IRTree::IIRExp* ToExp() { return exp; }
		const IRTree::IIRStm* ToStm() { return new IRTree::CIRExp(exp); }
		const IRTree::IIRStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) { 
			return new IRTree::CIRCjump( IRTree::CJ_NotEqual, exp, new IRTree::CIRConst( 0 ), t, f ); 
		}
	private:
		const IRTree::IIRExp* exp;
	};

}