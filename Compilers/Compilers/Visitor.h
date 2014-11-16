#pragma once

class CExpBinOpExp;
class CUnMinExp;
class CExpWithIndex;
class CExpDotLength;
class CExpIdExpList;
class CExpIdVoidExpList;
class CIntegerLiteral;
class CTrue;
class CFalse;
class CId;
class CThis;
class CNewIntExpIndex;
class CNewId;
class CNotExp;
class CExpInBrackets;
class CProgram;
class CMainClass;
class CClassDeclList;
class CClassDecl;
class CVarDeclList;
class CVarDecl;
class CMethodDeclList;
class CMethodDecl;
class CFormalList;
class CType;
class CStatementList;
class CAssignStatement;
class CPrintStatement;
class CCurlyBraceStatement;
class CIfStatement;
class CWhileStatement;
class CExpList;

class IVisitor {
public:
	// EXP -> EXP BINOP EXP
	virtual void visit( CExpBinOpExp& exp ) = 0
	{ }
	// EXP -> -EXP
	virtual void visit( CUnMinExp& exp ) = 0
	{ }
	// EXP -> EXP [ EXP ]
	virtual void visit( CExpWithIndex& exp ) = 0
	{ }
	// EXP -> EXP.LENGTH
	virtual void visit( CExpDotLength& exp ) = 0
	{ }
	// EXP -> EXP . ID ( EXPLIST )
	virtual void visit( CExpIdExpList& exp ) = 0
	{ }
	// EXP -> EXP . ID ( )
	virtual void visit( CExpIdVoidExpList& exp ) = 0
	{ }
	// EXP -> INTEGER_LITERAL
	virtual void visit( CIntegerLiteral& exp ) = 0
	{ }
	// EXP -> TRUE
	virtual void visit( CTrue& exp ) = 0
	{ }
	// EXP -> FALSE
	virtual void visit( CFalse& exp ) = 0
	{ }
	// EXP -> ID
	virtual void visit( CId& exp ) = 0
	{ }
	// EXP -> THIS
	virtual void visit( CThis& exp ) = 0
	{ }
	// EXP -> NEW INT [ EXP ]
	virtual void visit( CNewIntExpIndex& exp ) = 0
	{ }
	// EXP -> NEW ID ( )
	virtual void visit( CNewId& exp ) = 0
	{ }
	// EXP -> ! EXP
	virtual void visit( CNotExp& exp ) = 0
	{ }
	// EXP -> ( EXP )
	virtual void visit( CExpInBrackets& exp ) = 0
	{ }
	virtual void visit( CProgram& program ) = 0
	{ }
	virtual void visit( CMainClass& mainClass ) = 0
	{ }
	virtual void visit( CClassDeclList& classDeclList ) = 0
	{ }
	virtual void visit( CClassDecl& classDecl ) = 0
	{ }
	virtual void visit( CVarDeclList& varDeclList ) = 0
	{ }
	virtual void visit( CVarDecl& varDecl ) = 0
	{ }
	virtual void visit( CMethodDeclList& methodDeclList ) = 0
	{ }
	virtual void visit( CMethodDecl& methodDecl ) = 0
	{ }
	virtual void visit( CFormalList& formalList ) = 0
	{ }
	virtual void visit( CType& type ) = 0
	{ }
	virtual void visit( CStatementList& statementList ) = 0
	{ }
	virtual void visit( CAssignStatement& assignStatement ) = 0
	{ }
	virtual void visit( CPrintStatement& printStatement ) = 0
	{ }
	virtual void visit( CCurlyBraceStatement& curlyBraceStatement ) = 0
	{ }
	virtual void visit( CIfStatement& ifStatement ) = 0
	{ }
	virtual void visit( CWhileStatement& whileStatement ) = 0
	{ }
	virtual void visit( CExpList& expList ) = 0
	{ }
};