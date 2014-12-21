// Автор: Азат Давлетшин
// Описание: Интерфейс для дерева промежуточного представления
#pragma once

namespace IRTree {

class CPrinter;
// Интерфейс для узлов, возвращающих значений
class IExp {
public:
	virtual ~IExp() {}

	virtual void Print( CPrinter& printer ) const = 0;
};

// Интерфейс для управляющих конструкций
class IStm {
public:
	virtual ~IStm() {}

	virtual void Print( CPrinter& printer ) const = 0;
};

}