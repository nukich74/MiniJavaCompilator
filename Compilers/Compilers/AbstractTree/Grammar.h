#pragma once

#include "Visitor.h"
#include "Location.h"

// Класс, хранящий местоположение токена в исходном коде.
class CLocationStorage {
public:
	const CLocation& Location() const { return location; }

protected:
	CLocationStorage( const CLocation& _location )
		: location( _location )
	{ }

private:
	CLocation location;
};

// Корневой интерфейс программы
class IProgram {
public:
	virtual ~IProgram() {}

	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Главный классa
class IMainClass {
public:
	virtual ~IMainClass() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Список классов
class IClassDeclList {
public:
	virtual ~IClassDeclList() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Описание класса
class IClassDecl {
public:
	virtual ~IClassDecl() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Список объявлений переменных
class IVarDeclList {
public:
	virtual ~IVarDeclList() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Объявление переменной
class IVarDecl {
public:
	virtual ~IVarDecl() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Список методов класса
class IMethodDeclList {
public:
	virtual ~IMethodDeclList() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Метод класса
class IMethodDecl {
public:
	virtual ~IMethodDecl() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Список параметров
class IFormalList {
public:
	virtual ~IFormalList() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Тип
class IType {
public:
	virtual ~IType() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Последовательность команд
class IStatementList {
public:
	virtual ~IStatementList() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Одна команда (или блок)
class IStatement {
public:
	virtual ~IStatement() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Последовательность выражений (аргументы функции)
class IExpList {
public:
	virtual ~IExpList() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};

// Арифметическое выражение
class IExp {
public:
	virtual ~IExp() {}
	virtual void Accept( IVisitor& visitor ) const = 0;
};