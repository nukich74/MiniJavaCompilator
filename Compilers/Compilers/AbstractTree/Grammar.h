#pragma once

#include "Visitor.h"

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