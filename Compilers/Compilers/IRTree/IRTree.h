// Автор: Азат Давлетшин
// Описание: Интерфейс для дерева промежуточного представления
#pragma once

namespace IRTree
{

// Интерфейс для узлов, возвращающих значений
class IIRExp {
public:
	virtual ~IIRExp() {}
};

// Интерфейс для управляющих конструкций
class IIRStm {
public:
	virtual ~IIRStm() {}
};

}