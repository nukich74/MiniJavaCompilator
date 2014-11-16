#pragma once

#include "Visitor.h"

// Корневой интерфейс программы
class IProgram {
public:
	virtual ~IProgram() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Главный классa
class IMainClass {
public:
	virtual ~IMainClass() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Список классов
class IClassDeclList {
public:
	virtual ~IClassDeclList() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Описание класса
class IClassDecl {
public:
	virtual ~IClassDecl() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Список объявлений переменных
class IVarDeclList {
public:
	virtual ~IVarDeclList() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Объявление переменной
class IVarDecl {
public:
	virtual ~IVarDecl() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Список методов класса
class IMethodDeclList {
public:
	virtual ~IMethodDeclList() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Метод класса
class IMethodDecl {
public:
	virtual ~IMethodDecl() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Список параметров
class IFormalList {
public:
	virtual ~IFormalList() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Тип
class IType {
public:
	virtual ~IType() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Последовательность команд
class IStatementList {
public:
	virtual ~IStatementList() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Одна команда (или блок)
class IStatement {
public:
	virtual ~IStatement() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Последовательность выражений (аргументы функции)
class IExpList {
public:
	virtual ~IExpList() {}
	virtual void accept( IVisitor& visitor ) = 0;
};

// Арифметическое выражение
class IExp {
public:
	virtual ~IExp() {}
	virtual void accept( IVisitor& visitor ) = 0;
};