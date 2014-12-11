#include "IRExp.h"
#include "IRStm.h"
#include "SubtreeWrapper.h"

namespace Translate {
	
	class CExpConverter : public ISubtreeWrapper {
	public:
		CExpConverter( IRTree::IIRExp* _exp ) : exp( _exp ) {}
		IRTree::IIRExp* ToExp() const { return exp; }
		IRTree::IIRStm* ToStm() const { return new IRTree::CIRExp(exp); }
		IRTree::IIRStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const { 
			return new IRTree::CIRCjump( IRTree::CJ_NotEqual, exp, new IRTree::CIRConst( 0 ), t, f ); 
		}
	private:
		IRTree::IIRExp* exp;
	};

}