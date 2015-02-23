// Автор: Воротилов Владислав
// Описание: Интерфейс обхода дерева промежуточного представления

#pragma once

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


struct IVisitor {

	virtual void Visit( const CMove* node ) = 0;
	virtual void Visit( const CExp* node ) = 0;
	virtual void Visit( const CJump* node ) = 0;
	virtual void Visit( const CCjump* node ) = 0;
	virtual void Visit( const CSeq* node ) = 0;
	virtual void Visit( const CConst* node ) = 0;
	virtual void Visit( const CName* node ) = 0;
	virtual void Visit( const CTemp* node ) = 0;
	virtual void Visit( const CBinop* node ) = 0;
	virtual void Visit( const CMem* node ) = 0;
	virtual void Visit( const CCall* node ) = 0;
	virtual void Visit( const CEseq* node ) = 0;
	virtual void Visit( const CExpList* node ) = 0;
	virtual void Visit( const CLabel* node ) = 0;

};

} // namespace IRTree