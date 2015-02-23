// Автор: Воротилов Владислав
// Описание: Преобразование дерева промежуточного представления в dot формат

#include "Digrapg.h"
#include "IRTreeVisitor.h"

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


class CIRTreeToDigraphConverter : public IVisitor {
public:
	CIRTreeToDigraphConverter( std::string treeFileName ) : treeRepresentation( treeFileName ) {}

	virtual void Visit( const CMove* node ) override;

	virtual void Visit( const CExp* node ) override;

	virtual void Visit( const CJump* node ) override;

	virtual void Visit( const CCjump* node ) override;

	virtual void Visit( const CSeq* node ) override;

	virtual void Visit( const CConst* node ) override;

	virtual void Visit( const CName* node ) override;

	virtual void Visit( const CTemp* node ) override;

	virtual void Visit( const CBinop* node ) override;

	virtual void Visit( const CMem* node ) override;

	virtual void Visit( const CCall* node ) override;

	virtual void Visit( const CEseq* node ) override;

	virtual void Visit( const CExpList* node ) override;

	virtual void Visit( const CLabel* node ) override;

	void Flush() { treeRepresentation.Flush(); }

private:

	static int minId;

	std::string lastNodeName;

	CDigraph treeRepresentation;

	void nextNameWithId( std::string label );
};

} // namespace IRTree