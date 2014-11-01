#pragma once

#include <string>

class IVisitor;

// Корневой интерфейс программы
class IProgram {
public:
	virtual ~IProgram() {}
	void accept( IVisitor& visitor );
};

// Главный классa
class IMainClass {
public:
	virtual ~IMainClass() {}
	void accept( IVisitor& visitor );
};

// Список классов
class IClassDeclList {
public:
	virtual ~IClassDeclList() {}
	void accept( IVisitor& visitor );
};

// Описание класса
class IClassDecl {
public:
	virtual ~IClassDecl() {}
	void accept( IVisitor& visitor );
};

// Список объявлений переменных
class IVarDeclList {
public:
	virtual ~IVarDeclList() {}
	void accept( IVisitor& visitor );
};

// Объявление переменной
class IVarDecl {
public:
	virtual ~IVarDecl() {}
	void accept( IVisitor& visitor );
};

// Список методов класса
class IMethodDeclList {
public:
	virtual ~IMethodDeclList() {}
	void accept( IVisitor& visitor );
};

// Метод класса
class IMethodDecl {
public:
	virtual ~IMethodDecl() {}
	void accept( IVisitor& visitor );
};

// Список параметров
class IFormalList {
public:
	virtual ~IFormalList() {}
	void accept( IVisitor& visitor );
};

// Тип
class IType {
public:
	virtual ~IType() {}
	void accept( IVisitor& visitor );
};

// Последовательность команд
class IStatementList {
public:
	virtual ~IStatementList() {}
	void accept( IVisitor& visitor );
};

// Одна команда (или блок)
class IStatement {
public:
	virtual ~IStatement() {}
	void accept( IVisitor& visitor );
};

// Последовательность выражений (аргументы функции)
class IExpList {
public:
	virtual ~IExpList() {}
	void accept( IVisitor& visitor );
};

// Арифметическое выражение
class IExp {
public:
	virtual ~IExp() {}
	void accept( IVisitor& visitor );
};

class CExpBinOpExp : public IExp {
public:
	CExpBinOpExp(IExp* newLeft, char op, IExp* newRight) : left(newLeft), operation(op), right(newRight) {}
	char GetOperation();
	IExp* GetRightChild();
	IExp* GetLeftChild();
private:
	IExp* left;
	IExp* right;
	char operation;
};

class CUnMinExp : public IExp {
public:
	CUnMinExp(IExp* child) : exp(child) {}
	IExp* GetExp();
private:
	IExp* exp;
};

class CExpWithIndex : public IExp {
public:
	CExpWithIndex(IExp* newExp, IExp* newIndex) : exp(newExp), index(newIndex) {}
	IExp* GetExp();
	IExp* GetIndex();
private:
	IExp* exp;
	IExp* index;
};

class CExpDotLength : public IExp {
public:
	CExpDotLength(IExp* newExp) : exp(newExp) {}
	IExp* GetExp();
private:
	IExp* exp;
};

class CExpIdExpList : public IExp {
public:
	CExpIdExpList(IExp* newExp, IExp* newId, IExpList* newExpList) : exp(newExp), id(newId), expList(newExpList) {}
	IExp* GetExp();
	IExp* GetId();
	IExpList* GetExpList();
private:
	IExp* exp;
	IExp* id;
	IExpList* expList;
};

class CExpIdVoidExpList : public IExp {
public:
	IExp* GetExp();
	IExp* GetId();
private:
	IExp* exp;
	IExp* id;
};

class CIntegerLiteral : public IExp {
public:
	CIntegerLiteral(int newValue) : value(newValue) {}
	int GetInteger();
private:
	int value;
};

class CTrue : public IExp {
public:
	bool GetValue() { return true; };
};

class CFalse : public IExp {
public:
	bool GetValue() { return false; }
};

class CId : public IExp {
public:
	CId(std::string newValue) : value(newValue) {}
	std::string GetString();
private:
	std::string value;
};
//пока не понятно что тут должно быть
class CThis : public IExp {
};

class CNewIntExpIndex : public IExp {
public:
	CNewIntExpIndex(IExp* newExp) : exp(newExp) {}
	IExp* GetExp();
private:
	IExp* exp;
};

class CNewIdExpIndex : public IExp	{
public:
	CNewIdExpIndex(IExp* newExp) : exp(newExp) {}
	IExp* GetExp();
private:
	IExp* exp;
};

class CNotExp : public IExp {
public:
	CNotExp(IExp* newExp) : exp(newExp) {}
	IExp* GetExp();
private:
	IExp* exp;
};

class CExpInBrackets : public IExp {
	CExpInBrackets(IExp* newExp) : exp(newExp) {}
	IExp* GetExp();
private:
	IExp* exp;
};

class C


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
};