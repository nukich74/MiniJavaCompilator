// Автор: Азат Давлетшин
// Описание: Интерфейс для дерева промежуточного представления
#pragma once

namespace IRTree {

struct IVisitor;
// Интерфейс для узлов, возвращающих значений
class IExp {
public:
	virtual ~IExp() {}

	virtual void Visit( IVisitor& printer ) const = 0;
};

// Интерфейс для управляющих конструкций
class IStm {
public:
	virtual ~IStm() {}

	virtual void Visit( IVisitor& printer ) const = 0;
};

}