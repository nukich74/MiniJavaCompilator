#include "IRExp.h"
#include "IRStm.h"
#include "SubtreeWrapper.h"

namespace Translate {
	
	class CExpConverter : public ISubtreeWrapper {
	public:
		CExpConverter( const IRTree::IExp* _exp ) : exp( _exp ) {}
		const IRTree::IExp* ToExp() const { return exp; }
		const IRTree::IStm* ToStm() const { return new IRTree::CExp(exp); }
		const IRTree::IStm* ToConditional( const Temp::CLabel* t, const Temp::CLabel* f ) const { 
			return new IRTree::CCjump( IRTree::CJ_NotEqual, exp, new IRTree::CConst( 0 ), t, f ); 
		}
	private:
		const IRTree::IExp* exp;
	};

}