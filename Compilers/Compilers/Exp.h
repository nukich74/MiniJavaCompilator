#pragma once

#include "Grammar.h"

class CExpBinOpExp : public IExp {
public:
	CExpBinOpExp( IExp* newLeft, char op, IExp* newRight ) : left( newLeft ), operation( op ), right( newRight ) {}
	char GetOperation( );
	IExp* GetRightChild( );
	IExp* GetLeftChild( );
private:
	IExp* left;
	IExp* right;
	char operation;
};

class CUnMinExp : public IExp {
public:
	CUnMinExp( IExp* child ) : exp( child ) {}
	IExp* GetExp( );
private:
	IExp* exp;
};

class CExpWithIndex : public IExp {
public:
	CExpWithIndex( IExp* newExp, IExp* newIndex ) : exp( newExp ), index( newIndex ) {}
	IExp* GetExp( );
	IExp* GetIndex( );
private:
	IExp* exp;
	IExp* index;
};

class CExpDotLength : public IExp {
public:
	CExpDotLength( IExp* newExp ) : exp( newExp ) {}
	IExp* GetExp( );
private:
	IExp* exp;
};

class CExpIdExpList : public IExp {
public:
	CExpIdExpList( IExp* newExp, IExp* newId, IExpList* newExpList ) : exp( newExp ), id( newId ), expList( newExpList ) {}
	IExp* GetExp( );
	IExp* GetId( );
	IExpList* GetExpList( );
private:
	IExp* exp;
	IExp* id;
	IExpList* expList;
};

class CExpIdVoidExpList : public IExp {
public:
	IExp* GetExp( );
	IExp* GetId( );
private:
	IExp* exp;
	IExp* id;
};

class CIntegerLiteral : public IExp {
public:
	CIntegerLiteral( int newValue ) : value( newValue ) {}
	int GetInteger( );
private:
	int value;
};

class CTrue : public IExp {
public:
	bool GetValue( ) { return true; };
};

class CFalse : public IExp {
public:
	bool GetValue( ) { return false; }
};

class CId : public IExp {
public:
	CId( std::string newValue ) : value( newValue ) {}
	std::string GetString( );
private:
	std::string value;
};
//пока не понятно что тут должно быть
class CThis : public IExp {};

class CNewIntExpIndex : public IExp {
public:
	CNewIntExpIndex( IExp* newExp ) : exp( newExp ) {}
	IExp* GetExp( );
private:
	IExp* exp;
};

class CNewIdExpIndex : public IExp {
public:
	CNewIdExpIndex( IExp* newExp ) : exp( newExp ) {}
	IExp* GetExp( );
private:
	IExp* exp;
};

class CNotExp : public IExp {
public:
	CNotExp( IExp* newExp ) : exp( newExp ) {}
	IExp* GetExp( );
private:
	IExp* exp;
};

class CExpInBrackets : public IExp {
	CExpInBrackets( IExp* newExp ) : exp( newExp ) {}
	IExp* GetExp( );
private:
	IExp* exp;
};