// Автор: Азат Давлетшин
// Описание: Принтер IRTree

#pragma once

#include <map>

namespace IRTree
{
class CIRMove;
class CIRExp;
class CIRJump;
class CIRCjump;
class CIRSeq;
class CIRConst;
class CIRName;
class CIRTemp;
class CIRBinop;
class CIRMem;
class CIRCall;
class CIREseq;
class CIRExpList;


class CPrinter {
public:
	CPrinter();

	void Print( const CIRMove* node );
	void Print( const CIRExp* node );
	void Print( const CIRJump* node );
	void Print( const CIRCjump* node );
	void Print( const CIRSeq* node );
	void Print( const CIRConst* node );
	void Print( const CIRName* node );
	void Print( const CIRTemp* node );
	void Print( const CIRBinop* node );
	void Print( const CIRMem* node );
	void Print( const CIRCall* node );
	void Print( const CIREseq* node );
	void Print( const CIRExpList* node );
private:
	std::map<const void*, int> ids;
	std::map<const void*, int> parents;
	static int minId;
};

}