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
	virtual void Visit( const CExpBinOpExp& exp ) = 0
	{ }
	virtual void Visit( const CUnMinExp& exp ) = 0
	{ }
	virtual void Visit( const CExpWithIndex& exp ) = 0
	{ }
	virtual void Visit( const CExpDotLength& exp ) = 0
	{ }
	virtual void Visit( const CExpIdExpList& exp ) = 0
	{ }
	virtual void Visit( const CExpIdVoidExpList& exp ) = 0
	{ }
	virtual void Visit( const CIntegerLiteral& exp ) = 0
	{ }
	virtual void Visit( const CTrue& exp ) = 0
	{ }
	virtual void Visit( const CFalse& exp ) = 0
	{ }
	virtual void Visit( const CId& exp ) = 0
	{ }
	virtual void Visit( const CThis& exp ) = 0
	{ }
	virtual void Visit( const CNewIntExpIndex& exp ) = 0
	{ }
	virtual void Visit( const CNewId& exp ) = 0
	{ }
	virtual void Visit( const CNotExp& exp ) = 0
	{ }
	virtual void Visit( const CExpInBrackets& exp ) = 0
	{ }
	virtual void Visit( const CProgram& program ) = 0
	{ }
	virtual void Visit( const CMainClass& mainClass ) = 0
	{ }
	virtual void Visit( const CClassDeclList& classDeclList ) = 0
	{ }
	virtual void Visit( const CClassDecl& classDecl ) = 0
	{ }
	virtual void Visit( const CVarDeclList& varDeclList ) = 0
	{ }
	virtual void Visit( const CVarDecl& varDecl ) = 0
	{ }
	virtual void Visit( const CMethodDeclList& methodDeclList ) = 0
	{ }
	virtual void Visit( const CMethodDecl& methodDecl ) = 0
	{ }
	virtual void Visit( const CFormalList& formalList ) = 0
	{ }
	virtual void Visit( const CType& type ) = 0
	{ }
	virtual void Visit( const CStatementList& statementList ) = 0
	{ }
	virtual void Visit( const CAssignStatement& assignStatement ) = 0
	{ }
	virtual void Visit( const CPrintStatement& printStatement ) = 0
	{ }
	virtual void Visit( const CCurlyBraceStatement& curlyBraceStatement ) = 0
	{ }
	virtual void Visit( const CIfStatement& ifStatement ) = 0
	{ }
	virtual void Visit( const CWhileStatement& whileStatement ) = 0
	{ }
	virtual void Visit( const CExpList& expList ) = 0
	{ }
};