#pragma once

#include "Program.h"
#include "Exp.h"

class IVisitor {
public:
	virtual void visit( CExpBinOpExp& exp );
	virtual void visit( CUnMinExp& exp );
	virtual void visit( CExpWithIndex& exp );
	virtual void visit( CExpDotLength& exp );
	virtual void visit( CExpIdExpList& exp );
	virtual void visit( CExpIdVoidExpList& exp );
	virtual void visit( CIntegerLiteral& exp );
	virtual void visit( CTrue& exp );
	virtual void visit( CFalse& exp );
	virtual void visit( CId& exp );
	virtual void visit( CThis& exp );
	virtual void visit( CNewIntExpIndex& exp );
	virtual void visit( CNewIdExpIndex& exp );
	virtual void visit( CNotExp& exp );
	virtual void visit( CExpInBrackets& exp );
	virtual void visit( CProgram& exp );
};