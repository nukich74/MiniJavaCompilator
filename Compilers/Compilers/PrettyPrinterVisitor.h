#include "Visitor.h"

class CPrettyPrinterVisitor : public IVisitor {
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
	virtual void visit( CNotExp& exp );
	virtual void visit( CExpInBrackets& exp );
	virtual void visit( CProgram& program );
	virtual void visit( CMainClass& mainClass );
	virtual void visit( CClassDeclList& classDeclList );
	virtual void visit( CClassDecl& classDecl );
	virtual void visit( CVarDeclList& varDeclList );
	virtual void visit( CVarDecl& varDecl );
	virtual void visit( CMethodDeclList& methodDeclList );
};