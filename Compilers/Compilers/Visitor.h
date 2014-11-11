#pragma once

#include "Program.h"
#include "MainClass.h"
#include "ClassDeclList.h"
#include "ClassDecl.h"
#include "VarDeclList.h"
#include "VarDecl.h"
#include "MethodDeclList.h"
#include "FormalList.h"
#include "Exp.h"
#include "ExpList.h"

class IVisitor {
public:
	// EXP -> EXP BINOP EXP
	virtual void visit( CExpBinOpExp& exp );
	// EXP -> -EXP
	virtual void visit( CUnMinExp& exp );
	// EXP -> EXP [ EXP ]
	virtual void visit( CExpWithIndex& exp );
	// EXP -> EXP.LENGTH
	virtual void visit( CExpDotLength& exp );
	// EXP -> EXP . ID ( EXPLIST )
	virtual void visit( CExpIdExpList& exp );
	// EXP -> EXP . ID ( )
	virtual void visit( CExpIdVoidExpList& exp );
	// EXP -> INTEGER_LITERAL
	virtual void visit( CIntegerLiteral& exp );
	// EXP -> TRUE
	virtual void visit( CTrue& exp );
	// EXP -> FALSE
	virtual void visit( CFalse& exp );
	// EXP -> ID
	virtual void visit( CId& exp );
	// EXP -> THIS
	virtual void visit( CThis& exp );
	virtual void visit( CNewIntExpIndex& exp );
	virtual void visit( CNewId& exp );
	virtual void visit( CNotExp& exp );
	virtual void visit( CExpInBrackets& exp );
	virtual void visit( CProgram& program );
	virtual void visit( CMainClass& mainClass );
	virtual void visit( CClassDeclList& classDeclList );
	virtual void visit( CClassDecl& classDecl );
	virtual void visit( CVarDeclList& varDeclList );
	virtual void visit( CVarDecl& varDecl );
	virtual void visit( CMethodDeclList& methodDeclList );
	virtual void visit( CFormalList& formalList );
	virtual void visit( CExp& expList );
	virtual void visit( CExpExpRest& expList );
};