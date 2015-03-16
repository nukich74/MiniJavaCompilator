/*
Автор: Мысин Юрий
*/

#include<IRTreeVisitor.h>
#include<IRTree.h>
#include<IRStm.h>
#include<IRExp.h>
#include<IRHelpers.h>
#include<vector>

using namespace std;

namespace IRTree {
	//Данный класс строит новое дерево, в котором все узлы Eseq перенесены на наивысший уровень
	class IRTreeEseqLifter : public IRTree::IVisitor  {
	public:
		void Visit(const CMove* node) override;
		void Visit(const CExp* node) override;
		void Visit(const CJump* node) override;
		void Visit(const CCjump* node) override;
		void Visit(const CSeq* node) override;
		void Visit(const CConst* node) override;
		void Visit(const CName* node) override;
		void Visit(const CTemp* node) override;
		void Visit(const CBinop* node) override;
		void Visit(const CMem* node) override;
		void Visit(const CCall* node) override;
		void Visit(const CEseq* node) override;
		void Visit(const CExpList* node) override;
		void Visit(const CLabel* node) override;
	private:
		IExp* lastBuildExp;
		IStm* lastBuildStm;
		pair<IStm*, CExpList*> lastBuildPair;
	};

}