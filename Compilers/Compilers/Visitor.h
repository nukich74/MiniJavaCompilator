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
	virtual void visit( const CExpBinOpExp& exp ) = 0
	{ }
	// EXP -> -EXP
	virtual void visit( const CUnMinExp& exp ) = 0
	{ }
	// EXP -> EXP [ EXP ]
	virtual void visit( const CExpWithIndex& exp ) = 0
	{ }
	// EXP -> EXP.LENGTH
	virtual void visit( const CExpDotLength& exp ) = 0
	{ }
	// EXP -> EXP . ID ( EXPLIST )
	virtual void visit( const CExpIdExpList& exp ) = 0
	{ }
	// EXP -> EXP . ID ( )
	virtual void visit( const CExpIdVoidExpList& exp ) = 0
	{ }
	// EXP -> INTEGER_LITERAL
	virtual void visit( const CIntegerLiteral& exp ) = 0
	{ }
	// EXP -> TRUE
	virtual void visit( const CTrue& exp ) = 0
	{ }
	// EXP -> FALSE
	virtual void visit( const CFalse& exp ) = 0
	{ }
	// EXP -> ID
	virtual void visit( const CId& exp ) = 0
	{ }
	// EXP -> THIS
	virtual void visit( const CThis& exp ) = 0
	{ }
	// EXP -> NEW INT [ EXP ]
	virtual void visit( const CNewIntExpIndex& exp ) = 0
	{ }
	// EXP -> NEW ID ( )
	virtual void visit( const CNewId& exp ) = 0
	{ }
	// EXP -> ! EXP
	virtual void visit( const CNotExp& exp ) = 0
	{ }
	// EXP -> ( EXP )
	virtual void visit( const CExpInBrackets& exp ) = 0
	{ }
	virtual void visit( const CProgram& program ) = 0
	{ }
	virtual void visit( const CMainClass& mainClass ) = 0
	{ }
	virtual void visit( const CClassDeclList& classDeclList ) = 0
	{ }
	virtual void visit( const CClassDecl& classDecl ) = 0
	{ }
	virtual void visit( const CVarDeclList& varDeclList ) = 0
	{ }
	virtual void visit( const CVarDecl& varDecl ) = 0
	{ }
	virtual void visit( const CMethodDeclList& methodDeclList ) = 0
	{ }
	virtual void visit( const CMethodDecl& methodDecl ) = 0
	{ }
	virtual void visit( const CFormalList& formalList ) = 0
	{ }
	virtual void visit( const CType& type ) = 0
	{ }
	virtual void visit( const CStatementList& statementList ) = 0
	{ }
	virtual void visit( const CAssignStatement& assignStatement ) = 0
	{ }
	virtual void visit( const CPrintStatement& printStatement ) = 0
	{ }
	virtual void visit( const CCurlyBraceStatement& curlyBraceStatement ) = 0
	{ }
	virtual void visit( const CIfStatement& ifStatement ) = 0
	{ }
	virtual void visit( const CWhileStatement& whileStatement ) = 0
	{ }
	virtual void visit( const CExpList& expList ) = 0
	{ }
};