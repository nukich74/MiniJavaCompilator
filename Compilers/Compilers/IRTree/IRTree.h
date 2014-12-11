// Автор: Азат Давлетшин
// Описание: Интерфейс для дерева промежуточного представления
#pragma once

namespace IRTree
{

class CPrinter;
// Интерфейс для узлов, возвращающих значений
class IIRExp {
public:
	virtual ~IIRExp() {}

	virtual void Print( CPrinter& printer ) const = 0;
};

// Интерфейс для управляющих конструкций
class IIRStm {
public:
	virtual ~IIRStm() {}

	virtual void Print( CPrinter& printer ) const = 0;
};

}