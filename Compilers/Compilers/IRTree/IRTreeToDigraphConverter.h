// Автор: Воротилов Владислав
// Описание: Преобразование дерева промежуточного представления в dot формат

#include "Digrapg.h"

namespace IRTree {

class CMove;
class CExp;
class CJump;
class CCjump;
class CSeq;
class CConst;
class CName;
class CTemp;
class CBinop;
class CMem;
class CCall;
class CEseq;
class CExpList;
class CLabel;


class CIRTreeToDigraphConverter {
public:
	CIRTreeToDigraphConverter( std::string treeFileName );

	void Print( const CMove* node );
	void Print( const CExp* node );
	void Print( const CJump* node );
	void Print( const CCjump* node );
	void Print( const CSeq* node );
	void Print( const CConst* node );
	void Print( const CName* node );
	void Print( const CTemp* node );
	void Print( const CBinop* node );
	void Print( const CMem* node );
	void Print( const CCall* node );
	void Print( const CEseq* node );
	void Print( const CExpList* node );
	void Print( const CLabel* node );

private:

	static int minId;

	CDigraph treeRepresentation;
};

} // namespace IRTree