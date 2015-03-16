// Автор: Николай Фролов.

// Описание: Класс, преобразующий вызовы CALL в IRTree в новую конструкцию.

#include <IRTreeVisitor.h>
#include <IRTree.h>
#include <IRStm.h>
#include <IRExp.h>

namespace IRTree {
	class CIRTreeCallLifter : public IRTree::IVisitor  {
	public:
		void Visit( const CMove* node ) override;
		void Visit( const CExp* node ) override;
		void Visit( const CJump* node ) override;
		void Visit( const CCjump* node ) override;
		void Visit( const CSeq* node ) override;
		void Visit( const CConst* node ) override;
		void Visit( const CName* node ) override;
		void Visit( const CTemp* node ) override;
		void Visit( const CBinop* node ) override;
		void Visit( const CMem* node ) override;
		void Visit( const CCall* node ) override;
		void Visit( const CEseq* node ) override;
		void Visit( const CExpList* node ) override;
		void Visit( const CLabel* node ) override;

	private:
		class CPseudoCall {};
	};

}
